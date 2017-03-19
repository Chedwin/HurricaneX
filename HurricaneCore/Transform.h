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
// Last updated:	Mar 18, 2017
//
//*******************************//


#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "HMath.h"

// NOTE: If HURRICANE_OPENGL is defined, VEC3 and QUATERNION will use GLM
//		 or else use DirectX Math

struct Transform
{
	VEC3 position;
	VEC3 scale;
	//QUATERNION rotation;
};


#endif