//*******************************//
//
// Name:			Component.h
// Description:		Defines a basic component class for different component types.
//					Pure virtual class to be overriden
//
// Author:			Edwin Chen, 
// Spcial Thanks:   Mathieu Violette, James Sholdice, Nathan Senter
//
// Created:			Sep 30, 2016
// Last updated:	Sep 08, 2017
//
//*******************************//


#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "Macro.h"

class GameObject;

enum COMPONENT_TYPE {
	Renderable	= 0, // Mesh
	Light		= 1,
	Rigidbody	= 2,
	Collider	= 3
};

class Component {
public:
	explicit Component(GameObject* g, COMPONENT_TYPE ct);
	virtual ~Component();

	virtual void DestroyComponent() = 0;

	inline void SetEnabled(bool _b) {
		isEnabled = _b;
	}
	inline bool CheckEnabled() const {
		return isEnabled;
	}

public:
	GameObject* parentGmObj;
	COMPONENT_TYPE compType;
	bool isEnabled;
};

#endif