#include "ShaderProgram.h"
#include "Debugger.h"

using namespace HMath;
using namespace HurricaneEngine;

ShaderProgram::ShaderProgram()
{
	// empty
}

ShaderProgram::~ShaderProgram() 
{
	ReleaseObjects();
}

void ShaderProgram::ReleaseObjects()
{
	RELEASE_COM(_VS);
	RELEASE_COM(_PS);
	RELEASE_COM(_layout);
	RELEASE_COM(_matrixBuffer);
}


bool ShaderProgram::InitShader(DXRenderer* _dxR, _In_ LPCWSTR filePath, _In_ LPCWSTR vsFuncName, _In_ LPCWSTR psFuncName) 
{
	_dx = _dxR;
	_dev = _dx->GetDevice();
	_devCon = _dx->GetDeviceContext();

	HRESULT result = 0;
	ID3D10Blob* errorMessage = 0;
	ID3D10Blob* vsBuffer = 0;
	ID3D10Blob* psBuffer = 0;

	// Compile Vertex Shader
	result = D3DCompileFromFile(filePath, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VSMain", "vs_5_0", D3DCOMPILE_DEBUG, 0, &vsBuffer, &errorMessage);
	// Compile Pixel shader
	result = D3DCompileFromFile(filePath, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PSMain", "ps_5_0", D3DCOMPILE_DEBUG, 0, &psBuffer, &errorMessage);

	if (FAILED(result)) 
	{
		MessageBox(NULL, "LoadShader() FAILED!", "FATAL ERROR", MB_OK);
		ReleaseObjects();
		return false;
	}

	// Create vertex shader buffer
	result = _dev->CreateVertexShader(vsBuffer->GetBufferPointer(), vsBuffer->GetBufferSize(), NULL, &_VS);
	// Create pixel shader buffer
	result = _dev->CreatePixelShader(psBuffer->GetBufferPointer(), psBuffer->GetBufferSize(), NULL, &_PS);

	_devCon->VSSetShader(_VS, 0, 0);
	_devCon->PSSetShader(_PS, 0, 0);

	if (FAILED(result))
	{
		MessageBox(NULL, "LoadShader() FAILED!", "FATAL ERROR", MB_OK);
		ReleaseObjects();
		return false;
	}

	// Setup the layout of the data that goes into the shader
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];

	// Create the vertex input layout description.
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;


	unsigned int numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]); 

	// Create the vertex input layout
	result = _dev->CreateInputLayout(polygonLayout, numElements, vsBuffer->GetBufferPointer(), vsBuffer->GetBufferSize(), &_layout);
	if (FAILED(result))
	{
		MessageBox(NULL, "LoadShader() FAILED!", "FATAL ERROR", MB_OK);
		ReleaseObjects();
		return false;
	}

	// Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
	RELEASE_COM(vsBuffer);
	RELEASE_COM(psBuffer);

	// Set up the matrix buffer description
	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC matrixBufferDesc;

	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	result = _dev->CreateBuffer(&matrixBufferDesc, NULL, &_matrixBuffer);
	if (FAILED(result))
	{
		MessageBox(NULL, "LoadShader() FAILED!", "FATAL ERROR", MB_OK);
		ReleaseObjects();
		return false;
	}


	return true;
}


bool HurricaneEngine::ShaderProgram::SetShaderParameters(DXRenderer* _d, ID3D11ShaderResourceView* _texture)
{
	_devCon->PSSetShaderResources(0, 1, &_texture);

	return true;
}

bool HurricaneEngine::ShaderProgram::SetShaderParameters(DXRenderer* _d, HMath::MAT4 _world, HMath::MAT4 _proj, HMath::MAT4 _view)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;


	// transpose all matrices
	_world = TRANSPOSE_MATRIX(_world);
	_proj = TRANSPOSE_MATRIX(_proj);
	_view = TRANSPOSE_MATRIX(_view);

	// Lock buffer
	result = _devCon->Map(_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	if (FAILED(result)) 
	{
		MessageBox(NULL, "SetShaderParameters() FAILED!", "FATAL ERROR", MB_OK);
		return false;
	}

	dataPtr = (MatrixBufferType*)mappedResource.pData;
	dataPtr->world = _world;
	dataPtr->projection = _proj;
	dataPtr->view = _view;

	// Unlock buffer
	_devCon->Unmap(_matrixBuffer, 0);


	// Update the values in the shader
	_devCon->VSSetConstantBuffers(0, 1, &_matrixBuffer);

	return true;
}

void ShaderProgram::Begin(unsigned int _indexCount)
{
	_devCon->IASetInputLayout(_layout);
	_devCon->VSSetShader(_VS, NULL, 0);
	_devCon->PSSetShader(_PS, NULL, 0);

	_devCon->DrawIndexed(_indexCount, 0, 0);
}

void ShaderProgram::End() 
{
	_devCon->IASetInputLayout(NULL);
	_devCon->VSSetShader(NULL, NULL, 0);
	_devCon->PSSetShader(NULL, NULL, 0);
}