#include "CameraComponent.h"
#include "GameObject.h"

using namespace HurricaneEngine;

CameraComponent::CameraComponent(GameObject* _obj, DXRenderer* _dx)
	: IComponent(_obj)
{
	_dxR = _dx;
}


CameraComponent::~CameraComponent()
{
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

void CameraComponent::BuildViewFrustrum() 
{
	//MAT4 viewProjection = _viewMatrix * _projMatrix;

	////D3DXMatrixMultiply( &viewProjection, &m_mView, &m_mProjection );
	//// Left plane
	//_frustum[0].a = viewProjection._14 + viewProjection._11;
	//_frustum[0].b = viewProjection._24 + viewProjection._21;
	//_frustum[0].c = viewProjection._34 + viewProjection._31;
	//_frustum[0].d = viewProjection._44 + viewProjection._41;

	//// Right plane
	//_frustum[1].a = viewProjection._14 - viewProjection._11;
	//_frustum[1].b = viewProjection._24 - viewProjection._21;
	//_frustum[1].c = viewProjection._34 - viewProjection._31;
	//_frustum[1].d = viewProjection._44 - viewProjection._41;

	//// Top plane
	//_frustum[2].a = viewProjection._14 - viewProjection._12;
	//_frustum[2].b = viewProjection._24 - viewProjection._22;
	//_frustum[2].c = viewProjection._34 - viewProjection._32;
	//_frustum[2].d = viewProjection._44 - viewProjection._42;

	//// Bottom plane
	//_frustum[3].a = viewProjection._14 + viewProjection._12;
	//_frustum[3].b = viewProjection._24 + viewProjection._22;
	//_frustum[3].c = viewProjection._34 + viewProjection._32;
	//_frustum[3].d = viewProjection._44 + viewProjection._42;

	//// Near plane
	//_frustum[4].a = viewProjection._13;
	//_frustum[4].b = viewProjection._23;
	//_frustum[4].c = viewProjection._33;
	//_frustum[4].d = viewProjection._43;

	//// Far plane
	//_frustum[5].a = viewProjection._14 - viewProjection._13;
	//_frustum[5].b = viewProjection._24 - viewProjection._23;
	//_frustum[5].c = viewProjection._34 - viewProjection._33;
	//_frustum[5].d = viewProjection._44 - viewProjection._43;

	//// Normalize planes
	//for (int i = 0; i < 6; i++)
	//{
	//	D3DXPlaneNormalize(&_frustum[i], &_frustum[i]);
	//}

}