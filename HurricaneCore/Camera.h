//*******************************//
//
// Name:			Camera.h
// Description:		Perspective camera that is used to view the game level.
//
// Author:			Edwin Chen
// Created:			Sep 28, 2016
// Last updated:	Sep 07, 2017
//
//*******************************//


#ifndef _CAMERA_H
#define _CAMERA_H


#include "Macro.h"
#include "HMath.h"
#include "GameObject.h"


#include "d3dUtil.h"
#include "Transform.h"

class Camera : public GameObject {
	friend class Graphics;
protected:
	explicit Camera(ID3D11Device& _dev, const STRING& camName="");
	void InitCamera(ID3D11Device& _device);

public:
	~Camera() final;

	void Update(const float _dt);
	void Render();

	inline void SetDXDevice(ID3D11Device& _device) {
		device = &_device;
	}

	inline MAT4 GetViewMatrix() const {
		return viewMatrix;
	}

public:
	VEC3 dir, up;

	MAT4 viewMatrix;
	MAT4 projMatrix;

	GameObject* camera; // setting pointer to itself

	ID3D11Device* device;
};

#endif