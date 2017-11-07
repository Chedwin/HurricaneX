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

		HMath::MAT4 _viewMatrix;
		HMath::MAT4 _projMatrix;
		HMath::MAT4 _orthoMatrix;


	public:
		HMath::VEC3 dir, up;

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
	};

}


#endif