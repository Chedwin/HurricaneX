#pragma once

#include "Macro.h"
#include "D3D11Utility.h"

namespace HurricaneEngine 
{
	class Model {
	public:
		Model();
		~Model();

		bool Init();
		void Render();

	protected:
		ID3D11Buffer *_vertexBuffer, *_indexBuffer;
		int _vertexCount, _indexCount;
	};

}

