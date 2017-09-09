//*******************************//
//
// Name:			Model.h
// Description:		Simple Model class that contains data about a model
//					this includes: 
//						vertices, uv coord, normals, name
//
// Author:			Edwin Chen
// Created:			Oct 03, 2016
// Last updated:	Sep 08, 2017
//
//*******************************//

#ifndef _MODEL_H
#define _MODEL_H


#include "Macro.h"
#include "HMath.h"

class Model {
public:
	Model() {}
	virtual ~Model() {}

	virtual void Render() {}

	inline STRING GetModelName() {
		return _name;
	}
	inline void SetModelName(const STRING& n) {
		_name = n;
	}

protected:
	STRING _name;
public:
	VECTOR(VEC3) vertex;
	VECTOR(VEC2) uvs;
	VECTOR(VEC3) normals;

	VECTOR(int) indices;
};

#endif