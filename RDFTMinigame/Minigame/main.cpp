#include <windows.h>
#include <iostream>
#include "Game.h"
#include "Console.h"
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine, int nCmdShow) {
	// Register the window class.
	const char CLASS_NAME[] = "RDFT Systems, Inc.";

	Con();

	std::cout << "*********************************************************\n";
	std::cout << "*             RDFT Minigame and Engine Demo             *\n";
	std::cout << "*          Copyright (c) 2014 RDFT Systems, Inc.        *\n";
	std::cout << "*     Michael Davies, Daniel Shauger, Matt Wilkinson    *\n";
	std::cout << "*********************************************************\n";
	std::cout << "Creating window...\n";

	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.

	HWND hwnd = CreateWindowEx(
		0, CLASS_NAME,
		"RDFT Engine Demo",
		WS_OVERLAPPEDWINDOW,
		20, 20, 1024, 768,
		NULL, NULL,
		hInstance,
		NULL);

	if (hwnd == NULL)
		return 0;

	ShowWindow(hwnd, nCmdShow);
	
	std::cout << "Initializing Engine...\n";
	Engine()->SetHWND(hwnd);

	std::cout << "Loading libraries...\n";
	if (!Engine()->LoadDLLs())
		return 0;

	std::cout << "Creating devices...\n";
	if (!Engine()->CreateDevices())
		return 0;

	std::cout << "Setting up devices...\n";
	Engine()->GetGlDevice()->SetWindowSize();

	// This will call the constructors for our singletons
	std::cout << "Creating game...\n";
	MG();

	std::cout << "Setup complete!\n";

	Con()->Start();


	// Run the message loop.

	MSG msg = {};
	bool done = false; 
	while (!done) {
		PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE);
		if (msg.message == WM_QUIT) {
			done = true;
		}
		else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		MG()->Think();
		MG()->Draw();
	}

	Con()->Stop();

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_SIZE:
		if (Engine()->GetGlDevice()) {
			Engine()->GetGlDevice()->SetWindowSize();
			MG()->Resize();
		}
		break;

	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(hwnd, &ps);
		break;
	
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}