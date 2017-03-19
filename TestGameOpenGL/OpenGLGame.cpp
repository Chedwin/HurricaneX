#include "OpenGLGame.h"
#include <glew.h>


OpenGLGame::OpenGLGame()
{
	_instance = this;
}


OpenGLGame::~OpenGLGame()
{

}

bool OpenGLGame::InitGame()
{
	return true;
}

void OpenGLGame::GameUpdate(const float _deltaTime)
{
}

void OpenGLGame::GameRender()
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glEnd();
}