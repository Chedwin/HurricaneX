#include "DXApp.h"
#include "DXRenderer.h"
#include "GLRenderer.h"

// STATIC GAME INSTANCE

DXApp* DXApp::_dxAppInstance = nullptr;

DXApp* DXApp::GetDXApp()
{
	if (_dxAppInstance == nullptr) 
		_dxAppInstance = new DXApp();
	
	return _dxAppInstance;
}


//////////////////////////////////////////////////

// CONSTUCTOR(S) & DESTRUCTOR

DXApp::DXApp() 
	: _renderer(nullptr), _fpsCounter(nullptr),
	_isFullScreen(false), _width(0), _height(0), 
	_hwnd(NULL), _hInstance(NULL)
{
	// empty
}

DXApp::~DXApp()
{
	if (_renderer)
		delete _renderer;

	_renderer = nullptr;

	// Show the mouse cursor
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode
	if (IsFullscreen())
		ChangeDisplaySettings(NULL, 0);

	// Remove the window
	DestroyWindow(_hwnd);
	_hwnd = NULL;

	// Remove the application instance
	UnregisterClass(_className, _hInstance);
	_hInstance = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

// Prototype our callback window procedure function
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// INIT WINDOW

bool DXApp::InitWindow(HINSTANCE hInstance, int width, int height, bool isFullscreen)
{
	_width = width;
	_height = height;

	_isFullScreen = isFullscreen;
	_hInstance = hInstance;

	DEVMODE dmScreenSettings;

	//create an extended styles windows class called wc, then fill out all the properties. 
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));


	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.lpszClassName = DXApp::_className; // HGAME


	RECT rect;
	UINT w, h;

	if (isFullscreen) 
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)_width;
		dmScreenSettings.dmPelsHeight = (unsigned long)_height;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		w = width;
		h = height;
	}
	else 
	{
		rect = { 0, 0, width, height };
		AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);

		w = rect.right - rect.left;
		h = rect.bottom - rect.top;
	}



	//register the class, if it fails we get an error. If it passes we move on to create the window
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Error registering class", "Error", MB_OK | MB_ICONERROR);
		return false;
	}



	//// screen will always be centered to your monitor when it launches
	//UINT x = GetSystemMetrics((SM_CXSCREEN) / 2 - w / 2);
	//UINT y = GetSystemMetrics((SM_CYSCREEN) / 2 - h / 2);

	//create the window
	_hwnd = CreateWindowEx(WS_EX_APPWINDOW, DXApp::_className, "Hurricane Game", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 
		//x, y,
		w, h, 
		NULL, NULL, hInstance, NULL);

	if (!_hwnd)
	{
		MessageBox(NULL, "Error Creating Window", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//we need to now show the window and refresh it using UpdateWindow()
	ShowWindow(_hwnd, SW_SHOW);

	SetForegroundWindow(_hwnd);
	SetFocus(_hwnd);

	/** send a WM_PAINT message directly to the windows procedure. If there isn't anything in the client area
	of the window, then UpdateWindow() does not send a message. We then return true so our WinMain()
	function can get on to the message loop.
	**/
	//UpdateWindow(_hwnd);
	
	_fpsCounter = FPS_COUNTER;

	return true;
}


bool DXApp::InitRenderer()
{
	_renderer = new DXRenderer();

	if (!_renderer->InitRenderer(_hwnd, _width, _height, _isFullScreen)) 
	{
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

			TranslateMessage(&msg); //If our message was a windows message, we translate, then dispatch.
			DispatchMessage(&msg);
		}
		else //if there ws not a windows message, we run our game
		{
			_fpsCounter->BeginFrame();

			//run game code here
			Update(2.0f);

			// Pre-render
			_renderer->BeginFrame();

			//*** Draw stuff HERE ***//
			Render(2.0f);
			//***********************//

			// Post-render (back buffering)
			_renderer->EndFrame();

			_fps = _fpsCounter->End();
		}
	}
	return msg.wParam;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT DXApp::MessageHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg) 
	{
		// Check if a key has been pressed on the keyboard
		case WM_KEYDOWN:
		{
			// If a key is pressed send it to the input object so it can record that state
			//m_Input->KeyDown((unsigned int)wparam);
			return 0;
		}

		// Check if a key has been released on the keyboard
		case WM_KEYUP:
		{
			// If a key is released then send it to the input object so it can unset the state for that key
			//m_Input->KeyUp((unsigned int)wparam);
			MessageBox(NULL, "You pressed a key!", "Box", NULL);
			return 0;
		}

		// Any other messages send to the default message handler as our application won't make use of them
		default:
		{
			return DefWindowProc(hwnd, msg, wparam, lparam);
		}
	}

}



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//check the message for events
	switch (msg) {
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
	default:
		return DX11GAME->MessageHandler(hwnd, msg, wParam, lParam);
	}

	/*This is the default windows procedure function. We call this at the end to take care of all the
	messages we recieve but don't take care of ourselves.*/
	//return DefWindowProc(hwnd, msg, wParam, lParam);
}