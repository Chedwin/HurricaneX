#include "GameObject.h"
#include "Scene.h"

//////////////////////////////////////////////////////////////////////////////////////////////////

// CONSTRUCTOR(S) / DESTRUCTOR
GameObject::GameObject(Scene& sc, const STRING & name): gameObject(this)
{
	if (name == "") 
		SetName("NewGameObject");
	else 
		SetName(name);

	scripts = nullptr;
	scripts = new GameObjectMultiScript();

	SetEnabled(true);

	scene = &sc;
	sc.AddSceneNode(*gameObject);
}


GameObject::~GameObject()
{
	// TODO: Delete all scripts attached to this game object
	if (scripts) {
		delete scripts;
	}
	scripts = nullptr;
}


//////////////////////////////////////////////////////////////////////////////////////////////////

void GameObject::Update(const float _deltaTime)
{
}

void GameObject::PreRender()
{
}

void GameObject::Render()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////

// CHILDREN GAME OBJECTS
// Helpful when building scene graph

void GameObject::AddChild(GameObject& g)
{
	childObjects.push_back(&g);
}

void GameObject::RemoveChild(GameObject& g)
{
	VECTOR(GameObject*)::iterator iter;
	for (iter = childObjects.begin(); iter != childObjects.end(); iter++)
	{
		if (*iter == &g) {
			delete *iter;
			*iter = nullptr;
			return;
		}
	}
}

void GameObject::RemoveChild(const STRING& n)
{
	VECTOR(GameObject*)::iterator iter;
	for (iter = childObjects.begin(); iter != childObjects.end(); iter++)
	{
		GameObject* temp = *iter;
		if (temp->GetName() == n)
		{
			delete *iter;
			childObjects.erase(iter);
			return;
		}
	}
	childObjects.shrink_to_fit();
}

void GameObject::ClearAllChildren()
{
	if (childObjects.size() > 0)
	{
		VECTOR(GameObject*)::iterator iter;
		for (iter = childObjects.begin(); iter != childObjects.end(); iter++)
		{
			delete *iter;
			*iter = nullptr;
		}
	}
	childObjects.clear();
}


// GET CHILD
// by name
GameObject* GameObject::GetChild(const STRING& name)
{
	VECTOR(GameObject*)::iterator iter;
	for (iter = childObjects.begin(); iter != childObjects.end(); iter++)
	{
		GameObject* temp = *iter;
		if (temp->GetName() == name)
		{
			return temp;
		}
	}
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

// TAGS

void GameObject::AddTag(const STRING& _tag)
{
	bool checkTag = HasTag(_tag);

	if (!checkTag)
	{
		tags.push_back(_tag);
		return;
	}
}

bool GameObject::HasTag(const STRING& _tag)
{
	for (int i = 0; i < tags.size(); i++)
	{
		if (tags[i] == _tag)
			return true;
	}
	return false;
}

void GameObject::RemoveTag(const STRING& _tag)
{
	bool checkTag = HasTag(_tag);

	if (!checkTag)
		return;

	for (int i = 0; i < tags.size(); i++)
	{
		if (tags[i] == _tag) {
			tags[i].erase();
		}
	}
	tags.shrink_to_fit();
}


//////////////////////////////////////////////////////////////////////////////////////////////////