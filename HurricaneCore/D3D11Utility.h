//*******************************//
//
// Name:			d3dUtil.h
// Description:		Single header for including d3d11 header files
//
// Author:			Edwin Chen
// Special Thanks:  
//
// Created:			May 20, 2017
// Last updated:	Nov 04, 2017
//
//*******************************//

#ifndef _D3D_UTILITY_H
#define _D3D_UTILITY_H

#include <DXGI.h>
#include <d3d11.h>
#include <d3d11sdklayers.h>
#include <d3dcompiler.h>
#include <d3d10.h>

#include <dxgi.h>
#include <d3dcommon.h>

#include <d3dx11tex.h>

#include <DirectXMath.h>
#include <DirectXMathVector.inl>
#include <DirectXColors.h>
#include <DirectXCollision.h>

// We will make sure that the appropriate static libraries are being linked
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3dx11.lib")



#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
//#define HR(x)
//		{                                                          
//			HRESULT hr = (x);                                      
//			if(FAILED(hr))                                         
//			{                                                      
//				DXTrace(__FILE__, (DWORD)__LINE__, hr, x, true); 
//			}                                                      
//		}
#endif

#else
	#ifndef HR
	#define HR(x) (x)
	#endif
#endif 

//---------------------------------------------------------------------------------------
// Convenience macro for releasing COM objects.
//---------------------------------------------------------------------------------------

#define RELEASE_COM(x) { if(x){ x->Release(); x = 0; } }


#endif // end _D3D_UTILITY