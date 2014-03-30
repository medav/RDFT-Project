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

	Engine()->SetHWND(hwnd);

	if (!Engine()->LoadDLLs())
		return 0;

	if (!Engine()->CreateDevices())
		return 0;

	Engine()->GetGlDevice()->SetWindowSize();

	// This will call the constructors for our singletons
	MG();
	MGM();
	MGG();

	// This is for testing - delay the game 
	int ct = 0;

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

		if (ct > 100)
			MG()->Think();

		MG()->Draw();
		ct++;
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_SIZE:
		if (Engine()->GetGlDevice())
			Engine()->GetGlDevice()->SetWindowSize();

		MG()->Resize();
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