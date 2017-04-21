#include "DXApp.h"

// STATIC GAME INSTANCE

DXApp* DXApp::_dxAppInstance = nullptr;

DXApp * DXApp::GetDXApp()
{
	if (_dxAppInstance == nullptr) 
		_dxAppInstance = new DXApp();
	
	return _dxAppInstance;
}


//////////////////////////////////////////////////

// CONSTUCTOR(S) & DESTRUCTOR

DXApp::DXApp() : _dxRenderer(nullptr)
{
	// empty
}

DXApp::~DXApp()
{
	if (_dxRenderer)
		delete _dxRenderer;

	_dxRenderer = nullptr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

// Prototype our callback window procedure function
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// INIT WINDOW

bool DXApp::InitWindow(HINSTANCE hInstance, int width, int height, bool windowed)
{
	_width = width;
	_height = height;

	//create an extended styles windows class called wc, then fill out all the properties. 
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = DXApp::_className; // HGAME
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//register the class, if it fails we get an error. If it passes we move on to create the window
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Error registering class", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	RECT rect = { 0, 0, width, height };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);

	UINT w = rect.right - rect.left;
	UINT h = rect.bottom - rect.top;

	//// screen will always be centered to your monitor when it launches
	//UINT x = GetSystemMetrics((SM_CXSCREEN) / 2 - w / 2);
	//UINT y = GetSystemMetrics((SM_CYSCREEN) / 2 - h / 2);

	//create the window
	_hwnd = CreateWindowEx(NULL, DXApp::_className, "Hurricane Game", WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT, 
		//x, y,
		width, height, 
		NULL, NULL, hInstance, NULL);

	if (!_hwnd)
	{
		MessageBox(NULL, "Error Creating Window", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//we need to now show the window and refresh it using UpdateWindow()
	ShowWindow(_hwnd, SW_SHOW);

	/** send a WM_PAINT message directly to the windows procedure. If there isn't anything in the client area
	of the window, then UpdateWindow() does not send a message. We then return true so our WinMain()
	function can get on to the message loop.
	**/
	UpdateWindow(_hwnd);

	return true;
}


bool DXApp::InitRenderer(HINSTANCE hInstance)
{
	_dxRenderer = new DXRenderer();

	if (!_dxRenderer->CreateDeviceAndRenderTarget(_hwnd, _width, _height)) {
		MessageBox(NULL, "Initialization of DirectX 11 FAILED", "FATAL ERROR", 0);
		return false;
	}

	return true;
}


int DXApp::MessageLoop() 
{
	MSG msg; //make instance to MSG structure
	ZeroMemory(&msg, sizeof(MSG)); //clears the struct and sets it to null

	while (true) //while thre's a message...
	{
		BOOL PeekMessageL(
			LPMSG lpMsg,
			HWND hWnd,
			UINT wMsgFilterMin,
			UINT wMsgFilterMax,
			UINT wRemoveMsg
		);

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{

			if (msg.message == WM_QUIT) //If the message was a quit message, we close our program.
				break;

			TranslateMessage(&msg);//If our message was a windows message, we translate, then dispatch.
			DispatchMessage(&msg);
		}
		else //if there ws not a windows message, we run our game
		{
			//run game code here
			Update(2.0f);


			_dxRenderer->BeginFrame();

			//*** Draw stuff HERE ***//
			Render(2.0f);
			//***********************//

			_dxRenderer->EndFrame();
		}
	}
	return msg.wParam;
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//check the message for events
	switch (msg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			if (MessageBox(0, "Are you sure you want to exit?", "Exit Game?", MB_YESNO | MB_ICONQUESTION) == IDYES)
				DestroyWindow(hwnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	/*This is the default windows procedure function. We call this at the end to take care of all the
	messages we recieve but don't take care of ourselves.*/
	return DefWindowProc(hwnd, msg, wParam, lParam);
}