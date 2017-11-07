#pragma once

#include <Macro.h>
#include <SceneManager.h>
#include <TextureShader.h>
#include <Texture.h>
#include <VertexBuffer.h>


class MainMenuScene : public HurricaneEngine::IScene {
public:
	explicit MainMenuScene(const STRING& _name = "MainMenu");
	~MainMenuScene() final;
	
	void EnterState(HurricaneEngine::SceneManager* owner) override;
	void ExitState(HurricaneEngine::SceneManager* owner) override;
	void UpdateState(HurricaneEngine::SceneManager* owner, const float _dt) override;
	void RenderState(HurricaneEngine::SceneManager* owner) override;

public:
	float timer = 0.0f;
	HurricaneEngine::VertexBuffer* vert;
	HurricaneEngine::Texture* texture;
	HurricaneEngine::TextureShader* shader;
};