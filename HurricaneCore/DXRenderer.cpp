#include "DXRenderer.h"

using namespace HurricaneEngine;

#include "DXRenderer.h"


#pragma region CONSTRUCTOR(S) & DESTRUCTOR

// CONSTUCTOR(S) & DESTRUCTOR

DXRenderer::DXRenderer()
{
	CleanUpSystems();
}

DXRenderer::~DXRenderer()
{
	CleanUpSystems();
}

#pragma endregion

/////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region INITIALIZERS & CLEAN-UP FUNCTIONS

void DXRenderer::CleanUpSystems()
{
	if (IsFullScreen() && _swapChain)
		_swapChain->SetFullscreenState(FALSE, NULL);    // switch to windowed mode
		
	// close and release all COM objects
	RELEASE_COM(_alphaEnabledBlendingState);
	RELEASE_COM(_alphaDisabledBlendingState);
	RELEASE_COM(_depthDisabledStencilState);
	RELEASE_COM(_depthStencilView);
	RELEASE_COM(_depthStencilState);
	RELEASE_COM(_depthStencilBuffer);
	RELEASE_COM(_rasterizerState);


	RELEASE_COM(_renderTargetView);
	RELEASE_COM(_deviceContext);
	RELEASE_COM(_device);
	RELEASE_COM(_swapChain);
}

bool DXRenderer::Initialize(HWND hwnd, int width, int height, bool isFullscreen, bool vsync)
{
	_width = width;
	_height = height;
	_isFullScreen = isFullscreen;
	_vsyncEnabled = vsync;

	HRESULT result;
	IDXGIFactory* factory;
	IDXGIAdapter* adaptor;
	IDXGIOutput* adaptorOutput;

	unsigned int numModes = 0, numerator = 0, denominator = 0, stringLength = 0;
	
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC adaptorDesc;

	int error;

	ID3D11Texture2D* backBufferPtr;


	// Create a DirectX graphics interface
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(result)) {
		RELEASE_COM(factory);
		return false;
	}


	// Use the factory to create an Adaptor	for the primary graphics interface
	result = factory->EnumAdapters(0, &adaptor);
	if (FAILED(result)) {
		RELEASE_COM(adaptor);
		RELEASE_COM(factory);
		return false;
	}


	// Enumerator the primary adaptor output
	result = adaptor->EnumOutputs(0, &adaptorOutput);
	if (FAILED(result)) {
		RELEASE_COM(adaptorOutput);
		RELEASE_COM(adaptor);
		RELEASE_COM(factory);
		return false;
	}


	// Get the num of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the AdaptorOutput
	result = adaptorOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(result)) {
		RELEASE_COM(adaptorOutput);
		RELEASE_COM(adaptor);
		RELEASE_COM(factory);
		return false;
	}


	// Create a list for all possible modes for this monitor/video card combination
	displayModeList = new DXGI_MODE_DESC[numModes];

	// Fill up display mode list
	result = adaptorOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(result)) {
		RELEASE_COM(adaptorOutput);
		RELEASE_COM(adaptor);
		RELEASE_COM(factory);
		return false;
	}

	
	for (unsigned int i = 0; i < numModes; ++i) 
	{
		bool dspWidth = (displayModeList[i].Width == (unsigned int)_width);
		bool dspHeight = (displayModeList[i].Height == (unsigned int)_height);

		if (dspWidth && dspHeight) 
		{
			numerator = displayModeList[i].RefreshRate.Numerator;
			denominator = displayModeList[i].RefreshRate.Denominator;
			break;
		}
	}

	if (numerator == 0 && denominator == 0)
	{
		RELEASE_COM(adaptorOutput);
		RELEASE_COM(adaptor);
		RELEASE_COM(factory);
		return false;
	}


	// Get the adaptor descriptor
	result = adaptor->GetDesc(&adaptorDesc);
	if (FAILED(result)) 
	{
		RELEASE_COM(adaptorOutput);
		RELEASE_COM(adaptor);
		RELEASE_COM(factory);
		return false;
	}


	// Store the video card memory 
	_videoCardMemory = (int)(adaptorDesc.DedicatedVideoMemory / 1024 / 1024);

	// Convert the name of the video card to a char array
	error = wcstombs_s(&stringLength, _videoCardDescription, 128, adaptorDesc.Description, 128);
	if (error != 0) 
	{
		RELEASE_COM(adaptorOutput);
		RELEASE_COM(adaptor);
		RELEASE_COM(factory);
		SAFE_DELETE_ARRAY(displayModeList);
		return false;
	}

	RELEASE_COM(adaptorOutput);
	RELEASE_COM(adaptor);
	RELEASE_COM(factory);
	SAFE_DELETE_ARRAY(displayModeList);

	if (!InitSwapChain(hwnd, width, height, numerator, denominator, isFullscreen, vsync))
		return false;

	result = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBufferPtr);
	if (FAILED(result)) 
		return false;


	result = _device->CreateRenderTargetView(backBufferPtr, NULL, &_renderTargetView);
	if (FAILED(result)) 
	{
		RELEASE_COM(backBufferPtr);
		return false;
	}

	RELEASE_COM(backBufferPtr);

	if (!InitDepthBuffer(width, height)) 
		return false;


	if (!InitDepthStencilBuffer())
		return false;

	if (!InitStencilView())
		return false;

	// bind the render target view and depth stencil buffer to the output render pipeline
	_deviceContext->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);

	if (!InitRasterizerState())
		return false;

	if (!InitViewport(width, height))
		return false;

	if (!InitAlphaBlending())
		return false;

	if (!InitZBuffer())
		return false;


	return true;
}

