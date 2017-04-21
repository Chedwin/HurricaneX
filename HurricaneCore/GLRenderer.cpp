//#include "GLRenderer.h"
//
//GLRenderer::GLRenderer(Window& _wnd) : AbstractRenderer(_wnd)
//{
//	GLenum error = glewInit();
//	if (error != GLEW_OK) {
//		MessageBox(_wnd.GetHandle(), "GLEW initialization FAILED", "Error", 0);
//		exit(0);
//	}
//
//	glEnable(GL_CULL_FACE);
//	glEnable(GL_DEPTH_TEST);
//	glCullFace(GL_FRONT);
//	glDepthFunc(GL_LESS);
//	glDepthMask(GL_TRUE);
//	glFrontFace(GL_CCW);
//	glEnable(GL_BLEND);
//	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
//
//	glViewport(0, 0, _wnd.GetWidth(), _wnd.GetHeight());
//}
//
//GLRenderer::~GLRenderer()
//{
//	// empty
//}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//void GLRenderer::BeginFrame()
//{
//	// Accept fragment if it closer to the camera than the former one
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	// To operate on model-view matrix
//	glMatrixMode(GL_MODELVIEW);
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//}
//
//void GLRenderer::Render()
//{
//}
//
//void GLRenderer::EndFrame()
//{
//	//SwapBuffers(Window::hDC);
//}
