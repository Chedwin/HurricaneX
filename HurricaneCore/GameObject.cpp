#include "GameObject.h"
#include "Scene.h"
#include "MeshComponent.h"

//////////////////////////////////////////////////////////////////////////////////////////////////

// CONSTRUCTOR(S) / DESTRUCTOR
//GameObject::GameObject(Scene& sc, const STRING& name) : gameObject(this)
//{
//	//if (name == "") 
//	//	SetName("NewGameObject");
//	//else 
//	//	SetName(name);
//
//	//scripts = nullptr;
//	//scripts = new GameObjectMultiScript();
//
//	//SetEnabled(true);
//
//	//scene = &sc;
//	//sc.AddSceneNode(*gameObject);
//}

GameObject::GameObject(const STRING& name) : gameObject(this) 
{
	InitGameObject(name);
}

GameObject::~GameObject()
{
	DestroyScripts();
	DestroyComponents();
}

GameObject::GameObject(const GameObject&) 
{
	// empty
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void GameObject::InitGameObject(const STRING& name) 
{
	if (name == "")
		SetName(DEFAULT_GAMEOBJECT_NAME);
	else
		SetName(name);

	scripts = nullptr;
	scripts = new GameObjectMultiScript();

	SetEnabled(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void GameObject::Update(const float _deltaTime)
{
	// GameObject Scripting
	if (scripts->scriptMap.size() > 0)
	{
		scripts->UpdateAllScripts(gameObject, _deltaTime);
	}
}

void GameObject::PreRender(const float _deltaTime)
{
	//empty
}

void GameObject::Render(const float _deltaTime)
{
	// Render THIS object
	MeshComponent* renderable = gameObject->GetComponent<MeshComponent>();

	if (renderable) 
		renderable->Render();	
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

// ATTACHABLE COMPONENTS

// ADD
void GameObject::AddComponent(Component* c)
{
	bool checkComp = HasComponent(c);

	if (!checkComp)
	{
		componentList.push_back(c);
		return;
	}
}

// HAS component?
bool GameObject::HasComponent(Component* c)
{
	if (componentList.size() > 0)
	{
		for (int i = 0; i < componentList.size(); i++)
		{
			Component* temp = componentList[i];
			if (temp->compType == c->compType)
			{
				return true;
			}
		}
	}
	return false;
}

// DELETE all components on this gameobject
void GameObject::DestroyComponents() 
{
	// TODO: Destroy and clean up components and other game objects
	if (componentList.size() > 0)
	{
		for (int i = 0; i < componentList.size(); i++)
		{
			//switch (componentList[i]->compType) {
			//case COMPONENT_TYPE::Renderable:
			//	
			//	break;
			//case COMPONENT_TYPE::Light:
			//	break;
			//case COMPONENT_TYPE::Rigidbody:
			//	break;
			//case COMPONENT_TYPE::Collider:
			//	break;
			//}

			delete componentList[i];
			componentList[i] = nullptr;
		}
	}
	componentList.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////

// SCRIPTS

void GameObject::DestroyScripts() 
{
	if (scripts)
		delete scripts;
	scripts = nullptr;
}

void GameObject::AddScript(GameObjectScript* _script) 
{
	scripts->AddScript(_script);
}