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
// Last updated:	Nov 04, 2017
//
//*******************************//


#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H


#include "Macro.h"
#include "Debugger.h"
#include "Transform.h"
#include "IComponent.h"
#include "GameObjectScript.h"



// forward declare 

namespace HurricaneEngine 
{

	#define DEFAULT_GAMEOBJECT_NAME "GameObject"

	class IScene;

	class GameObject {
	protected:
		STRING	_name;
		bool	_isEnabled = false;

		// Scripting behaviour
		// Allows for multiple scripts to be attached to this game object
		GameObjectMultiScript* _scripts;


		VECTOR(STRING)			_tags;
		VECTOR(GameObject*)		_childObjects;
		VECTOR(IComponent*)		_componentList;

	public:
		// Pointer to itself (Unity-like)
		GameObject* gameObject;

		// Transform fields
		HMath::Transform transform;

		// Which scene am I in?


	public:
		//explicit GameObject(Scene& sc, const STRING& name = ""); // not in use here

		// CONSTRUCTORS & DESTRUCTORS
		explicit GameObject(const STRING& _name = DEFAULT_GAMEOBJECT_NAME);
		virtual ~GameObject();

		GameObject() = delete; // no default constructor
		GameObject(const GameObject&);



		// VIRTUAL GAME SUBROUTINES
		// "CAN" BE OVERRIDEN BY DERIVED CLASSES
		virtual bool Init();
		virtual void Destroy();

		virtual void Update(const float _deltaTime);
		virtual void PreRender();
		virtual void Render();



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
		void AddComponent(IComponent* c);
		void RemoveComponents();

		// SCRIPTS
		void AddScript(GameObjectScript* _script);
		void RemoveScripts();

	#pragma region TEMPLATE SUBROUTINES

		// GET COMPONENT() template function
		// i.e. similiar to Unity;
		template<typename TYPE> TYPE* GetComponent()
		{
			STRING t1 = typeid(TYPE*).name(); // name of the type provided by the USER

			for (int i = 0; i < _componentList.size(); i++)
			{
				// We need to dynamically cast the base class to a derived class
				// NOTES: 
				//		- dynamic_cast<T> performs a runtime check to make sure the cast is valid
				//		- a dynamic cast only works with polymorphic class with at least ONE virtual method
				STRING t2 = typeid(dynamic_cast<TYPE*>(_componentList[i])).name(); // name of the type in the component list

				// Determine if the TYPE names are the same
				if (t1 == t2)
					return dynamic_cast<TYPE*>(_componentList[i]);

			}
			Debugger::Error(gameObject->GetName() + " failed to GetComponent() for: " + t1);
			return nullptr;
		}

		// GET SCRIPT() by template
		template<typename T> T* GetScript()
		{
			//static_assert(dynamic_cast<IComponent>, "Needs to derive from IComponent");
			static_assert((IComponent const*)&T, "Needs to derive from IComponent");

			T* temp = _scripts->GetScript<T>();
			STRING t1 = typeid(T*).name();

			if (!temp)
				Debugger::Error("GameObject: \"" + gameObject->GetName() + "\" failed to GetScript() for: " + t1);

			return temp;
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

} // end namespace HurricaneEngine

#endif