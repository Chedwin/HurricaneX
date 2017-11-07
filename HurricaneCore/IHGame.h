//*******************************//
//
// Name:			IHGame.h
// Description:		Abstract base DirectX 11 for Hurricane games to derive from.
//					
//
// Author:			Edwin Chen
// Special Thanks:  Daniel Argento, Mark Seaman, Scott Fielder
//
// Created:			Apr 15, 2017
// Last updated:	Nov 06, 2017
//
//*******************************//

#ifndef _IHGAME_H
#define _IHGAME_H

#include "Macro.h"
#include "GameTimer.h"
#include "Window32.h"
#include "DXRenderer.h"

#include "InputManager.h"
#include "SceneManager.h"
#include "FPSCounter.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 768


namespace HurricaneEngine 
{

	class IHGame {
	protected:
		IHGame();
		IHGame(const IHGame&) = delete;
		virtual ~IHGame();

		// Destroy all engine systems 
		void Exit();

		// Init all necessary engine systems
		bool InitEngine();

		virtual bool InitGame() = 0;
		virtual void OnExit() = 0;

		// For adding all scenes
		// Using this method here ensures perfect encapsulation of SceneManager subroutines
		// i.e. Only IHGame class and derived game classes can add, delete, render, update scenes in the SceneManager
		//		 then other classes can only use SwitchScenes(), GetSceneIndex(), etc.
		void AddScene(IScene* _scene);

		// GameLoop function to organize order of Update and Render calls
		void GameLoop();


		virtual void Update(const float _deltaTime);
		void Render(); // Render() most likely does not "need" to be overriden

	public:

		int Run();

		static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		// Set the title of the window bar
		void SetWindowTitle(const STRING& _string);


		// INLINE Functions
		inline int FPS() const {
			return _fps;
		}
		inline bool IsRunning() const {
			return _isRunning;
		}
		inline DXRenderer* DXR() const { 
			return _dxRenderer; 
		}

	protected:
		bool _isRunning;
		int _fps;

		GameTimer		_timer;
		InputManager*	_input;
		SceneManager*	_sceneManager;
		Window32*		_window;
		DXRenderer*		_dxRenderer;
		FPSCounter*		_fpsCounter;
	};

} // end namespace Hurricane

#endif