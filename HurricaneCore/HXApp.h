//*******************************//
//
// Name:			HXApp.h
// Description:		Establishes a base DirectX 11 or OpenGL application for Hurricane games to derive from.
//					
//
// Author:			Edwin Chen
// Special Thanks:  Daniel Argento, Mark Seaman, Scott Fielder
//
// Created:			Apr 15, 2017
// Last updated:	Sep 09, 2017
//
//*******************************//


#ifndef _HX_APP_H
#define _HX_APP_H

#include "Macro.h"
#include "FPSCounter.h"
#include "GameTimer.h"
#include "Graphics.h"

#define HXGAME HXApp::GetHXApp()	// Shortcut to static GAME instance

#define HX_WIN32_CLASS_NAME "HGAME" // Macro defined string for initializing WIN32 window class

class HXApp {
protected:
	HXApp();

	bool InitWindow(int width, int height, bool isFullscreen = false, HINSTANCE hInstance = NULL);
	bool InitGraphics();
	void ShutdownEngine();
	void GameLoop();
public:
	virtual ~HXApp();

	HXApp(const HXApp&) = delete;

	static HXApp* GetHXApp();

	int MessageLoop();

	// Helper function
	//bool InitEngine(HINSTANCE hInstance, int width, int height, bool isFullscreen = false);
	bool InitEngine(int width, int height, bool isFullscreen = false, HINSTANCE hInstance = NULL);

	// To be override by the main game
	virtual bool InitGame() { return true; }
	virtual void Update(const float _dt) { return; }
	virtual void Render(const float _dt) { return; }

	void CalculateFrameStats();

	// Message Loop for Win32 class
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

#pragma region INLINE FUNCTIONS
	// Inline getters

	inline int GetWidth() const {
		return _width;
	}
	inline int GetHeight() const {
		return _height;
	}
	inline float GetAspectRatio() const {
		return (float)(_width / _height);
	}
	inline bool IsFullscreen() const {
		return _isFullScreen;
	}

	inline float GetFPS() const {
		return _fps;
	}

	inline float GetDeltaTime() const {
		return _deltaTime;
	}

	inline Graphics* GetGraphics() const {
		return _graphics;
	}

	inline HWND GetHWND() const {
		return _hwnd;
	}

#pragma endregion

	// Pointer references
protected:
	static HXApp*		_hXAppInstance;		// Global static instance for entire GAME instance
	Graphics*			_graphics;
	FPSCounter*			_fpsCounter;		// Reference to FPS counter instance

	// Win32 
protected:
	HINSTANCE*			_hInstance;						// Pointer ref to WIN32 HINSTANCE
	HWND				_hwnd;
	UINT				_clientWidth, _clientHeight;
	STRING				_hAppTitle;
	DWORD				_hWndStyle;
	const LPCTSTR		_className = HX_WIN32_CLASS_NAME;

	HDC					_hdc; // device context


	// System settings
protected:
	int					_width, _height;
	bool				_isFullScreen;
	float				_fps;
	float				_deltaTime, _lastUpdateTime, _timeSinceLastUpdate;
	STRING				_mainWndCaption;
public:
	GameTimer			timer;
};

#endif