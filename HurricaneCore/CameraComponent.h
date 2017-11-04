#ifndef _CAMERA_COMPONENT_H
#define _CAMERA_COMPONENT_H

#include "Macro.h"
#include "IComponent.h"
#include "HMath.h"
#include "DXRenderer.h"
#include "GameObject.h"

namespace HurricaneEngine 
{

	class CameraComponent : public IComponent {
	protected:
		DXRenderer* _dxR;

		MAT4 _viewMatrix;
		MAT4 _projMatrix;
		MAT4 _orthoMatrix;

		PLANE  _frustum[6];
	public:
		VEC3 dir, up;

		float pitch;
		float yaw;
		float roll;

		float angle;

		float fieldOfView;
		float farDist;
		float nearDist;
		float width, height;

	public:
		CameraComponent(GameObject* _obj, DXRenderer* _dx);
		~CameraComponent() final;

		bool InitComp() final;
		void DestroyComp() final;
		void UpdateComp(const float _deltaTime) final;
		void RenderComp() final;

		void BuildViewFrustrum();
	};

}


#endif