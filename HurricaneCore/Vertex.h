//*******************************//
//
// Name:			Vertex.h
// Description:		
//					
//
// Author:			Edwin Chen
// Special Thanks:  Daniel Argento, Mark Seaman
//
// Created:			Apr 20, 2017
// Last updated:	Apr 20, 2017
//
//*******************************//


#ifndef _VERTEX_H
#define _VERTEX_H

#include "Macro.h"
#include "HMath.h"

struct Vertex //Overload Vertex Structure
{
	Vertex() {}
	Vertex(float x, float y, float z,
		float cr, float cg, float cb, float ca)
		: pos(x, y, z), color(cr, cg, cb, ca) {}

	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT4 color;
};

#endif