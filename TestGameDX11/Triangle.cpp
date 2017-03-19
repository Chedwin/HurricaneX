#include <DXRenderer.h>
#include "Triangle.h"


Triangle::Triangle(DXRenderer& _renderer)
{
	CreateMesh(_renderer);
	CreateShaders(_renderer);
	CreateRenderStates(_renderer);
}


Triangle::~Triangle()
{
	m_vertexBuffer->Release();
	m_vertexShader->Release();
	m_pixelShader->Release();
	m_inputLayout->Release();
	m_rasterizerState->Release();
	m_depthState->Release();
	m_blendState->Release();
}


///////////////////////////////////////////////////////////////////////////////

void Triangle::CreateMesh(DXRenderer & _renderer)
{
	// define triangle geometry
	Vertex vertices[] = {
		Vertex(0.0f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f),
		Vertex(0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f),
		Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f),
	};

	// Create our vertex buffer
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	//vertexBufferDesc = CD3D11_BUFFER_DESC(sizeof(vertices), D3D11_BIND_VERTEX_BUFFER);
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * 3;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexData = { 0 };
	ZeroMemory(&vertexData, sizeof(vertexData));

	vertexData.pSysMem = vertices; // push the vertices to the video card
	_renderer.GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer); // creates our vertex buffer
}

void Triangle::CreateShaders(DXRenderer & _renderer)
{
	IFSTREAM vsFile("triangleVertex.cso", std::ios::binary);
	IFSTREAM psFile("trianglePixel.cso", std::ios::binary);

	// iterates through the file, byte by byte, and loads into the vector
	// pretty slow but it works!
	VECTOR(char) vsData = { std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>() };
	VECTOR(char) psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };

	_renderer.GetDevice()->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &m_vertexShader);
	_renderer.GetDevice()->CreatePixelShader(psData.data(), psData.size(), nullptr, &m_pixelShader);


	// create our input layouts

	// we need to bind our "attributes" from the shaders
	// i.e. GLSL-like stuff
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 
		12, //D3D11_APPEND_ALIGNED_ELEMENT, 
		D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	_renderer.GetDevice()->CreateInputLayout(layout, 2, vsData.data(), vsData.size(), &m_inputLayout);

}


void Triangle::CreateRenderStates(DXRenderer& _renderer) {
	// Rasterizer state
	auto rasterizerDesc = CD3D11_RASTERIZER_DESC(
		D3D11_FILL_SOLID,
		D3D11_CULL_NONE,
		false,
		0, 0, 0, 0,
		false, false, false);
	_renderer.GetDevice()->CreateRasterizerState(&rasterizerDesc, &m_rasterizerState);

	// Blend state
	auto blendDesc = CD3D11_BLEND_DESC(CD3D11_DEFAULT());
	_renderer.GetDevice()->CreateBlendState(&blendDesc, &m_blendState);

	// Depth state
	auto depthDesc = CD3D11_DEPTH_STENCIL_DESC(
		FALSE, D3D11_DEPTH_WRITE_MASK_ZERO, D3D11_COMPARISON_LESS,
		FALSE, D3D11_DEFAULT_STENCIL_READ_MASK, D3D11_DEFAULT_STENCIL_WRITE_MASK,
		D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_ALWAYS,
		D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_ALWAYS);
	_renderer.GetDevice()->CreateDepthStencilState(&depthDesc, &m_depthState);
}

///////////////////////////////////////////////////////////////////////////////

void Triangle::Draw(DXRenderer& _renderer)
{
	auto deviceContext = _renderer.GetDeviceContext();

	// Set render states
	deviceContext->RSSetState(m_rasterizerState);
	deviceContext->OMSetBlendState(m_blendState, NULL, 0xffffffff);
	deviceContext->OMSetDepthStencilState(m_depthState, 1);

	// Bind the triangle shaders
	deviceContext->IASetInputLayout(m_inputLayout);
	deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
	deviceContext->PSSetShader(m_pixelShader, nullptr, 0);

	// Bind the vertex buffer
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	// IA stand for "Input Assembler" = the beginning stage of the DirectX programming pipeline
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Draw
	deviceContext->Draw(3, 0);
}
