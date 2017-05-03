#include "DirectXTestGame.h"



DirectXTestGame::DirectXTestGame() 
	: DXApp(), triangle(nullptr)
{
	_dxAppInstance = this;
}


DirectXTestGame::~DirectXTestGame()
{
	if (triangle)
		delete triangle;

	triangle = nullptr;
}


bool DirectXTestGame::InitGame()
{
	triangle = nullptr;
	triangle = new Triangle();

	if (!triangle->InitTriangle(*this->_renderer)) 
	{
		MessageBox(NULL, "Triangle initialization FAILED", "FATAL ERROR", 0);
		return false;
	}

	return true;
}

void DirectXTestGame::Render(const float _dt)
{
	triangle->Render();
}