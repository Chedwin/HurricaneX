#pragma once

#include <Macro.h>
#include <SceneManager.h>

class GameplayScene : public HurricaneEngine::IScene {
public:
	explicit GameplayScene(const STRING& _name = "Gameplay");
	~GameplayScene() final;

	void EnterState(HurricaneEngine::SceneManager* owner) override;
	void ExitState(HurricaneEngine::SceneManager* owner) override;
	void UpdateState(HurricaneEngine::SceneManager* owner, const float _dt) override;
	void RenderState(HurricaneEngine::SceneManager* owner) override;

};