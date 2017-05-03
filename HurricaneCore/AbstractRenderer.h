//*******************************//
//
// Name:			AbstractRenderer.h
// Description:		
//					
//
// Author:			Edwin Chen
// Special Thanks:  
//
// Created:			Sep 01, 2017
// Last updated:	Apr 24, 2017
//
//*******************************//


#ifndef _ABSTRACT_RENDERER_H
#define _ABSTRACT_RENDERER_H

#include "Macro.h"

class AbstractRenderer 
{
protected:
	AbstractRenderer() {}
public:
	virtual ~AbstractRenderer() {}

	virtual bool InitRenderer(HWND hwnd, int width, int height) {
		_hwnd = hwnd;
		_width = width;
		_height = height;

		return true;
	}

	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;

	virtual void ClearScreen(float r, float g, float b) {}

protected:
	HWND _hwnd;
	int _width, _height;
};

#endif