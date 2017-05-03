//*******************************//
//
// Name:			GLRenderer.h
// Description:		This creates an OpenGL environment for rendering to the window.
//
// Author:			Edwin Chen
// Created:			Sep 20, 2016
// Last updated:	May 02, 2017
//
//*******************************//

#ifndef _OPENGL_RENDERER_H
#define _OPENGL_RENDERER_H

#include <glew.h>
#include "Macro.h"
#include "AbstractRenderer.h"



class GLRenderer : public AbstractRenderer {
	friend class Game;
protected:
	GLRenderer();

	bool InitOpenGLDevice(const HWND& hwnd, int width, int height, bool fullscreen);
public:
	~GLRenderer();

	bool InitRenderer(const HWND& hwnd, int width, int height, bool fullscreen) override final;

	void BeginFrame() override final;
	void EndFrame() override final ;
};

#endif