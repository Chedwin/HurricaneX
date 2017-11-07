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
#include "IScene.h"


#define SCENE_MANAGER SceneManager::GetInstance()


namespace HurricaneEngine 
{
	class IHGame;

	class SceneManager {
		friend class IHGame;
		friend DEFAULT_DELETE(SceneManager);

	protected:
		static UNIQUE_PTR(SceneManager) _sceneManager;
		FiniteStateMachine<SceneManager>* _sceneFSM;
		IScene* _currentScene = nullptr;

	protected:
		SceneManager();
		~SceneManager();

		void DeleteScenes();
		void AddScene(IScene* _scene);

		void UpdateScene(const float _deltaTime);
		void RenderScene();
		void SetCurrentScene(IScene* _scene);

	public:
		static SceneManager* GetInstance();
		
		void SwitchScene(const STRING& _name);
		void SwitchScene(unsigned int _index);

		STRING CurrentSceneName() const;
		int CurrentSceneIndex() const; // returns -1 if null
	};



} // end namespace HurricaneEngine

#endif