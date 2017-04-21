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
// Last updated:	Apr 20, 2017
//
//*******************************//


#ifndef _DX_APP_H
#define _DX_APP_H

#include "Macro.h"
#include "DXRenderer.h"

#define DX11GAME DXApp::GetDXApp()

class DXApp {
protected:
	DXApp();
public:
	virtual ~DXApp();

	static DXApp* GetDXApp();

	int MessageLoop();

	bool InitWindow(HINSTANCE hInstance, int width, int height, bool windowed);
	bool InitRenderer(HINSTANCE hInstance);

	virtual bool InitGame() {
		return true;
	}

	virtual void Update(const float _dt) {}
	virtual void Render(const float _dt) {}

	inline int GetWidth() const {
		return _width;
	}

	inline int GetHeight() const {
		return _height;
	}

protected:
	static DXApp*		_dxAppInstance;

	DXRenderer*			_dxRenderer;

	HINSTANCE			_hInstance;
	HWND				_hwnd;
	HINSTANCE			_hAppInstance;
	UINT				_hClientWidth, _hClientHeight;

	int					_width, _height;

	STRING				_hAppTitle;
	DWORD				_hWndStyle;
	const LPCTSTR		_className = "HGAME";
};



#endif

