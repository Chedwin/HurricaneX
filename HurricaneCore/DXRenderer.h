//*******************************//
//
// Name:			DXRenderer.h
// Description:		
//					
//
// Author:			Edwin Chen
// Special Thanks:  Daniel Argento, Mark Seaman
//
// Created:			Mar 11, 2017
// Last updated:	Nov 04, 2017
//
//*******************************//


#ifndef _DIRECTX_RENDERER_H
#define _DIRECTX_RENDERER_H

#include "Macro.h"

// DIRECTX UTILITIES
#include "D3D11Utility.h"
#include "HMath.h"


namespace HurricaneEngine
{
	// forward declare main game application class
	class IHGame;

	// guarantees 16-btye alignment
	__declspec(align(16)) class DXRenderer {
	protected:
		bool InitSwapChain(HWND hwnd, int width, int height, unsigned int numerator, unsigned int denominator, bool isFullscreen = false, bool vsync = false);
		bool InitDepthBuffer(int width, int height);
		bool InitDepthStencilBuffer();
		bool InitStencilView();
		bool InitRasterizerState();
		bool InitViewport(int width, int height);

		bool InitAlphaBlending();
		bool InitZBuffer();

	public:
		DXRenderer();
		DXRenderer(const DXRenderer&) = delete;
		~DXRenderer();

#pragma region _new_ & _delete_ OPERATOR OVERLOAD
		void* operator new(size_t i) {
			return _mm_malloc(i, 16);
		}

		void operator delete(void* p) {
			_mm_free(p);
		}
#pragma endregion


		bool Initialize(HWND _hwnd, int _width, int _height, bool _fullScreen = false, bool _vsync = false);

		void CleanUpSystems();

		void BeginFrame(float r, float g, float b, float a = 1.0f);
		void EndFrame();

		void EnableAlphaBlending(bool _enable);
		void EnableZBuffer(bool _enable);

#pragma region INLINE FUNCTIONS
		// d3d devices accessors
		inline ID3D11Device* GetDevice() const {
			return _device;
		}
		inline ID3D11DeviceContext* GetDeviceContext() const {
			return _deviceContext;
		}

		inline bool IsFullScreen() const {
			return _isFullScreen;
		}
#pragma endregion


	protected:
		// Swap Chain = series of buffers which take turns being rendered
		// NOTE: this doesn't belong to Direct3D but to DXGI the DirectX hardware interface
		IDXGISwapChain*				_swapChain;

		// Device = virtual representation of your video adapter
		ID3D11Device*				_device;

		// Device Context = manager for the GPU and renderering pipeline
		ID3D11DeviceContext*		_deviceContext;


		// Render target = COM object that maintains a location in video memory for you to render to
		ID3D11RenderTargetView*		_renderTargetView;

		ID3D11Texture2D*			_depthStencilBuffer;
		ID3D11DepthStencilState*	_depthStencilState;
		ID3D11DepthStencilView*		_depthStencilView;
		ID3D11RasterizerState*		_rasterizerState;

		ID3D11BlendState*			_alphaEnabledBlendingState;
		ID3D11BlendState*			_alphaDisabledBlendingState;

		ID3D11DepthStencilState*    _depthDisabledStencilState;

		D3D11_VIEWPORT				_screenViewport;

	protected:
		bool  _vsyncEnabled;
		bool  _isFullScreen;
		int   _videoCardMemory;
		char  _videoCardDescription[128];

		int _width, _height;
	};

} // end namespace Hurricane

#endif
