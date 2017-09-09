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
//					This scripting behaviour was highly influenced by MonoBehavior from Unity
//
// Author:			Edwin Chen
// Special Thanks:	Unity
//
// Created:			Nov 21, 2016
// Last updated:	Sep 09, 2017
//
//*******************************//


#ifndef _GAME_OBJECT_SCRIPT_H
#define _GAME_OBJECT_SCRIPT_H

#include "Macro.h"

class GameObject;

#pragma region class GameObjectScript -> SINGLE game object script

class GameObjectScript {
public:
	explicit GameObjectScript(const STRING& n);
	virtual ~GameObjectScript() = 0;

	virtual bool UpdateScript(GameObject* gameObject, const float _timeStep) = 0;

	inline STRING GetName() {
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

#pragma region class GameObjectMultiScript -> MULTIPLE scripts to be put on a single game object

class GameObjectMultiScript {
public:
	GameObjectMultiScript();
	~GameObjectMultiScript();

	// GET
	template<typename T> T* GetScript() 
	{
		MAP(STRING, GameObjectScript*)::iterator iter = scriptMap.begin();

		for (iter = scriptMap.begin(); iter != scriptMap.end(); iter++)
		{
			// We need to dynamically cast the base class to a derived class
			// NOTES: 
			//		- dynamic_cast<T> performs a runtime check to make sure the cast is valid
			//		- a dynamic cast only works with polymorphic class with at least ONE virtual method
			STRING t1 = typeid(dynamic_cast<T*>(iter->second)).name();
			STRING t2 = typeid(T*).name();

			// Determine if the TYPE names are the same
			if (t1 == t2)
			{
				return dynamic_cast<T*>(iter->second);
			}
		}
		return nullptr;
	}

	void AddScript(GameObjectScript* script);
	void DeleteScript(const STRING& n);
	void ClearAllScripts();

	bool UpdateAllScripts(GameObject* gameObject, const float _timeStep);
public:
	MAP(STRING, GameObjectScript*) scriptMap;
};

#pragma endregion

#endif