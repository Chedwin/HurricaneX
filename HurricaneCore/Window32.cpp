#include "Window32.h"
#include "IHGame.h"

using namespace HurricaneEngine;

Window32::~Window32() 
{
	ExitWindow();
}


bool Window32::InitWindow(int _wd, int _hg, bool _fs)
{
	_width = _wd;
	_height = _hg;

	_isFullScreen = _fs;

	PIXELFORMATDESCRIPTOR pfd;

	// Create an extended styles windows class called wc, then fill out all the properties. 
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc = {
		sizeof(WNDCLASSEX),							// cbSize
		CS_CLASSDC || CS_HREDRAW || CS_VREDRAW,		// style
		IHGame::WndProc,								//lpfnWndProc
		0L,
		0L,
		GetModuleHandle(NULL),				// hInstance
		LoadIcon(NULL, IDI_APPLICATION),	// top left corner icon
		LoadCursor(NULL, IDC_ARROW),		// cursor icon
		NULL,
		NULL,								// hbrBackground
		_T(_className),				// lpszClassName
		NULL
	};

	RECT rect;
	UINT w, h;

	// Adjust Fullscreen settings
	DEVMODE dmScreenSettings;

	if (_isFullScreen)
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

		w = _width;
		h = _height;
	}
	else
	{
		rect = { 0, 0, _width, _height };
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
		_hInstance = &wc.hInstance;

	// Create the window
	_hwnd =
		CreateWindowEx(
			WS_EX_APPWINDOW,
			_className,
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

	_hdc = GetDC(_hwnd);

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

void Window32::ExitWindow()
{
	// Show the mouse cursor
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode
	if (IsFullScreen())
		ChangeDisplaySettings(NULL, 0);

	// Remove the window
	DestroyWindow(_hwnd);
	_hwnd = NULL;

	// Remove the application instance
	UnregisterClass(_className, *_hInstance);
	_hInstance = nullptr;
}

void Window32::SetWindowTitleText(const STRING& _title)
{
	SetWindowText(Window32::_hwnd, _title.c_str());
}
