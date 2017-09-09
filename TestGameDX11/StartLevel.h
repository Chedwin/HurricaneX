#pragma once

#include <HXApp.h>
#include <LevelManager.h>

class StartLevel : public Level {
public:
	float y = 0.0f;
	float ySpeed;

public:
	StartLevel();
	~StartLevel();

	void Render() override;
	void Update() override;
	void Load() override;
	void Unload() override;
};