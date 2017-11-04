#pragma once

#include <Macro.h>
#include <Scene.h>
#include <SceneManager.h>
#include "Triangle.h"

class MainMenuScene : public HurricaneEngine::Scene {
public:
	MainMenuScene();
	~MainMenuScene();
	
	void EnterState(HurricaneEngine::SceneManager* owner) override;
	void ExitState(HurricaneEngine::SceneManager* owner) override;
	void UpdateState(HurricaneEngine::SceneManager* owner, const float _dt) override;
	void RenderState(HurricaneEngine::SceneManager* owner) override;

public:
	float timer = 0.0f;
};