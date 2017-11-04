#pragma once

#include <Macro.h>
#include <SceneManager.h>
#include "Triangle.h"

class GameplayScene : public HurricaneEngine::Scene {
public:
	GameplayScene();
	~GameplayScene();

	void EnterState(HurricaneEngine::SceneManager* owner) override;
	void ExitState(HurricaneEngine::SceneManager* owner) override;
	void UpdateState(HurricaneEngine::SceneManager* owner, const float _dt) override;
	void RenderState(HurricaneEngine::SceneManager* owner) override;

	Triangle triangle;
};