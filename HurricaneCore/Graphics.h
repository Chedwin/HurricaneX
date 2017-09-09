#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "DXRenderer.h"
#include "AbstractRenderer.h"
#include "Camera.h"

class HXApp;


class Graphics {
	friend class HXApp;
protected:
	DXRenderer* _dxRenderer;
	Camera*		_camera;

protected:
	Graphics();
	Graphics(const Graphics&);
	~Graphics();

	bool InitGraphics(HWND hwnd, int width, int height, bool isFullScreen = false);
	void ShutdownGraphics();

	void BeginDraw();
	void EndDraw();

public:
	void ClearScreen(float r, float g, float b);

	ID3D11Device* GetDevice() const;
	ID3D11DeviceContext* GetDeviceContext() const;
};

#endif