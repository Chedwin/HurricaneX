#ifndef _ABSTRACT_RENDERER_H
#define _ABSTRACT_RENDERER_H

#include "Window.h"

class AbstractRenderer {
protected:
	AbstractRenderer(Window& _wnd) {}
public:
	virtual ~AbstractRenderer() {}

	virtual void BeginFrame() = 0;
	virtual void Render() = 0;
	virtual void EndFrame() = 0;

protected:
	Window* _windowRef = nullptr;
};

#endif