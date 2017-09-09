#pragma once

#include <HXApp.h>
#include "Triangle.h"

class DirectXTestGame : public HXApp {
public:
	DirectXTestGame();
	~DirectXTestGame() final;


	bool InitGame() override;

	void Update(const float _dt) override;
	void Render(const float _dt) override;

public:
	Triangle* triangle;
};