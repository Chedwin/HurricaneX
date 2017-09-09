#include "LevelManager.h"

Level* LevelManager::_currentLevel = nullptr;
bool   LevelManager::_loading = true;

////////////////////////////////////////////////////////////////////////////////////////////////////

void LevelManager::Init() {
	_loading = true;
	_currentLevel = nullptr;
}

void LevelManager::LoadInitialLevel(Level* lvl) {
	_loading = true;
	_currentLevel = lvl;
	_currentLevel->Load();
	_loading = false;
}

void LevelManager::SwitchLevel(Level * lvl) {
	_loading = true;
	_currentLevel->Unload();
	lvl->Load();
	delete _currentLevel;
	_currentLevel = lvl;
	_loading = false;
}

void LevelManager::Update() {
	if (_loading)
		return;

	_currentLevel->Update();
}

void LevelManager::Render() {
	if (_loading)
		return;

	_currentLevel->Render();
}