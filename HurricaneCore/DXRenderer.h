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
// Last updated:	Apr 21, 2017
//
//*******************************//


#ifndef _DX_RENDERER_H
#define _DX_RENDERER_H

#include "Macro.h"
#include "AbstractRenderer.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dcompiler.lib")

// DIRECTX 
#include <DXGI.h>
#include <d3d11.h>
#include <d3d11sdklayers.h>
#include <d3dcompiler.h>
#include <d3d10.h>

class DXRenderer 
	//: public AbstractRenderer 
{
	friend class Game;
	friend class DXApp;
protected:
	DXRenderer();
	bool CreateDeviceAndRenderTarget(HWND hwnd, int width, int height);

public:
	~DXRenderer();

	void CreateViewPort();

	void BeginFrame();
	void EndFrame();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();


protected:
	IDXGISwapChain* swapChain = nullptr;
	ID3D11Device* d3d11device = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;

	// render target
	ID3D11RenderTargetView* renderTargetView = nullptr;

	D3D11_TEXTURE2D_DESC m_backBufferDesc;

public:
	int width, height;
};


#endif
