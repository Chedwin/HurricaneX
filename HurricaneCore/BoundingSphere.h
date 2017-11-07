#ifndef _BOUNDING_SPHERE_H
#define _BOUNDING_SPHERE_H

#include "HMath.h"

namespace HMath 
{
	class BoundingSphere {
	protected:
		VEC3 _center;
		float _radius;

	public:
		BoundingSphere() 
			: _center(0.0f, 0.0f, 0.0f), _radius(0.0f) 
		{
			// empty
		}

		explicit BoundingSphere(VEC3 _c, float _r) 
			: _center(_c), _radius(_r)
		{
			// empty
		}

		~BoundingSphere() {}

		inline VEC3 GetCenter() const {
			return _center;
		}
		inline float GetRadius() const {
			return _radius;
		}
	};
}

#endif