bool DXRenderer::InitSwapChain(HWND hwnd, int width, int height, unsigned int numerator, unsigned int denominator, bool isFullscreen, bool vsync)
{
	HRESULT result;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	D3D_FEATURE_LEVEL featureLevel;

	// Initialize the swap chain
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// Set the swap chain to a single back buffer
	swapChainDesc.BufferCount = 1;

	// Set the width and height of the swap chain
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;

	// Set regular 32-bit back buffer
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Set the refresh rate of the back buffer
	swapChainDesc.BufferDesc.RefreshRate.Numerator	 = (_vsyncEnabled) ? numerator   : 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = (_vsyncEnabled) ? denominator : 1;


	// set the usage of the back buffer
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// Set the handle of the window
	swapChainDesc.OutputWindow = hwnd;

	// Turn multisampling off
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	// Set to fullscreen or window mode
	swapChainDesc.Windowed = !isFullscreen;
	
	// Set the scan line ordering and scaling to unspecified
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Discard the back buffer contents after presenting 
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Set the flags
	// changes resolution when swapping windowed - fullscreen
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; 

	// Set the feature to DirectX 11
	featureLevel = D3D_FEATURE_LEVEL_11_0;

	result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1, D3D11_SDK_VERSION,
		&swapChainDesc, &_swapChain, &_device, NULL, &_deviceContext);

	if (FAILED(result)) 
	{
		MessageBox(0, "Direct3D Initialization - FAILED", "FATAL ERROR", MB_OK);
		CleanUpSystems();
		return false;
	}
		

	return true;
}

bool DXRenderer::InitDepthBuffer(int width, int height) 
{
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	HRESULT result;

	// Init depth buffer desc
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// set up the depth buffer desc
	depthBufferDesc.Width = width;
	depthBufferDesc.Height = height;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;
	depthBufferDesc.SampleDesc.Count = 1;

	// Create the texture for the depth buffer 
	result = _device->CreateTexture2D(&depthBufferDesc, NULL, &_depthStencilBuffer);

	if (FAILED(result))
		return false;
	
	return true;
}

