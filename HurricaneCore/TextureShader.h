#pragma once

#include "Macro.h"
#include "HMath.h"
#include "ShaderProgram.h"

namespace HurricaneEngine 
{


	class TextureShader : public ShaderProgram {
	public:
		TextureShader();
		~TextureShader() final;

		bool InitShader(DXRenderer* _dxR, _In_ LPCWSTR filePath, _In_ LPCWSTR vsFuncName, _In_ LPCWSTR psFuncName) override;
		void Begin(unsigned int _indexCount) override;
		void End() override;

	protected:
		ID3D11SamplerState* _samplerState;
	};

}
