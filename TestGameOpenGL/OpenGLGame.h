#pragma once

#include <Macro.h>
#include <Game.h>

class OpenGLGame : public Game {
public:
	OpenGLGame();
	~OpenGLGame();

	bool InitGame() override;

	void GameUpdate(const float _deltaTime) override;
	void GameRender() override;
};