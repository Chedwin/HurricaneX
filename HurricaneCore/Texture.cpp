#include "Texture.h"

using namespace HMath;
using namespace HurricaneEngine;

Texture::Texture()
{
	_texture = nullptr;
	_dx = nullptr;
	_width = _height = 0;
}

Texture::~Texture()
{
	RELEASE_COM(_texture);
}

bool Texture::Init(DXRenderer* _dx, LPCSTR _fileName)
{
	// Load the texture
	HRESULT result = D3DX11CreateShaderResourceViewFromFile(_dx->GetDevice(), _fileName, NULL, NULL, &_texture, NULL);
	if (FAILED(result)) 
	{
		MessageBox(NULL, "Texture loading FAILED", "ERROR", NULL);
		return false;
	}

	ID3D11Resource* resource = 0;
	_texture->GetResource(&resource);

	ID3D11Texture2D* texture2D;
	result = resource->QueryInterface(&texture2D);
	if (SUCCEEDED(result)) 
	{
		D3D11_TEXTURE2D_DESC desc;
		texture2D->GetDesc(&desc);
		_width = desc.Width;
		_height = desc.Height;

	}

	RELEASE_COM(resource);
	RELEASE_COM(texture2D);

	return true;
}

ID3D11ShaderResourceView* Texture::GetTexture() const
{
	return _texture;
}

int Texture::GetWidth() const
{
	return _width;
}

int Texture::GetHeight() const
{
	return _height;
}
