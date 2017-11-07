#include "GameObjectScript.h"

using namespace HurricaneEngine;

#pragma region GAME OBJECT SCRIPT

GameObjectScript::GameObjectScript(const STRING& n)
{
	SetName(n);
}

GameObjectScript::~GameObjectScript()
{
	// EMPTY
}

///////////////////////////

// UPDATE one script
// TODO: be overridden by a derived class
bool GameObjectScript::UpdateScript(GameObject* gameObject, const float _timeStep)
{
	if (_userUpdateFunction)
		return _userUpdateFunction(gameObject, _timeStep);

	return true;
}

#pragma endregion

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#pragma region MULTI-SCRIPTS

GameObjectMultiScript::GameObjectMultiScript(GameObject& _gm)
	: gmOb(&_gm)
{
	// EMPTY
}

GameObjectMultiScript::~GameObjectMultiScript()
{
	ClearAllScripts();
	gmOb = nullptr;
}

//////////////////////////////

// ADD script() (if not already in game object)
void GameObjectMultiScript::AddScript(GameObjectScript* script)
{
	STRING n = script->GetName();
	auto f = scriptMap.find(n);

	script->SetName(n);
	if (f != scriptMap.end())
		return;

	scriptMap.insert(PAIR(STRING, GameObjectScript*)(n, script));
}


// DELETE one script()
void GameObjectMultiScript::DeleteScript(const STRING& n)
{
	if (scriptMap.size() == 0)
		return;

	auto f = scriptMap.find(n);

	if (f != scriptMap.end())
	{
		delete f->second;
		scriptMap.erase(f->first);
	}
}


// DESTROY ALL scripts()
void GameObjectMultiScript::ClearAllScripts()
{
	if (scriptMap.size() > 0)
	{
		MAP(STRING, GameObjectScript*)::iterator iter = scriptMap.begin();

		for (iter = scriptMap.begin(); iter != scriptMap.end(); iter++)
		{
			GameObjectScript* temp = iter->second;
			SAFE_DELETE(temp);
		}
	}
	scriptMap.clear();
}

// UPDATE ALL scripts()
bool GameObjectMultiScript::UpdateAllScripts(GameObject* gameObject, const float _timeStep)
{
	bool result = true;

	MAP(STRING, GameObjectScript*)::iterator iter = scriptMap.begin();

	for (iter = scriptMap.begin(); (iter != scriptMap.end()) && result; iter++)
	{
		auto temp = iter->second;
		result = temp->UpdateScript(gameObject, _timeStep);
	}

	return result;
}

#pragma endregion