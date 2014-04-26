#include "GLEngine.h"
#include <math.h>
#include <fstream>
#include <iostream>

GLuint GLENGINE::PrintErrorLine(int line) {
	
	GLuint err = glGetError();
	if (err)
		std::cout << "GlEngine.cpp : " << line << " OpenGL error code : " << err << std::endl;

	return err;
}

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

bmp_t GLENGINE::LoadBMP(const char * filename) {
	bmp_t bmp;

	bmp.bmpHeader = 0;
	bmp.bmpInfo = 0;
	bmp.datBuff[0] = 0;
	bmp.datBuff[1] = 0;
	bmp.pixels = 0;

	std::ifstream file(filename, std::ios::binary);

	if (!file)
		return bmp;

	bmp.datBuff[0] = new uint8_t[sizeof(BITMAPFILEHEADER)];
	bmp.datBuff[1] = new uint8_t[sizeof(BITMAPINFOHEADER)];

	file.read((char*)bmp.datBuff[0], sizeof(BITMAPFILEHEADER));
	file.read((char*)bmp.datBuff[1], sizeof(BITMAPINFOHEADER));

	bmp.bmpHeader = (BITMAPFILEHEADER*)bmp.datBuff[0];
	bmp.bmpInfo = (BITMAPINFOHEADER*)bmp.datBuff[1];

	bmp.pixels = new uint8_t[bmp.bmpInfo->biSizeImage];

	// Go to where image data starts, then read in image data
	file.seekg(bmp.bmpHeader->bfOffBits);
	file.read((char*)bmp.pixels, bmp.bmpInfo->biSizeImage);
	file.close();

	return bmp;
}


// This was written by following a tutorial on the internet:
// http://www.cplusplus.com/articles/GwvU7k9E/
bool GLENGINE::CreateTex(const char* location, GLuint *texture, uint8_t ** pixels, const char * mask) {
	bmp_t bmpfile = LoadBMP(location);
	bmp_t maskfile;

	*pixels = new uint8_t[bmpfile.bmpInfo->biSizeImage + bmpfile.bmpInfo->biSizeImage / 3];

	if (mask) {
		maskfile = LoadBMP(mask);
		if (!maskfile.bmpHeader) {
			mask = 0;
		}
		else {
			if (maskfile.bmpInfo->biSizeImage != bmpfile.bmpInfo->biSizeImage) {
				delete[] maskfile.datBuff[0];
				delete[] maskfile.datBuff[1];
				delete[] maskfile.pixels;

				mask = 0;
			}
		}
	}


	// We're almost done. We have our image loaded, however it's not in the right format.
	// .bmp files store image data in the BGR format, and we have to convert it to RGB.
	// Since we have the value in bytes, this shouldn't be to hard to accomplish
	unsigned long i;
	unsigned long j;

	for (i = 0, j = 0; i < bmpfile.bmpInfo->biSizeImage; i += 3, j += 4) {
		(*pixels)[j] = bmpfile.pixels[i + 2];
		(*pixels)[j + 1] = bmpfile.pixels[i + 1];
		(*pixels)[j + 2] = bmpfile.pixels[i];

		// Remove mask or pink

		if (mask) {
			if (maskfile.pixels[i] == 0x00 && maskfile.pixels[i + 1] == 0x00 && maskfile.pixels[i + 2] == 0x00)
				(*pixels)[j + 3] = 0x00;
			else
				(*pixels)[j + 3] = 0xFF;
		}
		else {
			if (bmpfile.pixels[i] > 215 && bmpfile.pixels[i + 1] < 35 && bmpfile.pixels[i + 2] > 215)
				(*pixels)[j + 3] = 0x00;
			else
				(*pixels)[j + 3] = 0xFF;
		}
	}

	// Set width and height to the values loaded from the file
	GLuint w = bmpfile.bmpInfo->biWidth;
	GLuint h = bmpfile.bmpInfo->biHeight;

	/*******************GENERATING TEXTURES*******************/

	glGenTextures(1, texture);

	if (*texture == -1) {
		std::cout << "\nglGenTextures() failed: " << glGetError() << std::endl;
		delete[] bmpfile.datBuff[0];
		delete[] bmpfile.datBuff[1];
		delete[] bmpfile.pixels;
		delete[] *pixels;

		if (mask) {
			delete[] maskfile.datBuff[0];
			delete[] maskfile.datBuff[1];
			delete[] maskfile.pixels;
		}

		return false;
	}
	PrintErrorLine(__LINE__);
	
	glBindTexture(GL_TEXTURE_2D, *texture);
	PrintErrorLine(__LINE__);

	GLint mode = GL_RGBA;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	PrintErrorLine(__LINE__);

	glTexImage2D(GL_TEXTURE_2D, 0, mode, w, h, 0, mode, GL_UNSIGNED_BYTE, *pixels);
	PrintErrorLine(__LINE__);

	glBindTexture(GL_TEXTURE_2D, NULL);
	PrintErrorLine(__LINE__);

	// Delete the two buffers.
	delete[] bmpfile.datBuff[0];
	delete[] bmpfile.datBuff[1];
	delete[] bmpfile.pixels;

	if (mask) {
		delete[] maskfile.datBuff[0];
		delete[] maskfile.datBuff[1];
		delete[] maskfile.pixels;
	}

	return true; // Return success code 
}

