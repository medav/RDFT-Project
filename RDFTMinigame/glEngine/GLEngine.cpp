#include "GLEngine.h"

bool GLENGINE::CreateRenderDevice(HWND hwnd) {
	
	this->hwnd = hwnd;
	// Get the device context for our window
	hdc = GetDC(hwnd);

	PIXELFORMATDESCRIPTOR pfd;
	int format;

	// get the device context (DC)
	hdc = GetDC(hwnd);

	// set the pixel format for the DC
	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	format = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, format, &pfd);

	// create and enable the render context (RC)
	hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hrc);

	return true; // We have successfully created a context, return true
}