#include "TestGame.h"
#include "MainMenuScene.h"
#include "GameplayScene.h"

using namespace HurricaneEngine;

UNIQUE_PTR(TestGame) TestGame::_instance(nullptr);

TestGame* TestGame::GetInstance() {
	if (_instance.get() == nullptr) 
		_instance.reset(new TestGame());
	return _instance.get();
}

TestGame::TestGame() 
{
	// empty
}

TestGame::~TestGame()
{
	TestGame::OnExit();
}

void TestGame::OnExit()
{

}

bool TestGame::InitGame()
{
	IHGame::AddScene(new MainMenuScene());
	IHGame::AddScene(new GameplayScene());

	return true;
}

void TestGame::Update(const float _deltaTime)
{
	IHGame::Update(_deltaTime);

	STRINGSTREAM stream;
	stream << "Hurricane Test Game | " << _sceneManager->CurrentSceneName() << " | FPS: " << _fps;
	STRING s = stream.str();

	SetWindowTitle(s);
}
