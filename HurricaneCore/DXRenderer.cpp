#include "DXRenderer.h"
#include "HXApp.h"

#pragma region CONSTRUCTOR(S) & DESTRUCTOR

// CONSTUCTOR(S) & DESTRUCTOR

DXRenderer::DXRenderer() 
	: _swapChain(nullptr), _d3d11device(nullptr), _deviceContext(nullptr), _renderTargetView(nullptr)
	//_depthStencilBuffer(nullptr), _depthStencilState(nullptr), _depthStencilView(nullptr), _rasterState(nullptr)
{
	// empty
}

DXRenderer::~DXRenderer() 
{
	CleanUpD3DSystems();
}

#pragma endregion

/////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region INITIALIZERS & CLEAN FUNCTIONS

// Create the DirectX 11 Swap chain, device context, etc.

bool DXRenderer::InitRenderer(HWND hwnd, int width, int height, bool isFullScreen)
{
	AbstractRenderer::InitRenderer(hwnd, width, height, isFullScreen);
	return CreateDeviceAndRenderTarget(hwnd, width, height, isFullScreen);
}

bool DXRenderer::CreateDeviceAndRenderTarget(HWND hwnd, int width, int height, bool isFullscreen, bool vsync)
{
	DXRenderer::width = width;
	DXRenderer::height = height;

	_vsync_enabled = vsync;

	//Describe our Buffer
	DXGI_MODE_DESC bufferDesc;

	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

	bufferDesc.Width					= width;						//Width of resolution
	bufferDesc.Height					= height;						//Height of resolution
	bufferDesc.RefreshRate.Numerator	= 60;
	bufferDesc.RefreshRate.Denominator	= 1;			//Describes refresh rate in hertz 60/1 = 60hz
	bufferDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM; //Describes format of the display 8 bits allocated for each
	bufferDesc.ScanlineOrdering			= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; //Describes the order the rasterizer will render onto a surface, because were using double rendering the order doesnt really matter
	bufferDesc.Scaling					= DXGI_MODE_SCALING_UNSPECIFIED; //Describes how an image will be stretched to fit a monitors resolution

														
	DXGI_SWAP_CHAIN_DESC swapChainDesc; //Describe our swap chain

	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferDesc			= bufferDesc;	//Describes the BackBuffer
	swapChainDesc.SampleDesc.Count		= 1;
	swapChainDesc.SampleDesc.Quality	= 0;	//Describes the Multi-Sampling
	swapChainDesc.BufferUsage			= DXGI_USAGE_RENDER_TARGET_OUTPUT; //Decribes the access the cpu has to the surface of the backbuffer
	swapChainDesc.BufferCount			= 1;			//number of back buffers to be used, can use more if wanted
	swapChainDesc.OutputWindow			= hwnd;		//Handle to our window
	swapChainDesc.Windowed				= TRUE;			//True for windowed, False for full-screen CARE WITH FULL-SCREEN
	swapChainDesc.SwapEffect			= DXGI_SWAP_EFFECT_DISCARD; //What the display driver should do with th front buffer after swaping it with the back-buffer. In this case we let it decide what the most efficient setting is

	if (isFullscreen) 
	{
		swapChainDesc.BufferDesc.Width  = width;
		swapChainDesc.BufferDesc.Height = height;
	}

	swapChainDesc.Flags					= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; //changes resolution when swapping windowed - fullscreen

	// Create SWAP CHAIN and d3d11 device
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL, 
		D3D_DRIVER_TYPE_HARDWARE, // use D3D_DRIVER_TYPE_REFERENCE if you don't have a DX11 compliant graphics card
		NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, 
		&swapChainDesc, 
		&_swapChain, 
		&_d3d11device, 
		NULL, 
		&_deviceContext
	);

	if (hr != S_OK) {
		MessageBox(0, "Direct3D Initialization - Failed ", "Error", MB_OK);
		CleanUpD3DSystems();
		return false;
	}

	// Create BACK BUFFER
	ID3D11Texture2D* pBackBuffer;

	// GetBuffer() == finds back buffer on swap chain and use it to create the pBackBuffer texture object 
	hr = _swapChain->GetBuffer(
		0,							// number of the back buffer to get; 0 == we are only using one back buffer
		__uuidof(ID3D11Texture2D),  // each COM object has a unique ID
									// we use this uuid to identify the ID3D11Texture2D COM object
		(void**)&pBackBuffer
	);

	if (hr != S_OK) {
		MessageBox(0, "Direct3D Initialization - Failed ", "Error", MB_OK);
		CleanUpD3DSystems();
		return false;
	}


	// Create RENDER TARGET
	hr = _d3d11device->CreateRenderTargetView(pBackBuffer, NULL, &_renderTargetView);

	if (hr != S_OK) {
		MessageBox(0, "Direct3D Initialization - Failed ", "Error", MB_OK);
		CleanUpD3DSystems();
		return false;
	}
	pBackBuffer->Release(); //Relase it when we dont need it anymore


	// this actually sets the render target
	_deviceContext->OMSetRenderTargets(
		1,					// number of render targets			
		&_renderTargetView,  // pointer to list of render target if there are more than one
		NULL
	);

	return true;
}


void DXRenderer::CleanUpD3DSystems()
{
	if (HXGAME->IsFullscreen() && _swapChain)
		_swapChain->SetFullscreenState(FALSE, NULL);    // switch to windowed mode

	// close and release all COM objects
	CleanUpRenderTarget();

	if (_swapChain)
		_swapChain->Release();
	if (_d3d11device)
		_d3d11device->Release();
	if (_deviceContext)
		_deviceContext->Release();
}

void DXRenderer::CleanUpRenderTarget() {
	if (_renderTargetView) 
		_renderTargetView->Release();
	_renderTargetView = NULL;
}

void DXRenderer::GetVideoCardInfo(char* cardName, int& memory)
{
	strcpy_s(cardName, 128, _videoCardDescription);
	memory = _videoCardMemory;
	return;
}

#pragma endregion

/////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region SCREEN FUNCTIONS

// Clear the screen w/ a specifed colour via the render target
void DXRenderer::ClearScreen(float r, float g, float b) {
	const float bgColor[] = { r, g, b, 1.0f }; // fully opaque color background
	_deviceContext->ClearRenderTargetView(_renderTargetView, bgColor);
}


// Set the viewport and renderTargetView
void DXRenderer::BeginFrame() 
{
	// a viewport is a way of translating pixel coordinates to NDC (Normalized Device Coordinates)
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX	= 0;
	viewport.TopLeftY	= 0;
	viewport.Width		= (FLOAT)DXRenderer::width;
	viewport.Height		= (FLOAT)DXRenderer::height;

	_deviceContext->RSSetViewports(1, &viewport);

	ClearScreen(1.0f, 0.0f, 0.0f);
}

///////
// Draw stuff BETWEEN these two calls!
//////

// Backbuffering
void DXRenderer::EndFrame() 
{
	// Present the back buffer to the screen since rendering is complete.
	if (_vsync_enabled)
	{
		// Lock to screen refresh rate.
		_swapChain->Present(1, 0);
	}
	else
	{
		// Present as fast as possible.
		_swapChain->Present(0, 0);
	}
}

#pragma endregion