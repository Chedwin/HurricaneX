

#ifndef _LEVELMANAGER_H
#define _LEVELMANAGER_H

#include "Level.h"

class LevelManager {
private:
	static Level* _currentLevel;
public:
	static bool _loading;

protected:
	LevelManager() {}
public:
	~LevelManager() {}

	static void Init();

	static void LoadInitialLevel(Level* lvl);
	static void SwitchLevel(Level* lvl);

	static void Update();
	static void Render();
};

#endif