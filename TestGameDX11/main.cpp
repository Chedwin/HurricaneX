#include "DirectXTestGame.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	DirectXTestGame myGame;

	bool fullScreen = false;

	bool window	   = myGame.InitWindow(hInstance, 800, 600, fullScreen);
	bool renderer  = myGame.InitRenderer();
	bool game	   = myGame.InitGame();

	if (!window || !renderer || !game)
	{
		MessageBox(NULL, "Initialization of the main game FAILED", "FATAL ERROR", 0);
	}
	else 
	{
		myGame.MessageLoop();
	}

	return 0;
}