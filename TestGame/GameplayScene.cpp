#include "GameplayScene.h"
#include "Debugger.h"
#include "TestGame.h"

using namespace HurricaneEngine;

GameplayScene::GameplayScene()
{
	stateName = "Gameplay";
	triangle.InitTriangle(TestGame::GetInstance()->DXR());
}

GameplayScene::~GameplayScene()
{
}

void GameplayScene::EnterState(SceneManager* owner)
{

}

void GameplayScene::ExitState(SceneManager* owner)
{
}

void GameplayScene::UpdateState(SceneManager* owner, const float _dt)
{

}

void GameplayScene::RenderState(SceneManager * owner)
{
	triangle.Render();
}
