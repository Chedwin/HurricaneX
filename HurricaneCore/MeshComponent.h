//*******************************//
//
// Name:			MeshManager.h
// Description:		Loads and manages several types of meshs ranging in different formats (i.e. fbx, obj)
//					Makes use of Assimp (Asset Importer) to retrieve vertices, faces, uvs, etc. from meshs
//
// Author:			Edwin Chen
// Created:			Oct 03, 2016
// Last updated:	Sep 00, 2017
//
//*******************************//

#ifndef _Mesh_COMPONENT_H
#define _Mesh_COMPONENT_H

#include "Macro.h"
#include "d3dUtil.h"
#include "HMath.h"
#include "Component.h"
#include "Model.h"

class MeshComponent : public Component {
public:

	struct VertexType {
		VEC3 pos;
		VEC4 color;
	};

public:
	explicit MeshComponent(GameObject* g, ID3D11Device* device);
	~MeshComponent() final;

	bool InitMeshComp(ID3D11Device* device);
	void DestroyComponent();
	void Render();

	// Inline Subroutines
	inline STRING GetMeshName() const {
		return _meshName;
	}
	inline int GetVertexCount() const {
		return _vertexCount;
	}
	inline void SetMeshName(const STRING& _name) {
		_meshName = _name;
	}
protected:
	ID3D11Device* _deviceRef;

	ID3D11Buffer* _vertexBuffer;
	ID3D11Buffer* _indexBuffer;

	int _vertexCount, _indexCount;
	
	STRING _meshName;

public:
	VECTOR(VEC3) vertex;
	VECTOR(VEC2) uvs;
	VECTOR(VEC3) normals;

	VECTOR(int) indices;
};

#endif 