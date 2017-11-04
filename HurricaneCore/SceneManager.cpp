#include "SceneManager.h"
#include "Debugger.h"

using namespace HurricaneEngine;

UNIQUE_PTR(SceneManager) SceneManager::_sceneManager(nullptr);

SceneManager* SceneManager::GetInstance() 
{
	if (_sceneManager.get() == nullptr)
		_sceneManager.reset(new SceneManager);
	return _sceneManager.get();
}


SceneManager::SceneManager()
{
	_sceneFSM = nullptr;
	_sceneFSM = new FiniteStateMachine<SceneManager>(this);
}


SceneManager::~SceneManager()
{
	SAFE_DELETE(_sceneFSM);
}

void SceneManager::AddScene(Scene* _scene)
{
	_sceneFSM->AddState(_scene);
	if (!_currentScene)
		SetCurrentScene(_scene);
}

void SceneManager::SetCurrentScene(Scene* _scene)
{
	_sceneFSM->ChangeState(_scene);
	_currentScene = static_cast<Scene*>(_sceneFSM->GetCurrentState());
}


void SceneManager::DeleteScenes() 
{
	_sceneFSM->Clear();
}


void SceneManager::UpdateScene(const float _deltaTime)
{
	_sceneFSM->UpdateState(_deltaTime);
}

void SceneManager::RenderScene()
{
	_sceneFSM->RenderState();
}


void SceneManager::SwitchScene(const STRING& _name)
{
	Scene* newScene = static_cast<Scene*>(_sceneFSM->GetState(_name));

	if (!newScene) 
	{
		Debugger::Error("Scene Named: '" + _name + "' does not exist!");
		return;
	}

	SetCurrentScene(newScene);
}