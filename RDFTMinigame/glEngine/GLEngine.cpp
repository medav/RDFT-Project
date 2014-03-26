#include "GLEngine.h"
#include <math.h>

GLENGINE::GLENGINE(HWND hwnd) {
	this->CreateRenderDevice(hwnd);
	this->SetWindowSize();
	r = 0;
}

void GLENGINE::SetWindowSize() {
	RECT r;

	GetWindowRect(hwnd, &r);
	int width = r.right - 1;
	int height = r.bottom - 1;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
}

bool GLENGINE::CreateRenderDevice(HWND hwnd) {
	this->hwnd = hwnd;
	this->hdc = GetDC(hwnd);

	
	PIXELFORMATDESCRIPTOR pfd;
	int format;

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

	return true;
}

bool GLENGINE::BeginScene() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	return true;
}

void GLENGINE::DrawRect(GLVERTEX2 pos, GLVECTOR2 size, GLCOLORARGB color) {
	glBegin(GL_QUADS);

	glColor3f(color.r, color.g, color.b);

	glVertex2f(pos.x - size.x / 2.0, pos.y - size.y / 2.0);
	glVertex2f(pos.x + size.x / 2.0, pos.y - size.y / 2.0);
	glVertex2f(pos.x + size.x / 2.0, pos.y + size.y / 2.0);
	glVertex2f(pos.x - size.x / 2.0, pos.y + size.y / 2.0);
	
	glEnd();
}

void GLENGINE::DrawCircle(GLVERTEX2 pos, GLVECTOR2 size, GLCOLORARGB color) {
	float theta = 2 * 3.1416 / 300.0;
	float c = cosf(theta);
	float s = sinf(theta);
	float t;

	float x = sqrt(size.x * size.x + size.y + size.y);
	float y = 0;
	int i;

	glBegin(GL_TRIANGLE_FAN);

	glColor3f(color.r, color.g, color.b);
	glVertex2f(pos.x, pos.y);


	for (int i = 0; i < 302; i++) {
		glVertex2f(x + pos.x, y + pos.y);

		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}
	glEnd();
}

void GLENGINE::DrawArrow(GLVECTOR2 begin, GLVECTOR2 end, float weight, GLCOLORARGB color) {
	glLineWidth(weight);
	glBegin(GL_LINES);

	glColor3f(color.r, color.g, color.b);
	glVertex2f(begin.x, begin.y);
	glVertex2f(end.x, end.y);

	glEnd();
}

bool GLENGINE::EndScene() {
	SwapBuffers(hdc);
	return true;
}

bool GLENGINE::ReleaseRenderDevice() {
	bool result = true;

	if (!wglMakeCurrent(NULL, NULL))
		result = false;

	if (!wglDeleteContext(hrc))
		result = false;

	ReleaseDC(hwnd, hdc);

	return result;
}

GLENGINE::~GLENGINE() {
	this->ReleaseRenderDevice();
}

bool CreateGlDevice(LPGLENGINE device, HWND hwnd) {
	*device = new GLENGINE(hwnd);
	
	return true;
}

bool ReleaseGlDevice(GLENGINEDEVICE * device) {
	if (!device)
		return true;

	GLENGINE * engine = (GLENGINE *) device;
	delete engine;

	return true;
}

bool APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call,	LPVOID lpReserved) {
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// A process is loading the DLL.
		break;
	case DLL_THREAD_ATTACH:
		// A process is creating a new thread.
		break;
	case DLL_THREAD_DETACH:
		// A thread exits normally.
		break;
	case DLL_PROCESS_DETACH:
		// A process unloads the DLL.
		break;
	}
	return true;
}