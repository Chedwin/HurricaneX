#include "Triangle.h"

Triangle::Triangle() 
	: VS(nullptr), PS(nullptr), _renderer(nullptr)
{
	// empty
}

Triangle::~Triangle()
{
	if (VS)
		VS->Release();

	if (PS)
		PS->Release();

	if (VS_Buffer)
		VS_Buffer->Release();

	if (PS_Buffer)
		PS_Buffer->Release();

	if (vertLayout)
		vertLayout->Release();
}

bool Triangle::InitTriangle(DXRenderer& renderer)
{
	_renderer = &renderer;

	HRESULT hr = D3DCompileFromFile(L"Effects.fx", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS", "vs_5_0", D3DCOMPILE_DEBUG, 0, &VS_Buffer, &Errors);
	hr = D3DCompileFromFile(L"Effects.fx", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS", "ps_5_0", D3DCOMPILE_DEBUG, 0, &PS_Buffer, &Errors);

	if (Errors || hr != S_OK) {
		OutputDebugStringA(reinterpret_cast<const char*> (Errors->GetBufferPointer()));
		MessageBox(NULL, "Triangle shader(s) compilation FAILED", "FATAL ERROR", 0);
		return false;
	}

	hr = _renderer->GetDevice()->CreateVertexShader(VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), NULL, &VS);
	hr = _renderer->GetDevice()->CreatePixelShader(PS_Buffer->GetBufferPointer(), PS_Buffer->GetBufferSize(), NULL, &PS);
	
	
	_renderer->GetDeviceContext()->VSSetShader(VS, 0, 0);
	_renderer->GetDeviceContext()->PSSetShader(PS, 0, 0);



	Vertex v[] =
	{
		Vertex(0.0f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f),
		Vertex(0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f),
		Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f),
	};
	
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * 3;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	
	D3D11_SUBRESOURCE_DATA vertexBufferData;
	
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = v;
	hr = _renderer->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &triangleVertBuffer);
	
	
	
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	_renderer->GetDeviceContext()->IASetVertexBuffers(0, 1, &triangleVertBuffer, &stride, &offset);
	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);
	
	hr = _renderer->GetDevice()->CreateInputLayout(layout, numElements, VS_Buffer->GetBufferPointer(),
		VS_Buffer->GetBufferSize(), &vertLayout);
	

	
	_renderer->GetDeviceContext()->IASetInputLayout(vertLayout);
		
	_renderer->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	return true;
}

void Triangle::Render()
{
	_renderer->GetDeviceContext()->Draw(3, 0);
}
