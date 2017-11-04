#include <Debugger.h>
#include <SceneManager.h>
#include "MainMenuScene.h"

using namespace HurricaneEngine;

MainMenuScene::MainMenuScene()
{
	stateName = "MainMenu";

}

MainMenuScene::~MainMenuScene()
{

}

void MainMenuScene::EnterState(SceneManager* owner)
{
	Debugger::Log("Welcome to Hurricane!");
}

void MainMenuScene::ExitState(SceneManager* owner)
{
	Debugger::Log("Loading to Gameplay....");
}

void MainMenuScene::UpdateState(SceneManager* owner, const float _dt)
{
	timer += _dt;
	//Debugger::Log(timer);


	if (timer >= 5.0f)
		SCENE_MANAGER->SwitchScene("Gameplay");
}

void MainMenuScene::RenderState(SceneManager * owner)
{
}
