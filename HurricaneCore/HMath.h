//*******************************//
//
// Name:			HMath.h
// Description:		
//
// Author:			Edwin Chen
// Special Thanks:	DirectX, GLM
//
// Created:			Oct 08, 2016
// Last updated:	Sep 07, 2017
//
//*******************************//


#ifndef _HMATH_H
#define _HMATH_H

#include "Macro.h"


// If HURRICANE_OPENGL is defined then we're using GLM MATH
#ifdef HURRICANE_OPENGL

	#include <glm.hpp>
	#include <gtc/matrix_transform.hpp>
	#include <gtc/quaternion.hpp>
	#include <gtx/quaternion.hpp>
	#include <gtx/euler_angles.hpp>
	#include <gtx/norm.hpp>


	// LET'S MACRO DEFINE SOME GLM TERMS

	// Vector2
	#define VEC2 glm::vec2

	// Vector3
	#define VEC3 glm::vec3
	#define ORIGIN glm::vec3(0.0f, 0.0f, 0.0f)
	#define BASIS3X glm::vec3(1.0f, 0.0f, 0.0f)
	#define BASIS3Y glm::vec3(0.0f, 1.0f, 0.0f)
	#define BASIS3Z glm::vec3(1.0f, 0.0f, 1.0f)

	// Vector4
	#define VEC4 glm::vec4

	// Matrices
	#define MAT3 glm::mat3
	#define MAT4 glm::mat4
	#define MAT4_ID glm::mat4(1.0f)

	// Quaternions
	#define QUATERNION glm::quat


#else // ELSE - HURRICANE IS USING DIRECTX MATH

	#include "d3dUtil.h"


	#define VEC3 DirectX::XMFLOAT3 // 3D Vector -> 32 bit float point components
	#define VEC2 DirectX::XMFLOAT2
	#define VEC4 DirectX::XMFLOAT4

	#define MAT4 DirectX::XMMATRIX

	#define QUATERNION DirectX::XMVECTOR

	#define PERSPECTIVE_MATRIX DirectX::XMMatrixPerspectiveFovLH
	#define LOOKAT_MATRIX DirectX::XMMatrixLookAtLH


#endif // HURRICANE_OPENGL




#endif // _HMATH_H