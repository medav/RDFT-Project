#include <windows.h>
#include "Game.h"
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine, int nCmdShow) {
	// Register the window class.
	const char CLASS_NAME[] = "RDFT Systems, Inc.";

	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.

	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		"RDFT Engine Demo",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		
		CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
		);

	if (hwnd == NULL)
		return 0;

	ShowWindow(hwnd, nCmdShow);

	Engine()->SetHWND(hwnd);

	if (!Engine()->LoadDLLs())
	//	return 0;

	if (!Engine()->CreateDevices())
		return 0;

	ENTITY e(1, 1, 2, 2);

	// Run the message loop.

	MSG msg = {};
	bool done = false; 
	while (!done)
	{
		PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE);
		if (msg.message == WM_QUIT) //check for a quit message
		{
			done = true; //if found, quit app
		}
		else
		{
			/*	Translate and dispatch to event queue*/
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Engine()->GetGlDevice()->BeginScene();
		Engine()->GetGlDevice()->Render(&e);
		Engine()->GetGlDevice()->EndScene();
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(hwnd, &ps);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}