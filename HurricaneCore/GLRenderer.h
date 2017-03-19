//*******************************//
//
// Name:			GLRenderer.h
// Description:		This creates an OpenGL environment for rendering to the window.
//
// Author:			Edwin Chen
// Created:			Sep 20, 2016
// Last updated:	Mar 12, 2017
//
//*******************************//

#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H


#include <glew.h>

#include "Macro.h"
#include "AbstractRenderer.h"
#include "Window.h"


class GLRenderer : public AbstractRenderer {
	friend class Game;
protected:
	GLRenderer(Window& _wnd);
public:
	~GLRenderer();

	void BeginFrame() override;
	void Render() override;
	void EndFrame() override;
};

#endif