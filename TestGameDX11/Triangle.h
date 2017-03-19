#pragma once

#include <Macro.h>
#include <DXRenderer.h>
#include <DirectXMath.h>


struct Vertex //Overload Vertex Structure
{
	Vertex() {}
	Vertex(float x, float y, float z,
		float cr, float cg, float cb, float ca)
		: pos(x, y, z), color(cr, cg, cb, ca) {}

	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT4 color;
};

class Triangle {
public:
	Triangle( DXRenderer& _renderer);
	~Triangle();

	void Draw( DXRenderer& _renderer);

	void CreateMesh( DXRenderer& _renderer);
	void CreateShaders( DXRenderer& _renderer);
	void CreateRenderStates(DXRenderer& _renderer);


protected:
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11VertexShader* m_vertexShader = nullptr;
	ID3D11PixelShader* m_pixelShader = nullptr;
	ID3D11InputLayout* m_inputLayout = nullptr; // used to link shaders
	ID3D11RasterizerState* m_rasterizerState = nullptr;
	ID3D11DepthStencilState* m_depthState = nullptr;
	ID3D11BlendState* m_blendState = nullptr;

};