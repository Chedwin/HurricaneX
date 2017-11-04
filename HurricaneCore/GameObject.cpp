#include "GameObject.h"

using namespace HurricaneEngine;

GameObject::GameObject(const STRING& _name) 
	: gameObject(this)
{
	SetName(_name);
	Init();
}

GameObject::GameObject(const GameObject&) 
{

}


GameObject::~GameObject() 
{
	Destroy();
}

bool GameObject::Init()
{
	_scripts = new GameObjectMultiScript(*gameObject);
	SetEnabled(true);
	return true;
}

void GameObject::Destroy() 
{
	RemoveScripts();
	RemoveComponents();
}


void GameObject::Update(const float _deltaTime) 
{
	// GameObject Scripting
	if (_scripts->scriptMap.size() > 0)
		_scripts->UpdateAllScripts(gameObject, _deltaTime);
}

void GameObject::PreRender() 
{

}

void GameObject::Render() 
{

}



void GameObject::AddComponent(IComponent* c)
{
	IComponent* temp = GetComponent<IComponent>();

	if (temp)
		return;

	_componentList.push_back(c);
}

void GameObject::RemoveComponents()
{
	// TODO: Destroy and clean up components and other game objects
	if (!_componentList.empty())
	{
		for (int i = 0; i < _componentList.size(); i++)
			SAFE_DELETE(_componentList[i]);
	}
	_componentList.clear();
	_componentList.shrink_to_fit();
}

void GameObject::AddScript(GameObjectScript* _script)
{
	_scripts->AddScript(_script);
}

void GameObject::RemoveScripts() 
{
	SAFE_DELETE(_scripts);
}