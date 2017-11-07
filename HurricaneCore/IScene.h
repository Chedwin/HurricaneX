//*******************************//
//
// Name:			IScene.h
// Description:		Abstract class definition for a base scene
//					This class is a specialization of the template IState interface for the SceneManager class
//					Only scenes deriving from this class can be used by the scene manager
//
// Author:			Edwin Chen
// Special Thanks:	Scott Fielder
//
// Created:			Nov 04, 2017
// Last updated:	Nov 06, 2017
//
//*******************************//

#ifndef _SCENE_H
#define _SCENE_H

#include "Macro.h"
#include "GameObject.h"
#include "IState.h"

namespace HurricaneEngine 
{
#define HURRICANE_SCENE IState<SceneManager>

	class SceneManager;

	class IScene : public HURRICANE_SCENE {
		friend class SceneManager;

	protected:
		void SetSceneName(const STRING& _n)	 { _stateName = _n; }
		void SetSceneIndex(unsigned int _id) { _sceneIndex = _id; }
	public:
		explicit IScene(const STRING& _name) { SetSceneName(_name); }
		virtual ~IScene() {}

		virtual void EnterState(SceneManager* owner) = 0;
		virtual void ExitState(SceneManager* owner) = 0;
		virtual void UpdateState(SceneManager* owner, const float _dt) = 0;
		virtual void RenderState(SceneManager* owner) = 0;

	private:
		unsigned int _sceneIndex;
	protected:
		// TODO: ADD SCENE GRAPH

	};

#undef HURRICANE_SCENE
}


#endif