#ifndef _GAME_H
#define _GAME_H

#include "Macro.h"
#include "Window.h"
#include "DXRenderer.h"
#include "HProperties.h"

#define GAME Game::GetInstance()

class Game {
protected:
	Game();

	bool InitEngine(HINSTANCE _hInst);
	void DestroySystems();

	virtual bool InitGame() { return true;  }
	virtual void GameUpdate(const float _deltaTime) {}
	virtual void GameRender() {}

	void EngineUpdate(const float _deltaTime);
	void GameLoop();

public:	
	static Game* GetInstance();
	virtual ~Game();
	void Run(HINSTANCE _hInst);


protected:
	static Game* _instance;
	bool _isRunning;
public:
	DXRenderer* renderer;
	Window* gameWindow;
	HProperties* hProps;
};

#endif 