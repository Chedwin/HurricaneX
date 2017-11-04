//*******************************//
//
// Name:			HMath.h
// Description:		D3D11 Math Library
//
// Author:			Edwin Chen
// Special Thanks:	DirectX 
//
// Created:			Oct 08, 2016
// Last updated:	Nov 03, 2017
//
//*******************************//


#ifndef _HMATH_H
#define _HMATH_H


#include "D3D11Utility.h"


#define VEC3 DirectX::XMFLOAT3 // 3D Vector -> 32 bit float point components
#define VEC2 DirectX::XMFLOAT2
#define VEC4 DirectX::XMFLOAT4

#define MAT4 DirectX::XMMATRIX
#define MAT4_TRANSPOSE DirectX::XMMatrixTranspose

#define PLANE DirectX::XMVECTOR


#define QUATERNION DirectX::XMVECTOR

#define PERSPECTIVE_MATRIX DirectX::XMMatrixPerspectiveFovLH
#define LOOKAT_MATRIX DirectX::XMMatrixLookToLH





#endif // _HMATH_H