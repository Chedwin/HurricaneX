#include "TextureShader.h"

using namespace HMath;
using namespace HurricaneEngine;

TextureShader::TextureShader() 
	: ShaderProgram(), _samplerState(NULL)
{
}


TextureShader::~TextureShader()
{
	SAFE_RELEASE(_samplerState);
}

bool TextureShader::InitShader(DXRenderer * _dxR, LPCWSTR filePath, LPCWSTR vsFuncName, LPCWSTR psFuncName)
{
	if (!ShaderProgram::InitShader(_dxR, filePath, vsFuncName, psFuncName))
		return false;

	D3D11_SAMPLER_DESC samplerDesc;
	HRESULT result;

	// Create Texture sampler desc
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;

	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;

	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the sample state
	result = _dev->CreateSamplerState(&samplerDesc, &_samplerState);

	if (FAILED(result))
		return false;

	return true;
}

void TextureShader::Begin(unsigned int _indexCount)
{
	_devCon->PSSetSamplers(0, 1, &_samplerState);
	ShaderProgram::Begin(_indexCount);
}

void TextureShader::End()
{
	_devCon->PSSetSamplers(0, 0, NULL);
	ShaderProgram::End();
}
