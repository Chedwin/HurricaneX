#pragma once

#include <Macro.h>
#include <Game.h>
#include "Triangle.h"

class DX11Game : public Game {
public:
	DX11Game();
	~DX11Game();

	bool InitGame() override;

	void GameUpdate(const float _deltaTime) override;
	void GameRender() override;

public:
	Triangle* triangle;
};

