//*******************************//
//
// Name:			DXRenderer.h
// Description:		
//					
//
// Author:			Edwin Chen
// Special Thanks:  Daniel Argento
//
// Created:			Mar 11, 2017
// Last updated:	May 02, 2017
//
//*******************************//


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

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dcompiler.lib")


class DXRenderer : public AbstractRenderer 
{
	friend class DXApp;
protected:
	DXRenderer();
	bool CreateDeviceAndRenderTarget(HWND hwnd, int width, int height, bool isFullscreen);

public:
	~DXRenderer();
	bool InitRenderer(const HWND& hwnd, int width, int height, bool fullscreen) final;
	void CreateViewPort();

	void BeginFrame();
	void EndFrame();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();


protected:
	// Device = virtual representation of your video adapter
	ID3D11Device* d3d11device = nullptr;

	// Device Context = manager for the GPU and renderering pipeline
	ID3D11DeviceContext* deviceContext = nullptr;
	
	// Swap Chain = series of buffers which take turns being rendered
	// NOTE: this doesn't belong to Direct3D but to DXGI the DirectX hardware interface
	IDXGISwapChain* swapChain = nullptr;

	// Render target = COM object that maintains a location in video memory for you to render to
	ID3D11RenderTargetView* renderTargetView = nullptr;

};


#endif
