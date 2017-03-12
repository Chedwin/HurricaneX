
#include <Macro.h>
#include <Window.h>
#include <DXRenderer.h>

int CALLBACK WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmd, int nShowCmd) 
{
	Window wind(hInst, nShowCmd, 1024, 980);
	DXRenderer renderer(wind);

	MSG msg = { 0 };

	while (true) {
		
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}

		
		renderer.BeginFrame();

		// Game stuff goes in between here!

		renderer.EndFrame();
	}

	return 0;
}