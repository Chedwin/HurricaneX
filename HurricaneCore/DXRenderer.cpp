#include "DXRenderer.h"
#include "DXApp.h"

// CONSTUCTOR(S) & DESTRUCTOR

DXRenderer::DXRenderer() 
	: swapChain(nullptr), d3d11device(nullptr), deviceContext(nullptr), renderTargetView(nullptr)
{
	// empty
}

DXRenderer::~DXRenderer() 
{
	if (DX11GAME->IsFullscreen())
		swapChain->SetFullscreenState(FALSE, NULL);    // switch to windowed mode
	
	// close and release all COM objects
	swapChain->Release();
	d3d11device->Release();
	deviceContext->Release();
	renderTargetView->Release();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////

// Create the DirectX 11 Swap chain, device context, etc.

bool DXRenderer::CreateDeviceAndRenderTarget(HWND hwnd, int width, int height, bool isFullscreen)
{
	AbstractRenderer::SetSize(width, height);
	AbstractRenderer::SetWindow(hwnd);

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


	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL, 
		D3D_DRIVER_TYPE_HARDWARE, // use D3D_DRIVER_TYPE_REFERENCE if you don't have a DX11 compliant graphics card
		NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, 
		&swapChainDesc, 
		&swapChain, 
		&d3d11device, 
		NULL, 
		&deviceContext
	);

	if (hr != S_OK) {
		MessageBox(0, "Direct3D Initialization - Failed ", "Error", MB_OK);
		return false;
	}

	ID3D11Texture2D* pBackBuffer;

	// GetBuffer() == finds back buffer on swap chain and use it to create the pBackBuffer texture object 
	hr = swapChain->GetBuffer(
		0,							// number of the back buffer to get; 0 == we are only using one back buffer
		__uuidof(ID3D11Texture2D),  // each COM object has a unique ID
									// we use this uuid to identify the ID3D11Texture2D COM object
		(void**)&pBackBuffer
	);



	hr = d3d11device->CreateRenderTargetView(pBackBuffer, NULL, &renderTargetView);
	pBackBuffer->Release(); //Relase it when we dont need it anymore


	// this actually sets the render target
	deviceContext->OMSetRenderTargets(
		1,					// number of render targets			
		&renderTargetView,  // pointer to list of render target if there are more than one
		NULL
	);

	return true;
}

bool DXRenderer::InitRenderer(const HWND & hwnd, int width, int height, bool fullscreen)
{
	return CreateDeviceAndRenderTarget(hwnd, width, height, fullscreen);
}

void DXRenderer::CreateViewPort() 
{
	//D3D11_VIEWPORT viewport;
	//ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	//viewport.TopLeftX = 0;
	//viewport.TopLeftY = 0;
	//viewport.Width = DXRenderer::width;
	//viewport.Height = DXRenderer::height;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////

// Set the viewport and renderTargetView
void DXRenderer::BeginFrame() 
{
	// a viewport is a way of translating pixel coordinates to NDC (Normalized Device Coordinates)
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX	= 0;
	viewport.TopLeftY	= 0;
	viewport.Width		= (FLOAT)AbstractRenderer::_width;
	viewport.Height		= (FLOAT)AbstractRenderer::_height;

	deviceContext->RSSetViewports(1, &viewport);

	const float bgColor[] = { 0.0f, 0.0f, 0.3f, 1.0f };
	deviceContext->ClearRenderTargetView(renderTargetView, bgColor);
}

///////
// Draw stuff BETWEEN these two calls!
//////

// Backbuffering
void DXRenderer::EndFrame() 
{
	// switch the back buffer and the front buffer
	swapChain->Present(0, 0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

ID3D11Device* DXRenderer::GetDevice()
{
	return d3d11device;
}

ID3D11DeviceContext* DXRenderer::GetDeviceContext()
{
	return deviceContext;
}