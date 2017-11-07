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


#ifndef _FRUSTUM_H
#define _FRUSTUM_H

#include "HMath.h"

namespace HMath 
{
	class Frustum {
	public:
		Frustum();
		~Frustum();


		Frustum(const MAT4& ProjectionMatrix);

		enum CornerID
		{
			kNearLowerLeft, kNearUpperLeft, kNearLowerRight, kNearUpperRight,
			kFarLowerLeft, kFarUpperLeft, kFarLowerRight, kFarUpperRight
		};

		enum PlaneID
		{
			kNearPlane, kFarPlane, kLeftPlane, kRightPlane, kTopPlane, kBottomPlane
		};
	};

}

#endif