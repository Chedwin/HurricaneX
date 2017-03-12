#ifndef _WINDOW_H
#define _WINDOW_H

#include "Macro.h"

class Window {
public:
	Window(HINSTANCE _hInst, int show, int _width, int _height);
	~Window();

	HWND GetHandle() const;

	inline int GetWidth() const {
		return _width;
	}

	inline int GetHeight() const {
		return _height;
	}

	inline float GetAspectRatio() const {
		return _width / _height;
	}

protected:
	HWND _window;
	HINSTANCE _hInst;
	int _width, _height;
};

#endif
