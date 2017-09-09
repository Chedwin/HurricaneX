#include <Macro.h>
#include <Debug.h>


#include "AwesomeGame2D.h"

#define WIDTH  1024
#define HEIGHT 760

#pragma region MAIN ENTRY POINT

int main(int argc, char** argv) 
{
	AwesomeGame2D* myGame = new AwesomeGame2D();

	bool fullScreen = false;

	bool initEngine = myGame->InitEngine(WIDTH, HEIGHT, fullScreen);
	bool game = myGame->InitGame();

	if (!initEngine || !game) 
	{
		MessageBox(NULL, "Initialization of the main game FAILED", "FATAL ERROR", 0);
	}
	else 
	{
		// Run the game loop!
		myGame->MessageLoop();
	}

	if (myGame)
		delete myGame;
	myGame = nullptr;

	return 0;
}

#pragma endregion