//*******************************//
//
// Name:			Window32.h
// Description:		
//					
//
// Author:			Edwin Chen
// Special Thanks:  Scott Fielder
//
// Created:			Apr 20, 2017
// Last updated:	Nov 02, 2017
//
//*******************************//

#ifndef _WINDOW32_H
#define _WINDOW32_H

#include "Macro.h"



namespace HurricaneEngine 
{

#define HX_WIN32_CLASS_NAME "HGAME" // Macro defined string for initializing WIN32 window class

	class IHGame;
	class Window32 {
		friend class IHGame;
	protected:
		Window32() {}
		~Window32();

		bool InitWindow(int _wd, int _hg, bool _fs = false);
		void ExitWindow();
		void SetWindowTitleText(const STRING& _title);

	public:

		inline int Width() const {
			return _width;
		}
		inline int Height() const {
			return _height;
		}
		inline bool IsFullScreen() const {
			return _isFullScreen;
		}

	protected:

		int _width, _height;
		bool _isFullScreen;

		HINSTANCE*			_hInstance;						// Pointer ref to WIN32 HINSTANCE
		HWND				_hwnd;
		UINT				_clientWidth, _clientHeight;
		STRING				_hAppTitle;
		DWORD				_hWndStyle;
		const LPCTSTR		_className = HX_WIN32_CLASS_NAME;

		HDC _hdc;
	};

#undef HX_WIN32_CLASS_NAME

} // end namespace HurricaneEngine

#endif