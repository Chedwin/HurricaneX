//*******************************//
//
// Name:			GameObjectScript.h
// Description:		Allows a way for game objects to implement and execute individual behaviours.
//					To create a new script:
//						1) Create a new class deriving from GameObjectScript 
//							(i.e. class PlayerMovement : public GameObjectScript)
//						2) Override the UpdateScript() function
//						3) Add in any "initial" of starting behaviours in your child class constructor
//						4) Add any new functions and called them appropriately in your UpdateScript function
//						5) Instantiate a script inside of a game scene's constructor or init function
//						6) Attach said script to a game object
//
//					This scripting behaviour was highly influenced by "MonoBehavior" from Unity
//
// Author:			Edwin Chen
// Special Thanks:	Unity
//
// Created:			Nov 21, 2016
// Last updated:	Nov 03, 2017
//
//*******************************//


#ifndef _GAME_OBJECT_SCRIPT_H
#define _GAME_OBJECT_SCRIPT_H

#include "Macro.h"


namespace HurricaneEngine 
{

	class GameObject;
	#pragma region class GameObjectScript -> SINGLE game object script

	// NOTE: GameObjectScript is ABSTRACT
	// You MUST derive a class from this base to make custom behavior scripts
	class GameObjectScript {
	public:
		explicit GameObjectScript(const STRING& n);
		virtual ~GameObjectScript() = 0;

		virtual bool UpdateScript(GameObject* gameObject, const float _timeStep);

		inline STRING GetName() const {
			return _scriptName;
		}
		inline void SetName(const STRING& n) {
			_scriptName = n;
		}

	protected:
		STRING _scriptName;
	public:
		typedef FUNCTION(bool(GameObject*, float)) ScriptLambda;
		ScriptLambda		userUpdateFunction = nullptr;
	};

	#pragma endregion 

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	#pragma region class GameObjectMultiScript -> single object to hold MULTIPLE scripts to be put on a ONE game object

	// To be used ONLY by class GameObject

	class GameObjectMultiScript {
		friend class GameObject;
	protected:
		MAP(STRING, GameObjectScript*) scriptMap;
		GameObject* gmOb; // reference to GameObject this multiscript is attached to

	protected:
		explicit GameObjectMultiScript(GameObject& _gm);

		GameObjectMultiScript() = delete;
		GameObjectMultiScript(const GameObjectMultiScript&) = delete;

		// GET SCRIPT() by type
		// There could be thousands of custom made scripts available
		// Hurricane needs to be able to get any ADT script made for convinence 
		template<typename T> T* GetScript()
		{
			MAP(STRING, GameObjectScript*)::iterator iter = scriptMap.begin();

			STRING t1 = typeid(T*).name();
			for (iter = scriptMap.begin(); iter != scriptMap.end(); iter++)
			{
				// We need to dynamically cast the base class to a derived class
				// NOTES: 
				//		- dynamic_cast<T> performs a runtime check to make sure the cast is valid
				//		- a dynamic cast only works with polymorphic class with at least ONE virtual method
				STRING t2 = typeid(dynamic_cast<T*>(iter->second)).name();

				// Determine if the TYPE names are the same
				if (t1 == t2)
					return dynamic_cast<T*>(iter->second);

			}
			return nullptr;
		}

		void AddScript(GameObjectScript* script);
		void DeleteScript(const STRING& n);
		void ClearAllScripts();

		bool UpdateAllScripts(GameObject* gameObject, const float _timeStep);

	public:
		~GameObjectMultiScript();
	};

#pragma endregion

} // end namespace HurricaneEngine

#endif