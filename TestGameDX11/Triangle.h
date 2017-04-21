#pragma once

#include <Vertex.h>
#include <DXRenderer.h>

class Triangle {
public:
	Triangle();
	~Triangle();

	bool InitTriangle(DXRenderer& renderer);
	void Render();

public:
	ID3D11Buffer* triangleVertBuffer;

	ID3D11VertexShader* VS;
	ID3D11PixelShader* PS;

	ID3D10Blob* VS_Buffer = NULL;
	ID3D10Blob* PS_Buffer = NULL;
	
	ID3D10Blob* Errors;
	
	ID3D11InputLayout* vertLayout;

	DXRenderer* _renderer;
};