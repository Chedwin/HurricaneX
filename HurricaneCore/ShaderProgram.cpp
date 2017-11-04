#include "ShaderProgram.h"

using namespace HurricaneEngine;

ShaderProgram::ShaderProgram() : _dx(nullptr)
{
}

ShaderProgram::~ShaderProgram() 
{
	ReleaseObjects();
}

void ShaderProgram::ReleaseObjects()
{
	RELEASE_COM(_VS);
	RELEASE_COM(_PS);
}


bool ShaderProgram::LoadShader(DXRenderer* _dxR, _In_ LPCWSTR filePath)
{
	_dx = _dxR;

	ID3D10Blob* errorMessage = 0;
	ID3D10Blob* vsBuffer = 0;
	ID3D10Blob* psBuffer = 0;

	HRESULT result = 0;
	result = D3DCompileFromFile(filePath, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VSMain", "vs_5_0", D3DCOMPILE_DEBUG, 0, &vsBuffer, &errorMessage);
	result = D3DCompileFromFile(filePath, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PSMain", "ps_5_0", D3DCOMPILE_DEBUG, 0, &psBuffer, &errorMessage);

	if (FAILED(result)) {
		MessageBox(NULL, "LoadShader() FAILED!", "FATAL ERROR", MB_OK);
		ReleaseObjects();
		return false;
	}

	result = _dx->GetDevice()->CreateVertexShader(vsBuffer->GetBufferPointer(), vsBuffer->GetBufferSize(), NULL, &_VS);
	result = _dx->GetDevice()->CreatePixelShader(psBuffer->GetBufferPointer(), psBuffer->GetBufferSize(), NULL, &_PS);

	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;

	// Create the vertex input layout description.
	// This setup needs to match the VertexType stucture in the ModelClass and in the shader.
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	// Get a count of the elements in the layout.
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Create the vertex input layout.
	result = _dx->GetDevice()->CreateInputLayout(polygonLayout, numElements, vsBuffer->GetBufferPointer(),vsBuffer->GetBufferSize(), &_layout);
	if (FAILED(result))
		return false;


	// Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
	RELEASE_COM(vsBuffer);
	RELEASE_COM(psBuffer);

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	result = _dx->GetDevice()->CreateBuffer(&matrixBufferDesc, NULL, &_matrixBuffer);

	if (FAILED(result))
		return false;

	return true;
}

void ShaderProgram::RenderShader(unsigned int _vertCount)
{
	_dx->GetDeviceContext()->Draw(_vertCount, 0);
}
