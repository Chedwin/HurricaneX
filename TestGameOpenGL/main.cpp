
#include <Macro.h>
#include "OpenGLGame.h"


int CALLBACK WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmd, int nShowCmd)
{
#if defined(DEBUG) || defined(_DEBUG)
	// Avoid memory leaks by catching them
	// Won't catch all of them (but you gotta catch 'em all right? lol)
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	_CrtSetDbgFlag(_CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetDbgFlag(_CRTDBG_CHECK_ALWAYS_DF);
#endif

	static_assert(sizeof(void*) == 4, "64-bit code generation not supported!\n");


	OpenGLGame* game = new OpenGLGame();
	game->Run(hInst);

	delete game;
	game = nullptr;


	// Dump any memory leaks in DEBUG mode
#if defined(DEBUG) || defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}