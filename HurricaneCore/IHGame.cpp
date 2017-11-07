#include "IHGame.h"

using namespace HurricaneEngine;

IHGame::IHGame() 
	: _window(nullptr), _dxRenderer(nullptr), _sceneManager(nullptr),
	_fpsCounter(nullptr)
{
	// empty	
}

IHGame::~IHGame() 
{
	Exit();
}


bool IHGame::InitEngine()
{
	_sceneManager = SCENE_MANAGER;
	_fpsCounter = FPSCounter::GetFPSCounter();
	_input = INPUT;

	_window = new Window32();
	if (!_window->InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT))
		return false;

	_dxRenderer = new DXRenderer();
	if (!_dxRenderer->Initialize(_window->_hwnd, _window->Width(), _window->Height(), _window->IsFullScreen() ))
		return false;

	

	return true;
}

void IHGame::AddScene(IScene* _scene) 
{
	if (!_sceneManager)
		return;

	_sceneManager->AddScene(_scene);
}


void IHGame::Exit()
{
	_sceneManager = nullptr;

	SAFE_DELETE(_dxRenderer);
	SAFE_DELETE(_window);
}



int IHGame::Run()
{
	if (!(_isRunning = InitEngine())) 
	{
		MessageBox(NULL, "Engine Initialization FAILED", "FATAL ERROR", 0);
		return 0;
	}

	if (!(_isRunning = InitGame()))
	{
		MessageBox(NULL, "Game Initialization FAILED", "FATAL ERROR", 0);
		return 0;
	}

	MSG msg = { 0 };

	_fpsCounter->Initialize();
	_timer.Reset();
	_timer.Start();

	while (msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// Otherwise, do animation/game stuff.
		else
		{
			_timer.Tick();

			if (_isRunning)
			{
				GameLoop();
			}
			else
			{
				Sleep(100);
			}

			_fpsCounter->Frame();
			_fps = _fpsCounter->GetFPS();
		}
	}

	return (int)msg.wParam;
}

void IHGame::GameLoop() 
{
	Update(_timer.DeltaTime());

	_dxRenderer->BeginFrame(0, 0, 0.4f);

	Render();

	_dxRenderer->EndFrame();
}

void IHGame::Update(const float _deltaTime)
{
	_sceneManager->UpdateScene(_deltaTime);
}

void IHGame::Render()
{
	_sceneManager->RenderScene();
}


void IHGame::SetWindowTitle(const STRING& _string)
{
	_window->SetWindowTitleText(_string);
}





// Static Win32 Procedure Function that receives message from the game window
// Input calls are here
LRESULT CALLBACK IHGame::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg) {
	case WM_PAINT:
		PAINTSTRUCT ps;
		BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		return 0;

		// Check if a key has been pressed on the keyboard
	case WM_KEYDOWN:
		if (wparam == VK_ESCAPE)
		{
			if (MessageBox(0, "Are you sure you want to exit?", "Exit Game?", MB_YESNO | MB_ICONQUESTION) == IDYES)
				DestroyWindow(hwnd);
		}
		//INPUT->KeyDown((unsigned int)wparam);
		return 0;

		// Get Mouse Cursor Position
	case WM_MOUSEMOVE:
		INPUT->SetMousePos((unsigned int)GET_X_LPARAM(lparam), (unsigned int)GET_Y_LPARAM(lparam));
		return 0;

		// Check if a key has been released on the keyboard
	case WM_KEYUP:
		// If a key is released then send it to the input object so it can unset the state for that key
		//INPUT->KeyUp((unsigned int)wparam);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

		// Any other messages send to the default message handler as our application won't make use of them
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

}
