#include "CameraComponent.h"
#include "GameObject.h"

using namespace HMath;
using namespace HurricaneEngine;

CameraComponent::CameraComponent(GameObject* _obj, DXRenderer* _dx)
	: IComponent(_obj) , _dxR(_dx)
{
	// empty
}


CameraComponent::~CameraComponent()
{
	// empty
}



bool CameraComponent::InitComp()
{
	_ownerObj->transform.SetPosition(VEC3(0.0, 1.0f, 0.0f));
	_ownerObj->transform.SetRotation(VEC3(0.0f, 0.0f, 0.0f));

	//_projMatrix = PERSPECTIVE_MATRIX(45.0f, _dxR->_width / _dxR->height, 0.1f, 10.0f); // hard coded for now

	return true;
}

void CameraComponent::DestroyComp()
{
}

void CameraComponent::UpdateComp(const float _deltaTime)
{
}

void CameraComponent::RenderComp()
{
}	 