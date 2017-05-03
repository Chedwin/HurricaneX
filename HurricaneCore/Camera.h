//*******************************//
//
// Name:			Camera.h
// Description:		Perspective camera that is used to view the game level.
//
// Author:			Edwin Chen
// Created:			Sep 28, 2016
// Last updated:	May 03, 2017
//
//*******************************//


#ifndef _CAMERA_H
#define _CAMERA_H

#include "Macro.h"
#include "HMath.h"
#include "GameObject.h"

class Scene;

class Camera : public GameObject 
{
	friend class Scene;
protected:
	explicit Camera(Scene& sc);
public:
	virtual ~Camera();

	// ensure we don't have a default and move constructors
	Camera() = delete;
	Camera(const Camera&) = delete;


	virtual void Update(const float _deltaTime) override;
	virtual void Render() override;



	inline void SetPostion(const VEC3& newPos) {
		gameObject->transform.position = newPos;
	}
	inline void SetUp(const VEC3& newUp) {
		_up = newUp;
	}
	inline void SetDir(const VEC3& newDir) {
		_dir = newDir;
	}

protected:
	VEC3 _dir, _up;

//	MATRIX4 _projectionMatrix;
//	MATRIX4 _viewMatrix;
//
//
//public:
//	Frustum frustum;
};

#endif