//*******************************//
//
// Name:			HMath.h
// Description:		D3D11 Math Library
//
// Author:			Edwin Chen
// Special Thanks:	DirectX 
//
// Created:			Oct 08, 2016
// Last updated:	Nov 04, 2017
//
//*******************************//


#ifndef _HMATH_H
#define _HMATH_H


#include "D3D11Utility.h"

namespace HMath 
{

	typedef DirectX::XMFLOAT3 VEC3;
	typedef DirectX::XMFLOAT2 VEC2;

	typedef DirectX::XMFLOAT4 VEC4;

	typedef DirectX::XMMATRIX MAT4;

	typedef DirectX::XMVECTOR QUATERNION;

	#define PERSPECTIVE_MATRIX	DirectX::XMMatrixPerspectiveFovLH
	#define LOOKAT_MATRIX		DirectX::XMMatrixLookToLH
	#define TRANSPOSE_MATRIX	DirectX::XMMatrixTranspose

}



#endif // _HMATH_H