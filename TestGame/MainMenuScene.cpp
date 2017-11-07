#include <Debugger.h>
#include <HUtility.h>
#include "MainMenuScene.h"
#include "TestGame.h"

using namespace HMath;
using namespace HurricaneEngine;

MainMenuScene::MainMenuScene(const STRING& _name) 
	: IScene(_name)
{

}

MainMenuScene::~MainMenuScene()
{
	SAFE_DELETE(texture);
	SAFE_DELETE(shader);
	SAFE_DELETE(vert);
}

void MainMenuScene::EnterState(SceneManager* owner)
{
	Debugger::Log("Welcome to Hurricane!");

	shader = new TextureShader();
	shader->InitShader(TestGame::GetInstance()->DXR(), L"Texture.fx", L"VSMain", L"PSMain");
	
	texture = new Texture();
	texture->Init(TestGame::GetInstance()->DXR(), "persona4.jpg");

	vert = new VertexBuffer();
	vert->Init(TestGame::GetInstance()->DXR(), shader, 2.0f, false);
}

void MainMenuScene::ExitState(SceneManager* owner)
{
	Debugger::Log("Loading to Gameplay....");
}

void MainMenuScene::UpdateState(SceneManager* owner, const float _dt)
{
	timer += _dt;

}

void MainMenuScene::RenderState(SceneManager * owner)
{

	MAT4 view = DirectX::XMMatrixIdentity();
	MAT4 proj = DirectX::XMMatrixIdentity();
	MAT4 world = DirectX::XMMatrixIdentity();

	shader->SetShaderParameters(TestGame::GetInstance()->DXR(), texture->GetTexture());
	shader->SetShaderParameters(TestGame::GetInstance()->DXR(), world, proj, view);

	vert->Render();
	
}
