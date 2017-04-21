//*******************************//
//
// Name:			GameObject.h
// Description:		Basic definition and implemenetation for a base game object.
//					Note that it is possible to have an empty game object that can still interact with the game world.
//					Components attached to them affect their behaviour in the game.	
//					i.e. Very similiar to Unity's design
//
// Author:			Edwin Chen
// Special Thanks:  Mathieu Violette, James Sholdice, Nathan Senter, Unity, Aiden Dearing, House Yokeswaran, Mark Seaman
//
// Created:			Sep 30, 2016
// Last updated:	Mar 25, 2017
//
//*******************************//


#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H


#include "Macro.h"
#include "Transform.h"
#include "GameObjectScript.h"

// forward declare 
class Scene;

class GameObject {
public:
	explicit GameObject(Scene& sc, const STRING& name = "");
	virtual ~GameObject();

	// "CAN" BE OVERRIDEN BY DERIVED CLASSES
	virtual void Update(const float _deltaTime);
	virtual void PreRender();
	virtual void Render();


	// Child objects
	void AddChild(GameObject& g);
	void RemoveChild(GameObject& g);
	void RemoveChild(const STRING& n);
	void ClearAllChildren();
	GameObject* GetChild(const STRING& name);

	// Tags
	void AddTag(const STRING& _tag);
	bool HasTag(const STRING& _tag);
	void RemoveTag(const STRING& _tag);


	// Inline helper functions
	inline bool CheckEnabled() const {
		return _isEnabled;
	}
	inline void SetEnabled(bool _b) {
		_isEnabled = _b;
	}

	inline STRING GetName() const {
		return _name;
	}
	inline void SetName(const STRING& n) {
		_name = n;
	}

protected:
	STRING _name;
	bool _isEnabled = false;
public:
	VECTOR(STRING) tags;
	VECTOR(GameObject*) childObjects;

	// Pointer to itself (Unity-like)
	GameObject* gameObject;

	// Transform fields
	Transform transform;

	// Scripting behaviour
	// Allows for multiple scripts to be attached to this game object
	GameObjectMultiScript* scripts;

	// Which scene am I in?
	Scene* scene;
};


#endif