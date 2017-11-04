#ifndef _SPRITE_COMPONENT_H
#define _SPRITE_COMPONENT_H

#include "Macro.h"
#include "IComponent.h"

namespace HurricaneEngine 
{

	class SpriteComponent : public IComponent {
	public:
		explicit SpriteComponent(GameObject* _ob);
		~SpriteComponent();

		bool InitComp();
		void DestroyComp() final;
		void UpdateComp(const float _deltaTime) final;
		void RenderComp() final;
	};

}

#endif