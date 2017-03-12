#ifndef _DX_RENDERER_H
#define _DX_RENDERER_H

#include "Macro.h"
#include "AbstractRenderer.h"
#include <d3d11.h>

class DXRenderer : public AbstractRenderer {
public:
	DXRenderer(const Window& _wnd);
	~DXRenderer();

	void BeginFrame();
	void Render();
	void EndFrame();


protected:
	void CreateDevice(const Window& _wnd);
	void CreateRenderTarget();
	
protected:
	IDXGISwapChain* m_swapChain = nullptr;
	ID3D11Device* m_device = nullptr;
	ID3D11DeviceContext* m_deviceContext = nullptr;

	HWND _wndHandle;

	// render target
	ID3D11RenderTargetView* m_renderTargetView = nullptr;
};

#endif
