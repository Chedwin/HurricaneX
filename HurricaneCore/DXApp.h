//*******************************//
//
// Name:			DXApp.h
// Description:		Establishes a base DirectX 11 application for Hurricane games to derive from.
//					
//
// Author:			Edwin Chen
// Special Thanks:  Daniel Argento, Mark Seaman, Scott Fielder
//
// Created:			Apr 15, 2017
// Last updated:	May 03, 2017
//
//*******************************//


#ifndef _DX_APP_H
#define _DX_APP_H

#include "Macro.h"
#include "DXRenderer.h"
#include "FPSCounter.h"

#define DX11GAME DXApp::GetDXApp()

class DXApp {
protected:
	DXApp();
public:
	virtual ~DXApp();

	static DXApp* GetDXApp();

	int MessageLoop();

	bool InitWindow(HINSTANCE hInstance, int width, int height, bool isFullscreen);
	bool InitRenderer();

	virtual bool InitGame() {
		return true;
	}

	virtual void Update(const float _dt) {}
	virtual void Render(const float _dt) {}

	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	inline int GetWidth() const {
		return _width;
	}
	inline int GetHeight() const {
		return _height;
	}
	inline bool IsFullscreen() const {
		return _isFullScreen;
	}

	inline float GetFPS() const {
		return _fps;
	}

protected:
	static DXApp*		_dxAppInstance;

	DXRenderer*		    _renderer;

	FPSCounter*			_fpsCounter;

	HINSTANCE			_hInstance;
	HWND				_hwnd;
	HINSTANCE			_hAppInstance;
	UINT				_clientWidth, _clientHeight;

	int					_width, _height;
	bool				_isFullScreen;

	STRING				_hAppTitle;
	DWORD				_hWndStyle;
	const LPCTSTR		_className = "HGAME";

	float				_fps;
};


// static declaration of callback window procedure
static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


#endif