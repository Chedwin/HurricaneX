#include <Macro.h>
#include <Debug.h>
#include "DirectXTestGame.h"


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
//	UNREFERENCED_PARAMETER(hPrevInstance);
//	UNREFERENCED_PARAMETER(lpCmdLine);
//
//	static_assert(sizeof(void*) == 4, "64-bit code generation not supported!\n");
//
//	// Initialize console
//	if (!AllocConsole()) 
//	{
//		MessageBox(NULL, "FAILED to create console!", "FATAL ERROR", 0);
//		return 0;
//	}
//	freopen("CONOUT$", "w", stdout);
//
//
//	// Init Debugging
//#if defined(DEBUG) || defined(_DEBUG)
//
//	// Engine debugger
//	Debug::Init();
//
//	// Avoid memory leaks by catching them
//	// Won't catch all of them (but you gotta catch 'em all right? lol)
//	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
//	_CrtSetDbgFlag(_CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//	_CrtSetDbgFlag(_CRTDBG_CHECK_ALWAYS_DF);
//#endif
//
//
//
//
//	DirectXTestGame* myGame = new DirectXTestGame();
//
//	bool fullScreen = false;
//
//	bool initEngine = myGame->InitEngine(hInstance, 800, 600, fullScreen);
//	bool game	    = myGame->InitGame();
//
//	if (!initEngine || !game)
//	{
//		MessageBox(NULL, "Initialization of the main game FAILED", "FATAL ERROR", 0);
//	}
//	else 
//	{
//		// Run the game loop!
//		myGame->MessageLoop();
//	}
//
//	if (myGame)
//		delete myGame;
//	myGame = nullptr;
//
//
//	if (!FreeConsole()) 
//		MessageBox(NULL, "FAILED to free console!", "FATAL ERROR", 0);
//
//
//	// Dump any memory leaks in DEBUG mode
//#if defined(DEBUG) || defined(_DEBUG)
//	_CrtDumpMemoryLeaks();
//#endif

	return 0;
}