#include "Graphics.h"

Graphics::Graphics() 
	: _dxRenderer(nullptr), _camera(nullptr)
{
	// empty
}

Graphics::Graphics(const Graphics& other)
{
	// empty
}


Graphics::~Graphics() 
{
	ShutdownGraphics();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void Graphics::ShutdownGraphics() {
	if (_dxRenderer)
		delete _dxRenderer;

	if (_camera)
		delete _camera;

	_dxRenderer = nullptr;
}

bool Graphics::InitGraphics(HWND hwnd, int width, int height, bool isFullScreen) 
{
	_dxRenderer = new DXRenderer();
	if (!_dxRenderer->InitRenderer(hwnd, width, height, isFullScreen)) {
		MessageBox(NULL, "Initialization of DirectX 11 FAILED", "FATAL ERROR", 0);
		return false;
	}

	_camera = new Camera(*_dxRenderer->GetDevice(), "myCamera");

	if (!_camera)
		return false;

	_camera->transform.SetPosition(VEC3(0.0f, 0.0f, -10.0f));



	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void Graphics::BeginDraw() {
	_dxRenderer->BeginFrame();
}

void Graphics::EndDraw() {
	_dxRenderer->EndFrame();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void Graphics::ClearScreen(float r, float g, float b) {
	_dxRenderer->ClearScreen(r, g, b);
}

ID3D11Device* Graphics::GetDevice() const
{
	if (!_dxRenderer) {
		MessageBox(NULL, "DirectX Renderer NOT initialized - D3D11 Device NULL", "FATAL ERROR", 0);
		return nullptr;
	}
	return _dxRenderer->GetDevice();
}

ID3D11DeviceContext* Graphics::GetDeviceContext() const
{
	if (!_dxRenderer) {
		MessageBox(NULL, "DirectX Renderer NOT initialized - D3D11 Device Context NULL", "FATAL ERROR", 0);
		return nullptr;
	}
	return _dxRenderer->GetDeviceContext();
}