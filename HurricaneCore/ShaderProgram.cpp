#include "ShaderProgram.h"
#include "Debug.h"

ShaderProgram::ShaderProgram(const STRING& _name)
	: _vertShd(nullptr), _pixShd(nullptr), _geoShd(nullptr), _compShd(nullptr)
{
	SetShaderName(_name);
}

ShaderProgram::~ShaderProgram()
{
	CleanUpShader();
}



void ShaderProgram::CleanUpShader() 
{
	if (_vertShd)
		_vertShd->Release();

	if (_pixShd)
		_pixShd->Release();

	if (_geoShd)
		_geoShd->Release();

	if (_compShd)
		_compShd->Release();

	_vertShd = nullptr;
	_pixShd  = nullptr;
	_geoShd  = nullptr;
	_compShd = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ShaderProgram::InitShaderProgram(HWND hwnd, ID3D11Device & _d, ID3D11DeviceContext & _dc, const STRING& vsFilename, const STRING& psFilename, const STRING& entryPoint)
{
	SetDevice(_d);
	SetDeviceContext(_dc);

	HRESULT vertHR  = 0;
	HRESULT pixelHR = 0;

	ID3D10Blob* errorMessage			= 0;
	ID3D10Blob* vertexShaderBuffer		= 0;
	ID3D10Blob* pixelShaderBuffer		= 0;

	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;


	// Vertex Shader
	vertHR = LoadShader(vsFilename, entryPoint, vertexShaderBuffer, errorMessage);

	if (vertHR != S_OK) {
		MessageBox(NULL, "Vertex shader loading FAILED", "FATAL ERROR", 0);
		CleanUpShader();
		return false;
	}

	// Pixel shader
	pixelHR = LoadShader(psFilename, entryPoint, pixelShaderBuffer, errorMessage);

	if (pixelHR != S_OK) {
		MessageBox(NULL, "Vertex shader loading FAILED", "FATAL ERROR", 0);
		CleanUpShader();
		return false;
	}



	vertHR = CompileVertexShader(vertexShaderBuffer, _vertShd);
	if (FAILED(vertHR))
		return false;

	pixelHR = CompilePixelShader(pixelShaderBuffer, _pixShd);
	if (FAILED(pixelHR))
		return false;

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
	HRESULT result = _deviceRef->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), &_layout);
	if (FAILED(result))
	{
		return false;
	}

	// Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	result = _deviceRef->CreateBuffer(&matrixBufferDesc, NULL, &_matrixBuffer);
	if (FAILED(result))
		return false;

	return true;
}



HRESULT ShaderProgram::LoadShader(const STRING& _filePath, const STRING& entryPoint, ID3D10Blob* shaderBuffer, ID3D10Blob* errorBuffer)
{
	LPCWSTR fPath = (LPCWSTR)_filePath.c_str();
	HRESULT result = D3DCompileFromFile(fPath, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint.c_str(), "vs_5_0", D3DCOMPILE_DEBUG, 0, &shaderBuffer, &errorBuffer);

	if (FAILED(result))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if (errorBuffer)
		{
			//OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
		{
			LPCSTR concat = (LPCSTR)(_filePath + " file path not found").c_str();
			MessageBox(NULL, concat, "FATAL ERROR", MB_OK);
		}
	}

	return result;
}


#pragma region COMPILE SHADER TYPES

// VERTEX
HRESULT ShaderProgram::CompileVertexShader(ID3D10Blob* shaderBuffer, ID3D11VertexShader* _vert)
{
	HRESULT res = _deviceRef->CreateVertexShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, &_vert);
	return res;
}


// PIXEL
HRESULT ShaderProgram::CompilePixelShader(ID3D10Blob * shaderBuffer, ID3D11PixelShader * _pixel)
{
	HRESULT res = _deviceRef->CreatePixelShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, &_pixel);
	return res;
}

#pragma endregion