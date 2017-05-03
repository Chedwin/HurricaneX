#include "Camera.h"
//#include "HurricaneProperties.h"
//#include "ShaderProgram.h"
//#include "StandardShader.h"
//#include "InputHandler.h"
//#include "Game.h"

// CONSTRUCTOR(S) / DESTRUCTOR

Camera::Camera(Scene& sc) : GameObject(sc)
{
	gameObject = this;
	AddTag("Camera");
}


Camera::~Camera()
{
	// EMPTY
}


///////////////////////////////////////////////////////////////////////////////////////////////////////

void Camera::Update(const float _deltaTime)
{
	// Empty
}

void Camera::Render()
{

}