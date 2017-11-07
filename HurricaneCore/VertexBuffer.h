#ifndef _VERTEX_BUFFER_H
#define _VERTEX_BUFFER_H

#include "Macro.h"
#include "D3D11Utility.h"
#include "DXRenderer.h"
#include "ShaderProgram.h"

namespace HurricaneEngine 
{

	class VertexBuffer {
	public:
		struct VertexType 
		{
			HMath::VEC3 position;
			HMath::VEC2 uv;
		};
	public:
		VertexBuffer();
		~VertexBuffer();

		bool Init(DXRenderer* _dxR, ShaderProgram* _shader, float _size, bool _writeable = false);
		void Render();

		ID3D11Buffer* GetVertexBuffer() const;
		int GetIndiceCount() const;

	public:
		DXRenderer* _dx;

		ID3D11Buffer* _vertBuffer;
		ID3D11Buffer* _indexBuffer;

		ShaderProgram* _shaderProgram;

		int _vertexCount, _indexCount;
	};

}

#endif