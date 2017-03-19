#include "Game.h"
#include "Clock.h"
#include "DXRenderer.h"
#include "GLRenderer.h"

Game* Game::_instance = nullptr;


Game* Game::GetInstance()
{
	if (_instance == nullptr) {
		_instance = new Game();
	}
	return _instance;
}


Game::Game() : gameWindow(nullptr), renderer(nullptr)
{
	// empty
}


Game::~Game()
{
	DestroySystems();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Game::InitEngine(HINSTANCE _hInst)
{
	Clock::init();

	hProps = H_PROPERTIES;

	gameWindow = new Window(_hInst, hProps->GetVideoProperties()->screenWidth , hProps->GetVideoProperties()->screenHeight);

//#define HURRICANE_OPENGL
#if defined(HURRICANE_OPENGL)
	/*GLenum error = glewInit();
	if (error != GLEW_OK) {
		MessageBox(gameWindow->GetHandle(), "GLEW initialization FAILED", "Error", 0);
		exit(0);
	}*/
	renderer = new GLRenderer(*gameWindow);
#else
	renderer = new DXRenderer(*gameWindow);
#endif

	if (!renderer) {
		MessageBox(0, "Renderer FAILED to initialize!", "FATAL ERROR", 0);
		return false;
	}

	return true;
}

void Game::DestroySystems()
{
	if (renderer)
		delete renderer;

	if (gameWindow)
		delete gameWindow;

	renderer = nullptr;
	gameWindow = nullptr;
}

void Game::Run(HINSTANCE _hInst) 
{
	bool init = InitEngine(_hInst);

	if (!init)
	{
		MessageBox(0, "Engine initialization FAILED", "Fatal Error", 0);
		exit(0);
	}
	else
	{
		_isRunning = true;

		// Allow the game to initialize its own special options
		InitGame();

		// Now start the game loop
		GameLoop();
	}
}


void Game::EngineUpdate(const float _deltaTime)
{
}

void Game::GameLoop()
{
	MSG msg = { 0 };

	while (_isRunning) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}
		else 
		{
			// TODO: get frames per second for timestep stuff
			float timeStep = 0.2f; 
			EngineUpdate(timeStep);
			GameUpdate(timeStep);

			renderer->BeginFrame();

			// Game stuff goes in between here!
			GameRender();

			renderer->EndFrame();

	//#if defined(HURRICANE_OPENGL)
	//		SwapBuffers(Window::hDC);
	//#endif
		
		}
	}

}