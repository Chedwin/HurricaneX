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
// Last updated:	Sep 07, 2017
//
//*******************************//


#ifndef _DIRECTX_RENDERER_H
#define _DIRECTX_RENDERER_H

#include "Macro.h"
#include "AbstractRenderer.h"

// DIRECTX UTILITIES
#include "d3dUtil.h"
#include "HMath.h"


__declspec(align(16)) // guarantees 16-btye alignment
class DXRenderer : public AbstractRenderer
{
	friend class HXApp;
	friend class Graphics;
protected:
	DXRenderer();
	bool CreateDeviceAndRenderTarget(HWND hwnd, int width, int height, bool isFullscreen, bool vsync = false);

public:
	virtual ~DXRenderer();

	// This override will call CreateDeviceAndRenderTarget()
	bool InitRenderer(HWND hwnd, int width, int height, bool isFullScreen) override;

#pragma region _new_ & _delete_ OPERATOR OVERLOAD
	void* operator new(size_t i) {
		return _mm_malloc(i, 16);	
	}

	void operator delete(void* p) {
		_mm_free(p);
	}
#pragma endregion

public:
	void CleanUpD3DSystems();
	void CleanUpRenderTarget();

	void BeginFrame() override;
	void EndFrame() override;

	void ClearScreen(float r, float g, float b) override;

	void GetVideoCardInfo(char* cardName, int& memory);

#pragma region INLINE FUNCTIONS
	// d3d devices accessors
	inline ID3D11Device* GetDevice() const {
		return _d3d11device;
	}
	inline ID3D11DeviceContext* GetDeviceContext() const {
		return _deviceContext;
	}

	// matrix accessors
	inline MAT4 GetProjectionMatrix() const {
		return projectionMatrix;
	}
	inline MAT4 GetWorldMatrix() const {
		return worldMatrix;
	}
	inline MAT4 GetOrthoMatrix() const {
		return orthoMatrix;
	}

#pragma endregion


protected:
	// Device = virtual representation of your video adapter
	ID3D11Device*				_d3d11device;

	// Device Context = manager for the GPU and renderering pipeline
	ID3D11DeviceContext*		_deviceContext;
	
	// Swap Chain = series of buffers which take turns being rendered
	// NOTE: this doesn't belong to Direct3D but to DXGI the DirectX hardware interface
	IDXGISwapChain*				_swapChain;

	// Render target = COM object that maintains a location in video memory for you to render to
	ID3D11RenderTargetView*		_renderTargetView;

	//ID3D11Texture2D*			_depthStencilBuffer;
	//ID3D11DepthStencilState*	_depthStencilState;
	//ID3D11DepthStencilView*		_depthStencilView;
	//ID3D11RasterizerState*		_rasterState;

protected:
	bool  _vsync_enabled;
	int   _videoCardMemory;
	char  _videoCardDescription[128];
public:
	int width, height;

public:
	 MAT4 projectionMatrix;
	 MAT4 worldMatrix;
	 MAT4 orthoMatrix;
};


#endif
