#include "HXApp.h"
#include "Debug.h"
#include "HTime.h"	
#include "InputHandler.h"


#pragma region STATIC GAME INSTANCE and GLOBAL ACCESS FUNCTION

HXApp* HXApp::_hXAppInstance = nullptr;

HXApp* HXApp::GetHXApp()
{
	if (_hXAppInstance == nullptr) 
		_hXAppInstance = new HXApp();
	
	return _hXAppInstance;
}
#pragma endregion

//////////////////////////////////////////////////

#pragma region CONSTUCTOR(S) & DESTRUCTOR

// Default constructor
//
// Empty body
// Mainly used as field or reference pointer initializer
//
HXApp::HXApp()
	: _graphics(nullptr), _fpsCounter(nullptr), 
	_isFullScreen(false), _width(0), _height(0),
	_hwnd(NULL), _hInstance(nullptr),
	_timeSinceLastUpdate(0.0f), _lastUpdateTime(0.0f), _deltaTime(0.0f)
{
	// empty
}

HXApp::~HXApp()
{
	ShutdownEngine();
}
#pragma endregion

/////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region INITIALIZERS

// INIT WINDOW

bool HXApp::InitWindow(int width, int height, bool isFullscreen, HINSTANCE hInstance)
{
	_width = width;
	_height = height;

	_isFullScreen = isFullscreen;
	_hInstance = &hInstance;

	PIXELFORMATDESCRIPTOR pfd;

	// Create an extended styles windows class called wc, then fill out all the properties. 
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc = {
		sizeof(WNDCLASSEX),							// cbSize
		CS_CLASSDC || CS_HREDRAW || CS_VREDRAW,		// style
		HXApp::WndProc,								//lpfnWndProc
		0L, 
		0L, 
		GetModuleHandle(NULL),				// hInstance
		LoadIcon(NULL, IDI_APPLICATION),	// top left corner icon
		LoadCursor(NULL, IDC_ARROW),		// cursor icon
		NULL, 
		NULL,								// hbrBackground
		_T(HXApp::_className),				// lpszClassName
		NULL
	};

	RECT rect;
	UINT w, h;

	// Adjust Fullscreen settings
	DEVMODE dmScreenSettings;

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



	// Register the class.
	// If it fails we get an error. If it passes we move on to create the window
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Error registering class", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	// Set the HINSTANCE reference if haven't already
	if (_hInstance == NULL)
		HXApp::_hInstance = &wc.hInstance;

	// Create the window
	HXApp::_hwnd = 
		CreateWindowEx(
			WS_EX_APPWINDOW, 
			HXApp::_className, 
			"Hurricane Game", 
			WS_OVERLAPPEDWINDOW, // WS_OVERLAPPED || WS_CAPTION, WS_SYSMENU || WS_THICKFRAME || WS_MINIMIZEBOX || WS_MAXIMIZEBOX
			CW_USEDEFAULT, 
			CW_USEDEFAULT, 
			w, h, 
			NULL, NULL, 
			wc.hInstance,		// instance of window
			NULL
		);

	if (!_hwnd)
	{
		MessageBox(NULL, "Error Creating Window", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	HXApp::_hdc = GetDC(_hwnd);

	/* there is no guarantee that the contents of the stack that become
	the pfd are zeroed, therefore _make sure_ to clear these bits. */
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | 0; // flags;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;

	int pf = ChoosePixelFormat(_hdc, &pfd);
	if (pf == 0) {
		MessageBox(NULL, "ChoosePixelFormat() failed:  "
			"Cannot find a suitable pixel format.", "Error", MB_OK);
		return false;
	}

	if (SetPixelFormat(_hdc, pf, &pfd) == FALSE) {
		MessageBox(NULL, "SetPixelFormat() failed:  "
			"Cannot set format specified.", "Error", MB_OK);
		return false;
	}

	DescribePixelFormat(_hdc, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	ReleaseDC(_hwnd, _hdc);

	//we need to now show the window and refresh it using UpdateWindow()
	ShowWindow(_hwnd, SW_SHOW);

	return true;
}

// DIRECTX 2D Renderer

bool HXApp::InitGraphics()
{
	_graphics = new Graphics();
	if (!_graphics ->InitGraphics(HXApp::_hwnd, _width, _height, _isFullScreen)) {
		MessageBox(NULL, "Graphics initialization FAILED", "FATAL ERROR", 0);
		return false;
	}

	return true;
}


// NOTE: Helper Function
// Allow only the engine itself to initialize the window and renderer
bool HXApp::InitEngine(int width, int height, bool isFullscreen, HINSTANCE hInstance)
{
	bool a = InitWindow(width, height, isFullscreen, hInstance);
	bool b = InitGraphics();

	if (!a || !b)
		return false;

	return true;
}

#pragma endregion

/////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region SYSTEM SHUTDOWN

void HXApp::ShutdownEngine() {
	if (_graphics)
		delete _graphics;
	_graphics = nullptr;

	// Show the mouse cursor
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode
	if (IsFullscreen())
		ChangeDisplaySettings(NULL, 0);

	// Remove the window
	DestroyWindow(_hwnd);
	_hwnd = NULL;

	// Remove the application instance
	UnregisterClass(_className, *_hInstance);
	_hInstance = nullptr;
}

#pragma endregion

/////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region MESSAGE & GAME LOOP LOGIC

/// MESSAGE LOOP
//
// This is the message loop that will be called by the window class
// The main game loop logic is imbedded and called here
//
int HXApp::MessageLoop() 
{
	_fpsCounter = FPS_COUNTER;
	_fpsCounter->SetMaxFPS(120.0f);

	timer.Reset();

	MSG msg; //make instance to MSG structure
	ZeroMemory(&msg, sizeof(MSG)); //clears the struct and sets it to null

	while (msg.message != WM_QUIT) //while there's a message...
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) //If the message was a quit message, we close our program.
				break;

			TranslateMessage(&msg); //If our message was a windows message, we translate, then dispatch.
			DispatchMessage(&msg);
		}
		else //if there ws not a windows message, we run our game
		{
			HXApp::GameLoop();
		}
	}
	return msg.wParam;
}


