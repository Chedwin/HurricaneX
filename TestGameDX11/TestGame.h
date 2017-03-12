#pragma once

#include <Macro.h>
#include <Game.h>

class TestGame : public Game {
public:
	TestGame();
	~TestGame();

	bool InitGame() override;

	void GameUpdate(const float _deltaTime) override;
	void GameRender() override;
};

