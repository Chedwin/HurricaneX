#ifndef _DX_RENDERER_H
#define _DX_RENDERER_H

#include "Macro.h"
#include "AbstractRenderer.h"

// DIRECTX 
#include <DXGI.h>
#include <d3d11.h>
#include <d3d11sdklayers.h>
#include <d3dcompiler.h>
#include <d3d10.h>


class DXRenderer : public AbstractRenderer {
	friend class Game;
protected:
	DXRenderer(Window& _wnd);
public:
	~DXRenderer();

	void BeginFrame() override;
	void Render() override;
	void EndFrame() override;

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();


protected:
	void CreateDevice(Window& _wnd);
	void CreateRenderTarget();
	
protected:
	IDXGISwapChain* m_swapChain = nullptr;
	ID3D11Device* m_device = nullptr;
	ID3D11DeviceContext* m_deviceContext = nullptr;

	// render target
	ID3D11RenderTargetView* m_renderTargetView = nullptr;

	D3D11_TEXTURE2D_DESC m_backBufferDesc;
};

#endif
