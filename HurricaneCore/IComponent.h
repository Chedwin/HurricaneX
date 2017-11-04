//*******************************//
//
// Name:			IComponent.h
// Description:		Defines a basic component class for different component types.
//
//
// Author:			Edwin Chen, 
// Spcial Thanks:   Mathieu Violette, James Sholdice, Nathan Senter
//
// Created:			Sep 30, 2016
// Last updated:	Nov 02, 2017
//
//*******************************//


#ifndef _ICOMPONENT_H
#define _ICOMPONENT_H

#include "Macro.h"

namespace HurricaneEngine 
{
	class GameObject;

	class IComponent {
		friend class GameObject;
	protected:
		GameObject* _ownerObj;

	protected:
		IComponent(GameObject* _obj) 
		{
			_ownerObj = nullptr;
			_ownerObj = _obj;
			InitComp();
		}

		virtual ~IComponent() 
		{
			DestroyComp();
			_ownerObj = nullptr;
		}

	public:
		virtual bool InitComp()							= 0;
		virtual void DestroyComp()						= 0;
		virtual void UpdateComp(const float _deltaTime) = 0;
		virtual void RenderComp()						= 0;
	};

}


#endif