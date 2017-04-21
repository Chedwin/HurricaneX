#include "DirectXTestGame.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	DirectXTestGame myGame;

	bool window = myGame.InitWindow(hInstance, 800, 600, true);
	bool renderer = myGame.InitRenderer(hInstance);
	bool game = myGame.InitGame();

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

//#include <stdio.h>
//
//#pragma comment(lib, "d3d11.lib")
//#pragma comment(lib, "d3d10.lib")
//#pragma comment(lib, "d3dcompiler.lib")
//
//#include <windows.h>
//#include <DXGI.h>
//#include <d3d11.h>
//#include <d3d11sdklayers.h>
//#include <d3dcompiler.h>
//#include <d3d10.h>
//#include <DirectXMath.h>
//
//
//ID3D11Buffer* triangleVertBuffer;
//ID3D11VertexShader* VS;
//ID3D11PixelShader* PS;
//ID3D10Blob* VS_Buffer = NULL;
//ID3D10Blob* PS_Buffer = NULL;
//
//ID3D10Blob* Errors;
//
//ID3D11InputLayout* vertLayout;
//
//
//struct Vertex //Overload Vertex Structure
//{
//	Vertex() {}
//	Vertex(float x, float y, float z,
//		float cr, float cg, float cb, float ca)
//		: pos(x, y, z), color(cr, cg, cb, ca) {}
//
//	DirectX::XMFLOAT3 pos;
//	DirectX::XMFLOAT4 color;
//};
//
///**Create the input layout object, this tells Direct3D what our vertex structure consists of, and
//what to do with each component in our vertex struct. We provide the information to Direct3D with an
//array of D3D11_INPUT_ELEMENT_DESC elements. Each element in the D3D11_INPUT_ELEMENT_DESC array describes
//one element in the vertex structure.
//**/
//D3D11_INPUT_ELEMENT_DESC layout[] =
//{
//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//};
//UINT numElements = ARRAYSIZE(layout);
//
//IDXGISwapChain* SwapChain; //changes front buffer to back buffer and vise versa aka double rendering
//ID3D11Device* d3d11Device; //represents the GPU
//ID3D11DeviceContext* d3d11DevCon; // allows for multi-thread rendering calls.
//								
//ID3D11RenderTargetView* renderTargetView;
//
////LPCTSTR WndClassName = _T("HGAME");
//HWND hwnd = NULL;
//HRESULT	hr; //used for error checking
//
//const int Width = 800;
//const int Height = 600;
//
//bool InitWindow(HINSTANCE hInstance, int ShowWnd, int width, int height, bool windowed);
//bool InitializeDirect3D11App(HINSTANCE hInstance); //Will init Direct3D
//void ReleaseObjects();	//Release objects we don't need to prevent memory leaks
//bool InitScene();		//set up a scene
//void UpdateScene();		//Update scene per-frame
//void DrawScene();		//Draw scene to screen, also updated per-frame
//int messageloop();
//
//LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
//{
//	//register the window, will return true or false based on if the window was registered and created
//	if (!InitWindow(hInstance, nShowCmd, Width, Height, true))
//	{
//		MessageBox(0, "Window Initialization - Failed", "Error", MB_OK);
//		return 0;
//	}
//
//	if (!InitializeDirect3D11App(hInstance)) //Initialize Direct3D
//	{
//		MessageBox(0, "Direct3D Initialization - Failed ",
//			"Error", MB_OK);
//		return 0;
//	}
//
//	if (!InitScene()) //Initialize our Scene
//	{
//		MessageBox(0, "Scene Initialization - Failed ",
//			"Error", MB_OK);
//		return 0;
//	}
//
//	messageloop();
//
//	ReleaseObjects();
//	return 0;
//}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//bool InitWindow(HINSTANCE hInstance, int ShowWnd, int width, int height, bool windowed)
//{
//	//create an extended styles windows class called wc, then fill out all the properties. 
//	WNDCLASSEX wc;
//
//	wc.cbSize = sizeof(WNDCLASSEX);
//	wc.style = CS_HREDRAW | CS_VREDRAW;
//	wc.lpfnWndProc = WndProc;
//	wc.cbClsExtra = NULL;
//	wc.cbWndExtra = NULL;
//	wc.hInstance = hInstance;
//	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
//	wc.lpszMenuName = NULL;
//	wc.lpszClassName = "HGAME";
//	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
//
//	//register the class, if it fails we get an error. If it passes we move on to create the window
//	if (!RegisterClassEx(&wc))
//	{
//		MessageBox(NULL, "Error registering class", "Error", MB_OK | MB_ICONERROR);
//		return 1;
//	}
//
//	//create the window
//	hwnd = CreateWindowEx(NULL, "HGAME", "Grub", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
//		CW_USEDEFAULT, width, height, NULL, NULL, hInstance, NULL);
//
//	if (!hwnd)
//	{
//		MessageBox(NULL, "Error Creating Window", "Error", MB_OK | MB_ICONERROR);
//		return 1;
//	}
//
//	//we need to now show the window and refresh it using UpdateWindow()
//	ShowWindow(hwnd, ShowWnd);
//
//	/** send a WM_PAINT message directly to the windows procedure. If there isn't anything in the client area
//	of the window, then UpdateWindow() does not send a message. We then return true so our WinMain()
//	function can get on to the message loop.
//	**/
//	UpdateWindow(hwnd);
//
//	return true;
//}
//
//
//bool InitializeDirect3D11App(HINSTANCE hInstance)
//{
//
//	//Describe our Buffer
//	DXGI_MODE_DESC bufferDesc;
//
//	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));
//
//	bufferDesc.Width = Width;						//Width of resolution
//	bufferDesc.Height = Height;						//Height of resolution
//	bufferDesc.RefreshRate.Numerator = 60;
//	bufferDesc.RefreshRate.Denominator = 1;			//Describes refresh rate in hertz 60/1 = 60hz
//	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //Describes format of the display 8 bits allocated for each
//	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; //Describes the order the rasterizer will render onto a surface, because were using double rendering the order doesnt really matter
//	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; //Describes how an image will be stretched to fit a monitors resolution
//
//														//Describe our swap chain
//	DXGI_SWAP_CHAIN_DESC swapChainDesc;
//
//	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
//
//	swapChainDesc.BufferDesc = bufferDesc;	//Describes the BackBuffer
//	swapChainDesc.SampleDesc.Count = 1;
//	swapChainDesc.SampleDesc.Quality = 0;	//Describes the Multi-Sampling
//	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //Decribes the access the cpu has to the surface of the backbuffer
//	swapChainDesc.BufferCount = 1;			//number of back buffers to be used, can use more if wanted
//	swapChainDesc.OutputWindow = hwnd;		//Handle to our window
//	swapChainDesc.Windowed = TRUE;			//True for windowed, False for full-screen CARE WITH FULL-SCREEN
//	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; //What the display driver should do with th front buffer after swaping it with the back-buffer. In this case we let it decide what the most efficient setting is
//	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; //changes resolution when swapping windowed - fullscreen
//
//	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
//		D3D11_SDK_VERSION, &swapChainDesc, &SwapChain, &d3d11Device, NULL, &d3d11DevCon);
//
//
//	ID3D11Texture2D* BackBuffer;
//	hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
//
//
//
//	hr = d3d11Device->CreateRenderTargetView(BackBuffer, NULL, &renderTargetView);
//	BackBuffer->Release(); //Relase it when we dont need it anymore
//
//
//
//	d3d11DevCon->OMSetRenderTargets(1, &renderTargetView, NULL);
//
//	return true;
//}
//
//
//void ReleaseObjects()
//{
//	//Release the COM objects we created not doing this will cause memory leaks
//	SwapChain->Release();
//	d3d11Device->Release();
//	d3d11DevCon->Release();
//	renderTargetView->Release();
//	triangleVertBuffer->Release();
//	VS->Release();
//	PS->Release();
//	VS_Buffer->Release();
//	PS_Buffer->Release();
//	vertLayout->Release();
//}
//
//
//bool InitScene()
//{
//	//Compile shaders from shader file
//
//	hr = D3DCompileFromFile(L"Effects.fx", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS", "vs_5_0", D3DCOMPILE_DEBUG, 0, &VS_Buffer, &Errors);
//	hr = D3DCompileFromFile(L"Effects.fx", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS", "ps_5_0", D3DCOMPILE_DEBUG, 0, &PS_Buffer, &Errors);
//
//	if (Errors)
//	{
//		OutputDebugStringA(reinterpret_cast<const char*> (Errors->GetBufferPointer()));
//	}
//
//
//	hr = d3d11Device->CreateVertexShader(VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), NULL, &VS);
//	hr = d3d11Device->CreatePixelShader(PS_Buffer->GetBufferPointer(), PS_Buffer->GetBufferSize(), NULL, &PS);
//
//
//
//	d3d11DevCon->VSSetShader(VS, 0, 0);
//	d3d11DevCon->PSSetShader(PS, 0, 0);
//
//
//
//	Vertex v[] =
//	{
//		Vertex(0.0f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f),
//		Vertex(0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f),
//		Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f),
//	};
//
//	D3D11_BUFFER_DESC vertexBufferDesc;
//	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
//
//	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
//	vertexBufferDesc.ByteWidth = sizeof(Vertex) * 3;
//	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	vertexBufferDesc.CPUAccessFlags = 0;
//	vertexBufferDesc.MiscFlags = 0;
//
//	D3D11_SUBRESOURCE_DATA vertexBufferData;
//
//	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
//	vertexBufferData.pSysMem = v;
//	hr = d3d11Device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &triangleVertBuffer);
//
//
//
//	UINT stride = sizeof(Vertex);
//	UINT offset = 0;
//	d3d11DevCon->IASetVertexBuffers(0, 1, &triangleVertBuffer, &stride, &offset);
//
//
//
//	hr = d3d11Device->CreateInputLayout(layout, numElements, VS_Buffer->GetBufferPointer(),
//		VS_Buffer->GetBufferSize(), &vertLayout);
//
//
//	d3d11DevCon->IASetInputLayout(vertLayout);
//
//
//
//	d3d11DevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//
//
//
//	D3D11_VIEWPORT viewport;
//	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
//
//	viewport.TopLeftX = 0;
//	viewport.TopLeftY = 0;
//	viewport.Width = Width;
//	viewport.Height = Height;
//
//
//
//	d3d11DevCon->RSSetViewports(1, &viewport);
//
//	return true;
//}
//
//void UpdateScene()
//{
//
//}
//
//void DrawScene()
//{
//
//	//Clear our backbuffer to the updated color
//	const float bgColor[] = { 0.0f, 1.0f, 1.0f, 1.0f };
//	d3d11DevCon->ClearRenderTargetView(renderTargetView, bgColor);
//
//	d3d11DevCon->Draw(3, 0);//3 vertices with no offset.
//
//							//Present the backbuffer to the screen
//	SwapChain->Present(0, 0);
//}
//
//int messageloop()
//{
//
//	MSG msg; //make instance to MSG structure
//	ZeroMemory(&msg, sizeof(MSG)); //clears the struct and sets it to null
//
//	while (true) //while thre's a message...
//	{
//		BOOL PeekMessageL(
//			LPMSG lpMsg,
//			HWND hWnd,
//			UINT wMsgFilterMin,
//			UINT wMsgFilterMax,
//			UINT wRemoveMsg
//		);
//
//		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//		{
//
//			if (msg.message == WM_QUIT) //If the message was a quit message, we close our program.
//				break;
//
//			TranslateMessage(&msg);//If our message was a windows message, we translate, then dispatch.
//			DispatchMessage(&msg);
//		}
//		else //if there ws not a windows message, we run our game
//		{
//			//run game code here
//			UpdateScene();
//			DrawScene();
//		}
//	}
//	return msg.wParam;
//}
//
//LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	//check the message for events
//	switch (msg)
//	{
//	case WM_KEYDOWN:
//		if (wParam == VK_ESCAPE)
//		{
//			if (MessageBox(0, "Are you sure you want to exit?", "Really?", MB_YESNO | MB_ICONQUESTION) == IDYES)
//				DestroyWindow(hwnd);
//		}
//		return 0;
//
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		return 0;
//	}
//
//	/*This is the default windows procedure function. We call this at the end to take care of all the
//	messages we recieve but don't take care of ourselves.*/
//	return DefWindowProc(hwnd, msg, wParam, lParam);
//}
