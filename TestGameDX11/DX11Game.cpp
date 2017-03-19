#include "DX11Game.h"



DX11Game::DX11Game() : Game()
{
	_instance = this;
	triangle = nullptr;
}


DX11Game::~DX11Game()
{
	delete triangle;
	triangle = nullptr;
}

bool DX11Game::InitGame()
{
	triangle = new Triangle(*(this->renderer));
	return true;
}

void DX11Game::GameUpdate(const float _deltaTime)
{
}

void DX11Game::GameRender()
{
	triangle->Draw(*(this->renderer));
}
