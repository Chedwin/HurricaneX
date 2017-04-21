#include "DirectXTestGame.h"



DirectXTestGame::DirectXTestGame() : DXApp()
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

	if (!triangle->InitTriangle(*this->_dxRenderer)) {
		return false;
	}

	return true;
}

void DirectXTestGame::Render(const float _dt)
{
	triangle->Render();
}