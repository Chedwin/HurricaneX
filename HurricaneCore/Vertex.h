//*******************************//
//
// Name:			Vertex.h
// Description:		
//					
//
// Author:			Edwin Chen
// Special Thanks:  Daniel Argento, Mark Seaman, Scott Fielder
//
// Created:			Apr 20, 2017
// Last updated:	Nov 02, 2017
//
//*******************************//


#ifndef _VERTEX_H
#define _VERTEX_H

#include "Macro.h"
#include "HMath.h"

namespace HurricaneEngine 
{

	//Overload Vertex Structure
	struct Vertex
	{
		Vertex() :
			pos(0.0f, 0.0f, 0.0f) {}

		Vertex(float x, float y, float z)
			: pos(x, y, z) {}

		Vertex(float x, float y, float z,
			float u, float v)
			: pos(x, y, z), uv(u, v) {}

		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 uv;
	};

}

#endif