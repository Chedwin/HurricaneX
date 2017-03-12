#ifndef _ABSTRACT_RENDERER_H
#define _ABSTRACT_RENDERER_H

#include "Window.h"
class AbstractRenderer {
protected:
	AbstractRenderer(const Window& _wnd) {}
	virtual ~AbstractRenderer() {}

public:
	virtual void Render() = 0;
};

#endif