#include "MeshComponent.h"



MeshComponent::MeshComponent(GameObject* g, ID3D11Device* device)
	: _deviceRef(nullptr), _vertexBuffer(nullptr), _indexBuffer(nullptr),
	  _vertexCount(0), _indexCount(0),
	Component(g, COMPONENT_TYPE::Renderable)
{
	InitMeshComp(device);
}


MeshComponent::~MeshComponent()
{
	DestroyComponent();
}

bool MeshComponent::InitMeshComp(ID3D11Device* device)
{
	_deviceRef = device;



	return true;
}

void MeshComponent::DestroyComponent() 
{

}

void MeshComponent::Render() 
{

}