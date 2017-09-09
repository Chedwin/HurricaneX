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
// Last updated:	Sep 09, 2017
//
//*******************************//


#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H


#include "Macro.h"
#include "Transform.h"
#include "Component.h"
#include "GameObjectScript.h"

// forward declare 
class Scene;

#define DEFAULT_GAMEOBJECT_NAME "GameObject"

class GameObject {
protected:
	STRING	_name;
	bool	_isEnabled = false;

	// Scripting behaviour
	// Allows for multiple scripts to be attached to this game object
	GameObjectMultiScript* scripts;
public:
	VECTOR(STRING)			tags;
	VECTOR(GameObject*)		childObjects;
	VECTOR(Component*)		componentList;

	// Pointer to itself (Unity-like)
	GameObject* gameObject;

	// Transform fields
	Transform transform;


	// Which scene am I in?
	Scene* scene;

public:
	//explicit GameObject(Scene& sc, const STRING& name = ""); // not in use here

	// CONSTRUCTORS & DESTRUCTORS
	explicit GameObject(const STRING& name = "");
	virtual ~GameObject();

	GameObject() = delete; // no default constructor
	GameObject(const GameObject&);

	void InitGameObject(const STRING& name = "");


	// VIRTUAL GAME SUBROUTINES
	// "CAN" BE OVERRIDEN BY DERIVED CLASSES
	virtual void Update(const float _deltaTime);
	virtual void PreRender(const float _deltaTime);
	virtual void Render(const float _deltaTime);



	// CHILD OBEJCTS
	void AddChild(GameObject& g);
	void RemoveChild(GameObject& g);
	void RemoveChild(const STRING& n);
	void ClearAllChildren();
	GameObject* GetChild(const STRING& name);


	// Tags
	void AddTag(const STRING& _tag);
	bool HasTag(const STRING& _tag);
	void RemoveTag(const STRING& _tag);


	// COMPONENTS
	void AddComponent(Component* c);
	bool HasComponent(Component* c);
	void DestroyComponents();

	// SCRIPTS
	void DestroyScripts();
	void AddScript(GameObjectScript* _script);

#pragma region TEMPLATED SUBROUTINES

	// GETCOMPONENT template function
	// i.e. similiar to Unity;
	template<typename TYPE> TYPE* GetComponent() 
	{
		for (int i = 0; i < componentList.size(); i++)
		{
			// We need to dynamically cast the base class to a derived class
			// NOTES: 
			//		- dynamic_cast<T> performs a runtime check to make sure the cast is valid
			//		- a dynamic cast only works with polymorphic class with at least ONE virtual method
			STRING t1 = typeid(dynamic_cast<TYPE*>(componentList[i])).name();
			STRING t2 = typeid(TYPE*).name();

			// Determine if the TYPE names are the same
			if (t1 == t2)
			{
				return dynamic_cast<TYPE*>(componentList[i]);
			}
		}
		return nullptr;
	}
	
	// GET script by template
	template<typename T> T* GetScript() 
	{
		return scripts->GetScript<T>();
	}

#pragma endregion 


#pragma region INLINE 
	// helper functions
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
#pragma endregion

}; // end class GameObject

#endif