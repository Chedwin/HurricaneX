#ifndef _WINDOW_H
#define _WINDOW_H

#include "Macro.h"

class Window {
	friend class Game;
protected:
	Window(HINSTANCE _hInst, int _width, int _height);
public:
	~Window();

	HWND GetHandle();
	void SetWindowSize(const int _w, const int _h);

	inline int GetWidth() const {
		return _width;
	}

	inline int GetHeight() const {
		return _height;
	}

	inline float GetAspectRatio() const {
		return (float)_width / _height;
	}


protected:
	HWND _window;
	HINSTANCE _hInst;
	int _width, _height;
public:
	//static HDC hDC;
};

#endif
