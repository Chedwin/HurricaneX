#include "SpriteComponent.h"

using namespace HurricaneEngine;

SpriteComponent::SpriteComponent(GameObject* _ob) 
	: IComponent(_ob)
{
	// empty
}

SpriteComponent::~SpriteComponent() 
{
	DestroyComp();
}

bool SpriteComponent::InitComp() 
{
	return true;
}

void SpriteComponent::DestroyComp() 
{

}

void SpriteComponent::UpdateComp(const float _deltaTime) 
{

}

void SpriteComponent::RenderComp() 
{

}