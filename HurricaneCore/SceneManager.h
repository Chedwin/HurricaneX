//*******************************//
//
// Name:			SceneManager.h
// Description:		
//
// Author:			Edwin Chen
// Special Thanks:	Scott Fielder
//
// Created:			Nov 03, 2017
// Last updated:	Nov 04, 2017
//
//*******************************//


#ifndef _SCENE_MANAGER_H
#define _SCENE_MANAGER_H

#include "Macro.h"
#include "FiniteStateMachine.h"
#include "Scene.h"


namespace HurricaneEngine 
{
#define SCENE_MANAGER SceneManager::GetInstance()

	class IHGame;

	class SceneManager {
		friend class IHGame;

		friend DEFAULT_DELETE(SceneManager);
		static UNIQUE_PTR(SceneManager) _sceneManager;

	protected:
		FiniteStateMachine<SceneManager>* _sceneFSM;
		Scene* _currentScene = nullptr;

	protected:
		SceneManager();
		~SceneManager();

		void DeleteScenes();
		void AddScene(Scene* _scene);

		void UpdateScene(const float _deltaTime);
		void RenderScene();
		void SetCurrentScene(Scene* _scene);

	public:
		static SceneManager* GetInstance();
		
		void SwitchScene(const STRING& _name);

		inline STRING CurrentSceneName() const {
			return _currentScene->stateName;
		}
	};



}

#endif