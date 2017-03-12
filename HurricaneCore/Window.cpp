#include "Window.h"

LRESULT CALLBACK WndProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	if (msg == WM_DESTROY || msg == WM_CLOSE) {
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(handle, msg, wParam, lParam);
}

Window::Window(HINSTANCE _hInst, int show, int _width, int _height)
{
	WNDCLASS wc = { 0 };
	wc.style = CS_HREDRAW | CS_VREDRAW; // window to be painted either horizontally or vertically
	wc.lpfnWndProc = WndProc; // pointer to the window procedure function to deal w/ the WNDCLASS instance
	wc.cbClsExtra = 0; // extra memory slot for own purpose
	wc.cbWndExtra = 0; // extra memory slot for own purpose
	wc.hInstance = _hInst; // handle application instance
	wc.hIcon = LoadIcon(0, IDI_APPLICATION); // specify a handle to an icon to use for windows created using this struct
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.lpszMenuName = 0; // window's menu, no menu = 0
	wc.lpszClassName = "BasicWndClass"; // specifies name of the window class structure we're creating

	if (!RegisterClass(&wc)) {
		MessageBox(0, "RegisterClass FAILED", 0, 0);
		exit(0);
	}

	_window = CreateWindow(
		"BasicWndClass", // regiestered WNDCLASS instance to use
		"Win32Basic", // window title
		WS_OVERLAPPEDWINDOW, // style flags
		CW_USEDEFAULT, // x-coordinate
		CW_USEDEFAULT, // y-coordinate
		_width, // width
		_height, // height
		0, // parent window
		0, // menu handle
		_hInst, // app instance
		0 // extra creation parameters
	);
	
	if (_window == 0) {
		MessageBox(0, "CreateWindow FAILED", 0, 0);
		exit(0);
	}

	ShowWindow(_window, show);
	UpdateWindow(_window);
}

Window::~Window()
{
}

HWND Window::GetHandle() const
{
	return _window;
}