// GAME LOOP LOGIC
//
// It is better to separate out the code to this function
//
void HXApp::GameLoop() 
{
	// CALCULATE DELTA-TIME
	HTime::Update();

	_deltaTime = HTime::GetDeltaTime();

	// Update
	Update(_deltaTime);
	CalculateFrameStats();

	// Pre-render
	_graphics->BeginDraw();

	//*** Draw stuff HERE ***//

	// Override by derived game
	Render(_deltaTime);
	//***********************//

	// Post-render
	_graphics->EndDraw();

	// Update deltatime
	_fpsCounter->UpdateFPS();
}
#pragma endregion

/////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region WNDPROC CALLBACK FUNCTION

// CALLBACK WINDOW PROCEDURE FUNCTION 
//
// Used for Win32 window 
//
LRESULT CALLBACK HXApp::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	PAINTSTRUCT ps;

	switch (msg) {
	case WM_PAINT:
		BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		return 0;

	// Check if a key has been pressed on the keyboard
	case WM_KEYDOWN:
		if (wparam == VK_ESCAPE)
		{
			if (MessageBox(0, "Are you sure you want to exit?", "Exit Game?", MB_YESNO | MB_ICONQUESTION) == IDYES)
				DestroyWindow(hwnd);
		}
		INPUT->KeyDown((unsigned int)wparam);
		return 0;
	

	// Check if a key has been released on the keyboard
	case WM_KEYUP:
		// If a key is released then send it to the input object so it can unset the state for that key
		INPUT->KeyUp((unsigned int)wparam);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	// Any other messages send to the default message handler as our application won't make use of them
	default:		
		return DefWindowProc(hwnd, msg, wparam, lparam);		
	}

}


//
////// This was PROTOTYPED back in the HXApp class declaration
//LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	PAINTSTRUCT ps;
//	HDC hdc;
//
//	////check the message for events
//	switch (msg) {
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		return 0;
//	}
//
//	/*This is the default windows procedure function. We call this at the end to take care of all the
//	messages we recieve but don't take care of ourselves.*/
//	return HXGAME->MessageHandler(hwnd, msg, wParam, lParam);
//}

#pragma endregion


#pragma region FRAME RATE CALCULATION

void HXApp::CalculateFrameStats() 
{
	static int frameCnt = 0;
	static float timeElapsed = 0.0f;
	frameCnt++;

	// Compute averages over one second period.
	if ((timer.TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;
		STRINGSTREAM outs;
		outs.precision(6);
		outs << _mainWndCaption << L" "
			<< L"FPS: " << fps << L" "
			<< L"Frame Time: " << mspf << L" (ms)";

		// Set the caption of the window
		SetWindowText(HXApp::_hwnd, outs.str().c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

#pragma endregion