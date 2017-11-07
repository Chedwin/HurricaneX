//*******************************//
//
// Name:			ShaderProgram.h
// Description:		Basic compiled HLSL shader programs
//					Only holds links a vertex and a pixel (fragment) shader together at the moment
//
// Author:			Edwin Chen
// Created:			Sep 30, 2016
// Last updated:	Nov 04, 2017
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
			HMath::MAT4 world;
			HMath::MAT4 view;
			HMath::MAT4 projection;
		};

	protected:
		STRING	_shaderName;
		STRING	_shaderFilePath;
		bool	_initialized = false;

		ID3D11VertexShader* _VS;
		ID3D11PixelShader*  _PS;
		DXRenderer*			_dx;

		ID3D11Device*			_dev;
		ID3D11DeviceContext*	_devCon;

		ID3D11InputLayout*		_layout;
		ID3D11Buffer*			_matrixBuffer;


	protected:
	public:
		ShaderProgram();
		virtual ~ShaderProgram();

		void ReleaseObjects();

		virtual bool InitShader(DXRenderer* _dxR, _In_ LPCWSTR filePath, _In_ LPCWSTR vsFuncName, _In_ LPCWSTR psFuncName);
		


		bool SetShaderParameters(DXRenderer* _d, ID3D11ShaderResourceView* _texture);
		bool SetShaderParameters(DXRenderer* _d, HMath::MAT4 _world, HMath::MAT4 _proj, HMath::MAT4 _view);

		virtual void Begin(unsigned int _vertCount);
		virtual void End();


		// INLINE
		inline STRING GetName() const {
			return _shaderName;
		}
		inline STRING GetFilePath() const {
			return _shaderFilePath;
		}
	};

} // end namespace HurricaneEngine

#endif