bool DXRenderer::InitDepthStencilBuffer() 
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	HRESULT result;

	// Init depth stecil desc
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operation if pixel is front facing
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operation if pixel is back facing
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create Depth stencil state
	result = _device->CreateDepthStencilState(&depthStencilDesc, &_depthStencilState);

	if (FAILED(result))
		return false;

	// Set the device context's depth stencil state
	_deviceContext->OMSetDepthStencilState(_depthStencilState, 1);

  	return true;
}

bool DXRenderer::InitStencilView() 
{
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	HRESULT result;

	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// set up description
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// create depth stencil	view
	result = _device->CreateDepthStencilView(_depthStencilBuffer, &depthStencilViewDesc, &_depthStencilView);

	if (FAILED(result))
		return false;


	return true;
}

bool DXRenderer::InitRasterizerState() 
{
	D3D11_RASTERIZER_DESC rasterDesc;
	HRESULT result;

	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;

	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;


	// Create the rasterizer state 
	result = _device->CreateRasterizerState(&rasterDesc, &_rasterizerState);

	if (FAILED(result))
		return false;

	// Set the rasterizer
	_deviceContext->RSSetState(_rasterizerState);

	return true;
}

bool DXRenderer::InitViewport(int width, int height) 
{  
	D3D11_VIEWPORT viewport;

	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;

	_deviceContext->RSSetViewports(1, &viewport);

	return true;
}

bool DXRenderer::InitAlphaBlending() 
{
	D3D11_BLEND_DESC blendStateDesc;
	HRESULT result;
		
	ZeroMemory(&blendStateDesc, sizeof(D3D11_BLEND_DESC));

	blendStateDesc.RenderTarget[0].BlendEnable = true;
	blendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	// create the enabled blend state
	result = _device->CreateBlendState(&blendStateDesc, &_alphaEnabledBlendingState);
	if (FAILED(result))
		return false;

	// modify to create disabled alpha blend state 
	blendStateDesc.RenderTarget[0].BlendEnable = false;

	// create the disabled blend state
	result = _device->CreateBlendState(&blendStateDesc, &_alphaDisabledBlendingState);
	if (FAILED(result))
		return false;


	
	return true;
}

bool DXRenderer::InitZBuffer() 
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	HRESULT result;

	// clear the description
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	depthStencilDesc.DepthEnable = false;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operation if pixel is front facing
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operation if pixel is back facing
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;


	// create the disabled state
	result = _device->CreateDepthStencilState(&depthStencilDesc, &_depthDisabledStencilState);
	if (FAILED(result))
		return false;

	return true;
}

void DXRenderer::EnableAlphaBlending(bool _enable) 
{
	float blendFactor[4]{ 0.0f, 0.0f, 0.0f, 0.0f };

	if (_enable)
		_deviceContext->OMSetBlendState(_alphaEnabledBlendingState, blendFactor, 0xFFFFFFFF);
	else
		_deviceContext->OMSetBlendState(_alphaDisabledBlendingState, blendFactor, 0xFFFFFFFF);
}

void DXRenderer::EnableZBuffer(bool _enable) 
{
	if (_enable)
		_deviceContext->OMSetDepthStencilState(_depthStencilState, 1);
	else
		_deviceContext->OMSetDepthStencilState(_depthDisabledStencilState, 1);
}


#pragma endregion

/////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region SCREEN FUNCTIONS

// Clear the screen w/ a specifed colour via the render target
void DXRenderer::BeginFrame(float r, float g, float b, float a)
{
	// fully opaque color background
	const float bgColor[] = { r, g, b, a }; 

	// clear the back buffer
	_deviceContext->ClearRenderTargetView(_renderTargetView, bgColor);

	// clear the z buffer
	_deviceContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, (UINT8)0.0f);
}

///////
// Draw stuff BETWEEN these two calls!
//////

// Backbuffering
void DXRenderer::EndFrame()
{
	// Present the back buffer to the screen since rendering is complete.
	if (_vsyncEnabled)
		_swapChain->Present(1, 0);	// Lock to screen refresh rate.	
	else
		_swapChain->Present(0, 0); // Present as fast as possible.
}

#pragma endregion