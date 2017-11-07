#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "Macro.h"
#include "D3D11Utility.h"
#include "DXRenderer.h"
#include "ShaderProgram.h"

namespace HurricaneEngine 
{
	
	class Texture {
	public:
		Texture();
		~Texture();


	public:
		bool Init(DXRenderer* _dx, _In_ LPCSTR _fileName);
		ID3D11ShaderResourceView* GetTexture() const;
		int GetWidth() const;
		int GetHeight() const;

	protected:
		ID3D11ShaderResourceView* _texture;
		int _width, _height;
		DXRenderer* _dx;

	};

}

#endif