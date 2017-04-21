#pragma once

#include <DXApp.h>
#include "Triangle.h"

class DirectXTestGame : public DXApp
{
public:
	DirectXTestGame();
	~DirectXTestGame();


	bool InitGame() override;

	void Render(const float _dt) override;

public:
	Triangle* triangle;
};