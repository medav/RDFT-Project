#include "GLEngine.h"
#include <math.h>
#include <fstream>
#include <iostream>

GLENGINE::GLENGINE(HWND hwnd) : textures() {
	this->CreateRenderDevice(hwnd);
	this->SetWindowSize();
	
	bgColor.r = 0.0f;
	bgColor.g = 0.0f;
	bgColor.b = 0.0f;
	bgColor.a = 0.0f;

	listbase = glGenLists(256);
	wglUseFontBitmaps(hdc, 0, 256, listbase);

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

// This was written by following a tutorial on the internet:
// http://www.cplusplus.com/articles/GwvU7k9E/
bool LoadBMP(const char* location, GLuint *texture) {
	std::cout << "Loading texture \"" << location << "\"\n";

	uint8_t* datBuff[2] = { nullptr, nullptr };
	uint8_t* temp = nullptr;
	uint8_t* pixels = nullptr;

	*texture = -1;

	BITMAPFILEHEADER* bmpHeader = nullptr;
	BITMAPINFOHEADER* bmpInfo = nullptr;

	// The file... We open it with it's constructor
	std::ifstream file(location, std::ios::binary);
	if (!file)
		return false;

	// Allocate byte memory that will hold the two headers
	datBuff[0] = new uint8_t[sizeof(BITMAPFILEHEADER)];
	datBuff[1] = new uint8_t[sizeof(BITMAPINFOHEADER)];

	file.read((char*)datBuff[0], sizeof(BITMAPFILEHEADER));
	file.read((char*)datBuff[1], sizeof(BITMAPINFOHEADER));

	// Construct the values from the buffers
	bmpHeader = (BITMAPFILEHEADER*)datBuff[0];
	bmpInfo = (BITMAPINFOHEADER*)datBuff[1];

	// Check if the file is an actual BMP file
	if (bmpHeader->bfType != 0x4D42)
		return false;

	// First allocate pixel memory
	temp = new uint8_t[bmpInfo->biSizeImage];

	// Go to where image data starts, then read in image data
	file.seekg(bmpHeader->bfOffBits);
	file.read((char*)temp, bmpInfo->biSizeImage);

	pixels = new uint8_t[bmpInfo->biSizeImage + bmpInfo->biSizeImage / 3];

	// We're almost done. We have our image loaded, however it's not in the right format.
	// .bmp files store image data in the BGR format, and we have to convert it to RGB.
	// Since we have the value in bytes, this shouldn't be to hard to accomplish
	unsigned long i;
	unsigned long j;

	for (i = 0, j = 0; i < bmpInfo->biSizeImage; i += 3, j+=4) {
		pixels[j] = temp[i + 2];
		pixels[j + 1] = temp[i + 1];
		pixels[j + 2] = temp[i];

		// Remove pink
		if (temp[i] > 220 && temp[i + 1] < 30 && temp[i + 2] > 220)
			pixels[j + 3] = 0x00;
		else
			pixels[j + 3] = 0xFF;
	}

	// Set width and height to the values loaded from the file
	GLuint w = bmpInfo->biWidth;
	GLuint h = bmpInfo->biHeight;

	/*******************GENERATING TEXTURES*******************/

	glGenTextures(1, texture);             // Generate a texture
	glBindTexture(GL_TEXTURE_2D, *texture);

	GLint mode = GL_RGBA;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, mode, w, h, 0, mode, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, NULL);

	// Delete the two buffers.
	delete[] datBuff[0];
	delete[] datBuff[1];
	delete[] temp;
	//delete[] pixels;
	file.close();

	return true; // Return success code 
}

bool GLENGINE::LoadTexture(const char * filename, const char * name) {
	GLuint texture = 0;
	
	if (!LoadBMP(filename, &texture))
		return false;

	std::string str(name);
	textures[str] = texture;

	return true;
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
	glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	glClear(GL_COLOR_BUFFER_BIT);

	return true;
}

void GLENGINE::DrawRect(GLVERTEX2 pos, GLVECTOR2 size, GLCOLORARGB color) {
	glBegin(GL_QUADS);

	glColor3f(color.r, color.g, color.b);

	glVertex2f((GLfloat)(pos.x - size.x / 2.0), (GLfloat)(pos.y - size.y / 2.0));
	glVertex2f((GLfloat)(pos.x + size.x / 2.0), (GLfloat)(pos.y - size.y / 2.0));
	glVertex2f((GLfloat)(pos.x + size.x / 2.0), (GLfloat)(pos.y + size.y / 2.0));
	glVertex2f((GLfloat)(pos.x - size.x / 2.0), (GLfloat)(pos.y + size.y / 2.0));
	
	glEnd();
}

