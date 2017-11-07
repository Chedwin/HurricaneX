#ifndef _BOUNDING_PLANE_H
#define _BOUNDING_PLANE_H

#include "HMath.h"

namespace HMath 
{
	class BoundingPlane {
	protected:
		VEC4 _repr;
	public:
		BoundingPlane()
		{
			_repr = VEC4(0.0f, 0.0f, 0.0f, 0.0f);
		}
		explicit BoundingPlane(VEC3 normalToPlane, float distanceFromOrigin)
		{
			_repr = VEC4(normalToPlane.x, normalToPlane.y, normalToPlane.z, distanceFromOrigin);
		}

		//VEC3 GetNormal() const 
		//{
		//	using namespace DirectX;
		//	XMVECTOR temp = XMVectorSet(_repr.x, _repr.y, _repr.z, _repr.w);
		//	XMVECTOR temp2;

		//	XMPlaneDotNormal(temp, temp2);
		//}
	};
}

#endif