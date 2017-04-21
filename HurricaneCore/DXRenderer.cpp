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
	swapChain->Release();
	d3d11device->Release();
	deviceContext->Release();
	renderTargetView->Release();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

// Create the DirectX 11 Swap chain, device context, etc.

bool DXRenderer::CreateDeviceAndRenderTarget(HWND hwnd, int width, int height)
{
	DXRenderer::width = width;
	DXRenderer::height = height;

	//Describe our Buffer
	DXGI_MODE_DESC bufferDesc;

	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

	bufferDesc.Width = width;						//Width of resolution
	bufferDesc.Height = height;						//Height of resolution
	bufferDesc.RefreshRate.Numerator = 60;
	bufferDesc.RefreshRate.Denominator = 1;			//Describes refresh rate in hertz 60/1 = 60hz
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //Describes format of the display 8 bits allocated for each
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; //Describes the order the rasterizer will render onto a surface, because were using double rendering the order doesnt really matter
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; //Describes how an image will be stretched to fit a monitors resolution

														//Describe our swap chain
	DXGI_SWAP_CHAIN_DESC swapChainDesc;

	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferDesc = bufferDesc;	//Describes the BackBuffer
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;	//Describes the Multi-Sampling
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //Decribes the access the cpu has to the surface of the backbuffer
	swapChainDesc.BufferCount = 1;			//number of back buffers to be used, can use more if wanted
	swapChainDesc.OutputWindow = hwnd;		//Handle to our window
	swapChainDesc.Windowed = TRUE;			//True for windowed, False for full-screen CARE WITH FULL-SCREEN
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; //What the display driver should do with th front buffer after swaping it with the back-buffer. In this case we let it decide what the most efficient setting is
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; //changes resolution when swapping windowed - fullscreen

	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &d3d11device, NULL, &deviceContext);

	if (hr != S_OK) {
		MessageBox(0, "Direct3D Initialization - Failed ", "Error", MB_OK);
		return false;
	}

	ID3D11Texture2D* BackBuffer;
	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);



	hr = d3d11device->CreateRenderTargetView(BackBuffer, NULL, &renderTargetView);
	BackBuffer->Release(); //Relase it when we dont need it anymore



	deviceContext->OMSetRenderTargets(1, &renderTargetView, NULL);

	return true;
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
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width =  (FLOAT)DXRenderer::width;
	viewport.Height = (FLOAT)DXRenderer::height;

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
	swapChain->Present(0, 0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

ID3D11Device * DXRenderer::GetDevice()
{
	return d3d11device;
}

ID3D11DeviceContext * DXRenderer::GetDeviceContext()
{
	return deviceContext;
}


















































//#include "Window.h"
//#include "DXRenderer.h"
//
//DXRenderer::DXRenderer(Window& _wnd) : AbstractRenderer(_wnd)
//{
//	_windowRef = &_wnd;
//
//	CreateDevice(_wnd);
//	CreateRenderTarget();
//}
//
//DXRenderer::~DXRenderer()
//{
//	m_swapChain->Release();
//	m_device->Release();
//	m_deviceContext->Release();
//	m_renderTargetView->Release();
//}
//
//
/////////////////////////////////////////////////////////////////////////////////////////
//
//// Init functions
//
//void DXRenderer::CreateDevice(Window& _wnd)
//{
//	//Describe our Buffer
//	DXGI_MODE_DESC bufferDesc;
//
//	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));
//
//	bufferDesc.Width = _windowRef->GetWidth();		//Width of resolution
//	bufferDesc.Height = _windowRef->GetHeight();	//Height of resolution
//	bufferDesc.RefreshRate.Numerator = 60;
//	bufferDesc.RefreshRate.Denominator = 1;			//Describes refresh rate in hertz 60/1 = 60hz
//	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //Describes format of the display 8 bits allocated for each
//	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; //Describes the order the rasterizer will render onto a surface, because were using double rendering the order doesnt really matter
//	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; //Describes how an image will be stretched to fit a monitors resolution
//
//	DXGI_SWAP_CHAIN_DESC swapChainDesc;
//
//	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
//
//	swapChainDesc.BufferDesc = bufferDesc;	//Describes the BackBuffer
//	swapChainDesc.SampleDesc.Count = 1;
//	swapChainDesc.SampleDesc.Quality = 0;	//Describes the Multi-Sampling
//	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //Decribes the access the cpu has to the surface of the backbuffer
//	swapChainDesc.BufferCount = 1;			//number of back buffers to be used, can use more if wanted
//	swapChainDesc.OutputWindow = _windowRef->GetHandle();		//Handle to our window
//	swapChainDesc.Windowed = TRUE;			//True for windowed, False for full-screen CARE WITH FULL-SCREEN
//	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; //What the display driver should do with th front buffer after swaping it with the back-buffer. In this case we let it decide what the most efficient setting is
//	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; //changes resolution when swapping windowed - fullscreen
//
//	// create new swap chain, device, and context in one line!
//	auto result = D3D11CreateDeviceAndSwapChain(
//		nullptr,
//		D3D_DRIVER_TYPE_HARDWARE,
//		nullptr,
//		0,
//		nullptr,
//		0,
//		D3D11_SDK_VERSION,
//		&swapChainDesc,
//		&m_swapChain,
//		&m_device,
//		nullptr,
//		&m_deviceContext
//	);
//
//	if (result != S_OK) {
//		MessageBox(0, "DirectX 11 initialization FAILED", "Error", MB_OK);
//		exit(0);
//	}
//}
//
//void DXRenderer::CreateRenderTarget()
//{
//	ID3D11Texture2D* backBuffer;
//	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
//	m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);
//	
//	
//	backBuffer->GetDesc(&m_backBufferDesc);
//	backBuffer->Release();
//}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//// RENDER functions
//
//void DXRenderer::BeginFrame()
//{
//	// bind render target
//	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, nullptr); // last parameter = depth buffer -> used for 3D rendering
//
//	// set the viewport
//	D3D11_VIEWPORT viewport;// = D3D11_VIEWPORT(0.0f, 0.0f, (float)m_backBufferDesc.Width, (float)m_backBufferDesc.Height);
//	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
//	viewport.TopLeftX = 0;
//	viewport.TopLeftY = 0;
//	viewport.Width = (float)m_backBufferDesc.Width;   // _windowRef->GetWidth();
//	viewport.Height = (float)m_backBufferDesc.Height; // _windowRef->GetHeight();
//
//
//	m_deviceContext->RSSetViewports(1, &viewport);
//
//	// set background colour
//	float clearColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
//	m_deviceContext->ClearRenderTargetView(m_renderTargetView, clearColor);
//}
//
//void DXRenderer::Render()
//{
//	// empty
//}
//
//void DXRenderer::EndFrame()
//{
//	// swap the buffer
//	m_swapChain->Present(0, 0);
//}
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//ID3D11Device* DXRenderer::GetDevice()
//{
//	return m_device;
//}
//
//ID3D11DeviceContext* DXRenderer::GetDeviceContext()
//{
//	return m_deviceContext;
//}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////

