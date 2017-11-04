//*******************************//
//
// Name:			ShaderProgram.h
// Description:		Basic compiled HLSL shader programs
//					Only holds links a vertex and a pixel (fragment) shader together at the moment
//
// Author:			Edwin Chen
// Created:			Sep 30, 2016
// Last updated:	Nov 02, 2017
//
//*******************************//

#ifndef _SHADER_PROGRAM_H
#define _SHADER_PROGRAM_H

#include "Macro.h"
#include "D3D11Utility.h"
#include "DXRenderer.h"

namespace HurricaneEngine 
{

	class ShaderProgram {
	public:
		struct MatrixBufferType
		{
			MAT4 world;
			MAT4 view;
			MAT4 projection;
		};

	protected:
		ID3D11VertexShader* _VS;
		ID3D11PixelShader* _PS;
		DXRenderer* _dx;

		ID3D11InputLayout*		_layout;
		ID3D11Buffer*			_matrixBuffer;

	public:
		ShaderProgram();
		~ShaderProgram();

		void ReleaseObjects();
		bool LoadShader(DXRenderer* _dxR, _In_ LPCWSTR filePath);

		void RenderShader(unsigned int _vertCount);

	};

}

#endif