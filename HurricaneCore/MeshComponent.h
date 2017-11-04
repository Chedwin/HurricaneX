#pragma once

#include "Macro.h"
#include "IComponent.h"

namespace HurricaneEngine 
{
	class GameObject;
	class Model;

	class MeshComponent : public IComponent {
	public:
		MeshComponent(Model* _d, GameObject* _obj) : IComponent(_obj) {}
		~MeshComponent() {}


	};

}