#include "VertexBuffer.h"
#include "Vertex.h"
using namespace HMath;
using namespace HurricaneEngine;


VertexBuffer::VertexBuffer() 
{ 
	_vertBuffer = nullptr;
	_indexBuffer = nullptr;
}


VertexBuffer::~VertexBuffer()
{
	RELEASE_COM(_vertBuffer);
	RELEASE_COM(_indexBuffer);
}

bool VertexBuffer::Init(DXRenderer* _dxR, ShaderProgram* _shader, float _size, bool _writeable)
{
	_dx = _dxR;
	_shaderProgram = _shader;

	unsigned long* indices;

	HRESULT result;

	_vertexCount = 4;
	_indexCount = 6;

	Vertex v[] =
	{
		Vertex(-0.5, -0.5, 0.0f, 0.0f, 1.0f),
		Vertex(-0.5, 0.5, 0.0f, 0.0f, 0.0f),
		Vertex(0.5, 0.5, 0.0f, 1.0f, 0.0f),
		Vertex(0.5, -0.5, 0.0f, 1.0f, 1.0f),
	};

	VertexType _vertices[4];
	indices = new unsigned long[_indexCount];


	float halfSize = _size / 2.0f;

	_vertices[0].position = VEC3(-halfSize, -halfSize, 0.0f);
	_vertices[0].uv = VEC2(0, 1);

	_vertices[1].position = VEC3(-halfSize, halfSize, 0.0f);
	_vertices[1].uv = VEC2(0, 0);

	_vertices[2].position = VEC3(halfSize, halfSize, 0.0f);
	_vertices[2].uv = VEC2(1, 0);

	_vertices[3].position = VEC3(halfSize, -halfSize, 0.0f);
	_vertices[3].uv = VEC2(1, 1);


	// Load the indices
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;



	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;


	// set up the vertex buffer description
	vertexBufferDesc.Usage = (_writeable) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * 4;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// set up the vertex data
	vertexData.pSysMem =  _vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Create the vertex buffer

	result = _dx->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &_vertBuffer);
	if (FAILED(result)) 
	{
		MessageBox(NULL, "Vertex Buffer initialization FAILED", "ERROR", 0);
		return false;
	}
	
	// Set up the index buffer
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * _indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer
	result = _dx->GetDevice()->CreateBuffer(&indexBufferDesc, &indexData, &_indexBuffer);
	if (FAILED(result))
	{
		MessageBox(NULL, "Vertex Buffer initialization FAILED", "ERROR", 0);
		return false;
	}

	// Release 
	SAFE_DELETE_ARRAY(indices);

	return true;
}


void VertexBuffer::Render() 
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	_shaderProgram->Begin(_indexCount);

	_dx->GetDeviceContext()->IASetVertexBuffers(0, 1, &_vertBuffer, &stride, &offset);
	_dx->GetDeviceContext()->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	_dx->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}


ID3D11Buffer* HurricaneEngine::VertexBuffer::GetVertexBuffer() const
{
	return _vertBuffer;
}

int HurricaneEngine::VertexBuffer::GetIndiceCount() const
{
	return _indexCount;
}
