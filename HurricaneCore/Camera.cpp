#include "Camera.h"
#include "HXApp.h"

Camera::Camera(ID3D11Device& _dev, const STRING& camName) 
	: GameObject(camName), camera(this)
{
	InitCamera(_dev);
	AddTag("Camera");
}

Camera::~Camera()
{

}

///////////////////////////////////////////////////////////////////////////////////////////

void Camera::InitCamera(ID3D11Device& _device) 
{
	SetDXDevice(_device);
	transform.SetPosition(VEC3(0.0, 1.0f, 0.0f));
	transform.SetRotation(VEC3(0.0f, 0.0f, 0.0f));

}

void Camera::Update(const float _deltaTime)
{
}

void Camera::Render()
{
	projMatrix = PERSPECTIVE_MATRIX(45.0f, HXGAME->GetWidth() / HXGAME->GetHeight(), 0.1f, 100.0f); // hard coded for now
	
	//_viewMatrix = glm::lookAt(gameObject->transform.position, gameObject->transform.position + _dir, _up);
	VEC3 camPos = camera->transform.pos;
	//viewMatrix = LOOKAT_MATRIX(camPos, camPos + dir, up);
}