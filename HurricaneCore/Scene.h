//*******************************//
//
// Name:			Scene.h
// Description:		Abstract class definition for a base scene
//					This class is a specialization of the IState interface for the SceneManager class
//					Only scenes deriving from this class can be used by the scene manager
//
// Author:			Edwin Chen
// Special Thanks:	Scott Fielder
//
// Created:			Nov 04, 2017
// Last updated:	Nov 04, 2017
//
//*******************************//

#ifndef _SCENE_H
#define _SCENE_H

#include "Macro.h"
#include "IState.h"

namespace HurricaneEngine 
{
#define HURRICANE_SCENE HurricaneEngine::IState<HurricaneEngine::SceneManager>

	class SceneManager;
	class GameObject;

	class Scene : public HURRICANE_SCENE {
	public:
		Scene() {}
		virtual ~Scene() {}

		virtual void EnterState(SceneManager* owner) = 0;
		virtual void ExitState(SceneManager* owner) = 0;
		virtual void UpdateState(SceneManager* owner, const float _dt) = 0;
		virtual void RenderState(SceneManager* owner) = 0;

	};

#undef HURRICANE_SCENE
}


#endif