//*******************************//
//
// Name:			Transform.h
// Description:		Basic transform struture to define position, scale, and rotation.
//					Very similar to Unity transform design.
//
// Author:			Edwin Chen
// Special Thanks:  Unity
//
// Created:			Nov 07, 2016
// Last updated:	Jun 09, 2017
//
//*******************************//


#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "HMath.h"


struct Transform
{
	VEC3		pos;
	VEC3		scale;
	VEC3		rotation;

	// Position
	void SetPosition(float x, float y, float z) {
		pos.x = x;
		pos.y = y;
		pos.z = z;
	}
	void SetPosition(VEC3& _pos) {
		pos = _pos;
	}


	// Scale
	void SetScale(float x, float y, float z) {
		scale.x = x;
		scale.y = y;
		scale.z = z;
	}
	void SetScale(VEC3& _sc) {
		scale = _sc;
	}

	inline void SetRotation(float x, float y, float z) {
		rotation.x = x;
		rotation.y = y;
		rotation.z = z;
	}
	void SetRotation(VEC3& _rot) {
		rotation = _rot;
	}

};


#endif