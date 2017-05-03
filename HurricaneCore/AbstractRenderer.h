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
// Last updated:	May 02, 2017
//
//*******************************//


#ifndef _ABSTRACT_RENDERER_H
#define _ABSTRACT_RENDERER_H

#include "Macro.h"

class AbstractRenderer {
protected:
	AbstractRenderer() {}
public:
	virtual ~AbstractRenderer() {}

	virtual bool InitRenderer(const HWND& hwnd, int width, int height, bool fullscreen) = 0;
	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;

	virtual void ClearScreen(float r, float g, float b) {}


	inline void SetWindow(const HWND& hwnd) {
		_hwnd = hwnd;
	}
	inline void SetSize(float w, float h) {
		_width = w;
		_height = h;
	}

protected:
	HWND _hwnd;
	int _width;
	int _height;
};

#endif