#include "GLRenderer.h"

// CONSTRUCTOR(S) / DESTRUCTOR

GLRenderer::GLRenderer() : AbstractRenderer()
{
	_width = _height = 0;
}

GLRenderer::~GLRenderer()
{
	// empty
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

// INIT FUNCTIONS

bool GLRenderer::InitOpenGLDevice(const HWND & hwnd, int width, int height, bool fullscreen)
{
	AbstractRenderer::SetSize(width, height);
	AbstractRenderer::SetWindow(hwnd);

	GLenum error = glewInit();
	if (error != GLEW_OK) {
		MessageBox(NULL, "GLEW initialization FAILED", "FATAL ERROR", 0);
		return false;
	}

	glViewport(0, 0, width, height);

	return true;
}

bool GLRenderer::InitRenderer(const HWND & hwnd, int width, int height, bool fullscreen)
{
	return InitOpenGLDevice(hwnd, width, height, fullscreen);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void GLRenderer::BeginFrame()
{
	// Accept fragment if it closer to the camera than the former one
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// To operate on model-view matrix
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


void GLRenderer::EndFrame()
{
	//SwapBuffers(Window::hDC);
}
