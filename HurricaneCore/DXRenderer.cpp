#include "DXRenderer.h"

DXRenderer::DXRenderer(const Window& _wnd) : AbstractRenderer(_wnd)
{
	_wndHandle = _wnd.GetHandle();

	CreateDevice(_wnd);
	CreateRenderTarget();
}

DXRenderer::~DXRenderer()
{
}


///////////////////////////////////////////////////////////////////////////////////////

// Init functions

void DXRenderer::CreateDevice(const Window & _wnd)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferCount = 1; // 1 = allows for DOUBLE BUFFERING
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = _wnd.GetHandle();

	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = true; // can go fullscreen if false

								   // create new swap chain, device, and context in one line!
	auto result = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&m_swapChain,
		&m_device,
		nullptr,
		&m_deviceContext
	);

	if (result != S_OK) {
		MessageBox(_wnd.GetHandle(), "DirectX 11 initialization FAILED", "Error", MB_OK);
		exit(0);
	}
}

void DXRenderer::CreateRenderTarget()
{
	ID3D11Texture2D* backBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);
	backBuffer->Release();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void DXRenderer::BeginFrame()
{
	float clearColor[] = { 0.25f, 0.5f, 1.0f, 1.0f };
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, clearColor);
}

void DXRenderer::Render()
{
	
}

void DXRenderer::EndFrame()
{
	// swap the buffer
	m_swapChain->Present(1, 0);
}