void GLENGINE::PrintError() {
	if (!PrintErrorLine(__LINE__))
		std::cout << "No errors\n";
}

bool GLENGINE::LoadTexture(const char * filename, const char * name, bool mask) {
	GLuint texture = 0;
	uint8_t * pixels;

	std::string str(name);
	TEXTURE * tex;

	tex = textures[str];
	if (tex) {
		if (tex->pixels)
			UnloadTexture(name);	
	}

	std::cout << "Loading texture \"" << filename << "\"...";

	bool result = false;

	if (mask)
		result = CreateTex(filename, &texture, &pixels, "mask.bmp");
	else
		result = CreateTex(filename, &texture, &pixels, 0);

	if (!result) {
		std::cout << "Failed\n";
		return false;
	}
	PrintErrorLine(__LINE__);

	tex = new TEXTURE;
	tex->pixels = pixels;
	tex->texID = texture;
	textures[str] = tex;

	std::cout << "OK\n";
	return true;
}

bool GLENGINE::UnloadTexture(const char * name) {
	std::string str(name);
	std::cout << "Unloading texture \"" << name << "\"...";

	TEXTURE * tex = textures[str];

	glDeleteTextures(1, &tex->texID);
	PrintErrorLine(__LINE__);

	textures.erase(str);
	delete tex;

	std::cout << "OK\n";
	return true;
}

void GLENGINE::PrintTextures() {
	std::cout << "Currently loaded textures:\n";

	std::map<std::string, TEXTURE *>::iterator it = textures.begin();
	while (it != textures.end()) {
		if (it->second->pixels)
			std::cout << "Texture \"" << it->first.c_str() << "\"\n";
		it++;
	}
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
	PrintErrorLine(__LINE__);

	return true;
}

bool GLENGINE::BeginScene() {
	glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	PrintErrorLine(__LINE__);

	glClear(GL_COLOR_BUFFER_BIT);
	PrintErrorLine(__LINE__);

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

	if (textures.count(str) == 0 || !textures[textureName]) {
		GLCOLORARGB color;
		color.a = 1.0;
		color.r = 1.0;
		color.g = 1.0;
		color.b = 1.0;

		DrawRect(pos, size, color);
		return;
	}

	GLuint texture = textures[textureName]->texID;

	glEnable(GL_TEXTURE_2D);
	PrintErrorLine(__LINE__);

	glBindTexture(GL_TEXTURE_2D, texture);
	PrintErrorLine(__LINE__);

	glEnable(GL_BLEND);
	PrintErrorLine(__LINE__);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	PrintErrorLine(__LINE__);
	
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
	PrintErrorLine(__LINE__);
	

	glBindTexture(GL_TEXTURE_2D, NULL);
	PrintErrorLine(__LINE__);
	
	glDisable(GL_TEXTURE_2D);
	PrintErrorLine(__LINE__);

	glDisable(GL_BLEND);
	PrintErrorLine(__LINE__);
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
	PrintErrorLine(__LINE__);
	
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
	PrintErrorLine(__LINE__);

	glEnable(GL_LINE_SMOOTH);
	PrintErrorLine(__LINE__);

	glBegin(GL_LINES);
	

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

	
	glEnd();
	PrintErrorLine(__LINE__);

	glDisable(GL_LINE_SMOOTH);
	PrintErrorLine(__LINE__);
	
}

void GLENGINE::DrawTextGl(GLVECTOR2 pos, GLCOLORARGB color, const char * text) {
	glColor3f(color.r, color.g, color.b);
	PrintErrorLine(__LINE__);

	glRasterPos2f(pos.x, pos.y);
	PrintErrorLine(__LINE__);
	
	// Must save/restore the list base.
	glPushAttrib(GL_LIST_BIT);
	PrintErrorLine(__LINE__);

	glListBase(listbase);
	PrintErrorLine(__LINE__);

	glCallLists(strlen(text), GL_UNSIGNED_BYTE, (const GLvoid*) text);
	PrintErrorLine(__LINE__);

	glPopAttrib();
	PrintErrorLine(__LINE__);
}

bool GLENGINE::EndScene() {
	SwapBuffers(hdc);

	PrintErrorLine(__LINE__);
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