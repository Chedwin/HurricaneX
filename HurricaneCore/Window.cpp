#include "Window.h"

// static window HDC
//HDC Window::hDC;

//void SetupPixelFormat(HDC hDC)
//{
//	int pixelFormat;
//
//	PIXELFORMATDESCRIPTOR pfd =
//	{
//		sizeof(PIXELFORMATDESCRIPTOR),	// size
//		1,							// version
//		PFD_SUPPORT_OPENGL |		// OpenGL window
//		PFD_DRAW_TO_WINDOW |		// render to window
//		PFD_DOUBLEBUFFER,			// support double-buffering
//		PFD_TYPE_RGBA,				// color type
//		32,							// prefered color depth
//		0, 0, 0, 0, 0, 0,			// color bits (ignored)
//		0,							// no alpha buffer
//		0,							// alpha bits (ignored)
//		0,							// no accumulation buffer
//		0, 0, 0, 0,					// accum bits (ignored)
//		16,							// depth buffer
//		0,							// no stencil buffer
//		0,							// no auxiliary buffers
//		PFD_MAIN_PLANE,				// main layer
//		0,							// reserved
//		0, 0, 0,					// no layer, visible, damage masks
//	};
//
//	pixelFormat = ChoosePixelFormat(hDC, &pfd);
//	SetPixelFormat(hDC, pixelFormat, &pfd);
//}


LRESULT CALLBACK WndProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	////static HDC hDC;
	//static HGLRC hRC;
	//int height, width;

	//// dispatch messages
	//switch (msg)
	//{
	//case WM_CREATE:			// window creation
	//	Window::hDC = GetDC(handle);
	//	SetupPixelFormat(Window::hDC);
	//	//SetupPalette();
	//	hRC = wglCreateContext(Window::hDC);
	//	wglMakeCurrent(Window::hDC, hRC);
	//	break;

	//case WM_DESTROY:			// window destroy
	//case WM_QUIT:
	//case WM_CLOSE:					// windows is closing

	//								// deselect rendering context and delete it
	//	wglMakeCurrent(Window::hDC, NULL);
	//	wglDeleteContext(hRC);

	//	// send WM_QUIT to message queue
	//	PostQuitMessage(0);
	//	break;

	//case WM_SIZE:
	//	height = HIWORD(lParam);		// retrieve width and height
	//	width = LOWORD(lParam);

	//	break;

	//case WM_ACTIVATEAPP:		// activate app
	//	break;

	//case WM_PAINT:				// paint
	//	PAINTSTRUCT ps;
	//	BeginPaint(handle, &ps);
	//	EndPaint(handle, &ps);
	//	break;

	//case WM_LBUTTONDOWN:		// left mouse button
	//	break;

	//case WM_RBUTTONDOWN:		// right mouse button
	//	break;

	//case WM_MOUSEMOVE:			// mouse movement
	//	break;

	//case WM_LBUTTONUP:			// left button release
	//	break;

	//case WM_RBUTTONUP:			// right button release
	//	break;

	//case WM_KEYUP:
	//	break;

	//case WM_KEYDOWN:
	//	int fwKeys;
	//	LPARAM keyData;
	//	fwKeys = (int)wParam;    // virtual-key code 
	//	keyData = lParam;          // key data 

	//	switch (fwKeys)
	//	{
	//	case VK_ESCAPE:
	//		PostQuitMessage(0);
	//		break;
	//	default:
	//		break;
	//	}

	//	break;

	//default:
	//	break;
	//}

	if (msg == WM_DESTROY || msg == WM_CLOSE) {
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(handle, msg, wParam, lParam);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Window::Window(HINSTANCE _hInst, int _width, int _height)
{
	SetWindowSize(_width, _height);

	WNDCLASSEX wc = { 0 };

	wc.style = CS_HREDRAW | CS_VREDRAW; // window to be painted either horizontally or vertically
	wc.lpfnWndProc = WndProc; // pointer to the window procedure function to deal w/ the WNDCLASS instance
	wc.cbClsExtra = 0; // extra memory slot for own purpose
	wc.cbWndExtra = 0; // extra memory slot for own purpose
	wc.hInstance = _hInst; // handle application instance
	wc.hIcon = LoadIcon(0, IDI_APPLICATION); // specify a handle to an icon to use for windows created using this struct
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.lpszMenuName = 0; // window's menu, no menu = 0
	wc.lpszClassName = "BasicWndClass"; // specifies name of the window class structure we're creating

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = _hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wc.lpszMenuName = NULL;
	//wc.lpszClassName = WndClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		MessageBox(0, "RegisterClass FAILED", 0, 0);
		exit(0);
	}

	_window = CreateWindow(
		"BasicWndClass", // regiestered WNDCLASS instance to use
		"Win32Basic", // window title
		WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
		CW_USEDEFAULT, // x-coordinate
		CW_USEDEFAULT, // y-coordinate
		_width, // width
		_height, // height
		0,//nullptr, // parent window
		0,//nullptr, // menu handle
		_hInst, // app instance
		0,//nullptr // extra creation parameters
	);
	
	if (_window == 0) {
		MessageBox(0, "CreateWindow FAILED", 0, 0);
		exit(0);
	}

	//hDC = GetDC(_window);

	//if (hDC == S_OK)
	//	MessageBox(_window, "hDC works", "Stuff", 0);

	ShowWindow(_window, SW_SHOW);
	UpdateWindow(_window);
}

Window::~Window()
{
}

HWND Window::GetHandle()
{
	return _window;
}

void Window::SetWindowSize(const int _w, const int _h) {
	_width = _w;
	_height = _h;
}
