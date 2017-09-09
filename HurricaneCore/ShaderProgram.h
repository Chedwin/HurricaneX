//*******************************//
//
// Name:			ShaderProgram.h
// Description:		Basic compiled HLSL shader programs
//					Only holds links a vertex and a pixel (fragment) shader together at the moment
//
// Author:			Edwin Chen
// Created:			Sep 30, 2016
// Last updated:	Sep 08, 2017
//
//*******************************//

#ifndef _SHADER_PROGRAM_H
#define _SHADER_PROGRAM_H

#include "Macro.h"
#include "d3dUtil.h"
#include "HXApp.h"

class ShaderProgram {
public:
	enum SHADERTYPE : unsigned int
	{
		VERTEX		= 0,
		PIXEL		= 1,
		GEOMETRY	= 2,
		TESSELATION = 3
	};

	struct MatrixBufferType
	{
		MAT4 world;
		MAT4 view;
		MAT4 projection;
	};

protected:
	HRESULT CompileVertexShader(ID3D10Blob* shaderBuffer, ID3D11VertexShader* _vert);
	HRESULT CompilePixelShader(ID3D10Blob* shaderBuffer, ID3D11PixelShader* _pixel);

public:
	explicit ShaderProgram(const STRING& _name);
	virtual ~ShaderProgram();

	// We'll use this to ensure that the entry point to BOTH of the shaders is the same for the entire compiled shader program
	bool InitShaderProgram(HWND hwnd, ID3D11Device& _d, ID3D11DeviceContext& _dc, const STRING& vsFilename, const STRING& psFilename, const STRING& entryPoint);

	// Load and compile each individual shader (ie. vertex, geometry, pixel, etc)
	HRESULT LoadShader(const STRING& _filePath, const STRING& entryPoint, ID3D10Blob* shaderBuffer, ID3D10Blob* errorBuffer);



	void CleanUpShader();

	inline void SetShaderName(const STRING& _name) {
		_shaderName = _name;
	}

	inline void SetDeviceContext(ID3D11DeviceContext& _dc) {
		_deviceContextRef = &_dc;
	}
	inline void SetDevice(ID3D11Device& _d) {
		_deviceRef = &_d;
	}

private:
	STRING _shaderName;

protected:
	ID3D11VertexShader*		_vertShd;     // Vertex shader
	ID3D11PixelShader*		_pixShd;		 // Pixel shader (ie. fragment shader)
	ID3D11ComputeShader*	_compShd;	 // Compute shader
	ID3D11GeometryShader*	_geoShd;	     // Geometry shader

	ID3D11DeviceContext*	_deviceContextRef;
	ID3D11Device*			_deviceRef;

	ID3D11InputLayout*		_layout;
	ID3D11Buffer*			_matrixBuffer;
};

#endif