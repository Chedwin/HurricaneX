#include "DirectXTestGame.h"
#include "Debug.h"

#include <LevelManager.h>
#include "StartLevel.h"

DirectXTestGame::DirectXTestGame() 
	: HXApp(), triangle(nullptr)
{
	_hXAppInstance = this;
}


DirectXTestGame::~DirectXTestGame() {

}


bool DirectXTestGame::InitGame() {

	LevelManager::LoadInitialLevel(new StartLevel());
	Debug::ConsoleLog("Test Game has been successfully initializd!");
	return true;
}


void DirectXTestGame::Update(const float _dt) {
	LevelManager::Update();
}

void DirectXTestGame::Render(const float _dt) {
	LevelManager::Render();
}