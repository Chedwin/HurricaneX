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
			float cr, float cg, float cb, float ca)
			: pos(x, y, z), color(cr, cg, cb, ca) {}

		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT4 color;
	};

}

#endif