void GLENGINE::DrawTexturedRect(GLVERTEX2 pos, GLVECTOR2 size, const char * textureName) {
	std::string str(textureName);
	GLuint texture = textures[textureName];

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);

	glColor3f(1.0f, 1.0f, 1.0f);

	glTexCoord2f(0.0, 0.0);
	glVertex2f((GLfloat)(pos.x - size.x / 2.0), (GLfloat)(pos.y - size.y / 2.0));

	glTexCoord2f(1.0, 0.0);
	glVertex2f((GLfloat)(pos.x + size.x / 2.0), (GLfloat)(pos.y - size.y / 2.0));

	glTexCoord2f(1.0, 1.0);
	glVertex2f((GLfloat)(pos.x + size.x / 2.0), (GLfloat)(pos.y + size.y / 2.0));

	glTexCoord2f(0.0, 1.0);
	glVertex2f((GLfloat)(pos.x - size.x / 2.0), (GLfloat)(pos.y + size.y / 2.0));

	glEnd();

	glBindTexture(GL_TEXTURE_2D, NULL);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void GLENGINE::DrawCircle(GLVERTEX2 pos, GLVECTOR2 size, GLCOLORARGB color) {
	float theta = 2.0f * 3.14159f / 300.0f;
	float c = cosf(theta);
	float s = sinf(theta);
	float t;

	float x = (float) sqrt(size.x * size.x + size.y + size.y);
	float y = 0;
	int i;

	glBegin(GL_TRIANGLE_FAN);

	glColor3f(color.r, color.g, color.b);
	glVertex2f((GLfloat)pos.x, (GLfloat)pos.y);


	for (i = 0; i < 302; i++) {
		glVertex2f((GLfloat)(x + pos.x), (GLfloat)(y + pos.y));

		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}
	glEnd();
}

void GLENGINE::DrawCircleHollow(GLVERTEX2 pos, GLVECTOR2 size, GLCOLORARGB color) {

}

void GLENGINE::SetClearColor(GLCOLORARGB bgcolor) {
	this->bgColor = bgcolor;
}

void GLENGINE::DrawArrow(GLVECTOR2 begin, GLVECTOR2 end, float weight, GLCOLORARGB color) {
	
	const double PI = 3.14159;
	double phi = atan2(end.y - begin.y, end.x - begin.x);
	double theta1 = phi - PI / 6.0;
	double theta2 = PI / 3.0 - phi;

	GLVECTOR2 line;
	line.x = end.x - begin.x;
	line.y = end.y - begin.y;

	double mag = sqrt(line.x * line.x + line.y * line.y);
	double L = mag / 4;

	GLVECTOR2 e1;
	e1.x = end.x - L * cos(theta1);
	e1.y = end.y - L * sin(theta1);

	GLVECTOR2 e2;
	e2.x = end.x - L * sin(theta2);
	e2.y = end.y - L * cos(theta2);

	glLineWidth(weight);
	glBegin(GL_LINES);
	glEnable(GL_LINE_SMOOTH);

	glColor3f(color.r, color.g, color.b);
	glVertex2f((GLfloat)begin.x, (GLfloat)begin.y);
	glVertex2f((GLfloat)end.x, (GLfloat)end.y);

	glEnd();

	glLineWidth(2.0f * weight / 3.0f);
	glBegin(GL_LINES);

	glColor3f(color.r, color.g, color.b);

	glVertex2f((GLfloat)e1.x, (GLfloat)e1.y);
	glVertex2f((GLfloat)end.x, (GLfloat)end.y);
	
	glVertex2f((GLfloat)e2.x, (GLfloat)e2.y);
	glVertex2f((GLfloat)end.x, (GLfloat)end.y);

	glDisable(GL_LINE_SMOOTH);
	glEnd();
}

bool GLENGINE::EndScene() {
	
	
	glRasterPos2f(0.0f, 0.0f);

	// Must save/restore the list base.
	glPushAttrib(GL_LIST_BIT);

	glListBase(listbase);
	glCallLists(4, GL_UNSIGNED_BYTE, (const GLvoid*) "test");

	glPopAttrib();

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