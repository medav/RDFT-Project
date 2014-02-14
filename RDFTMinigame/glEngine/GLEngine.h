#ifndef __GLENGINEDEVICE__
#define __GLENGINEDEVICE__
#include "..\EngineLib\GLEngineDevice.h"
#include <GL/glew.h>
#include <GL/wglew.h>

class GLENGINE : public GLENGINEDEVICE {
private:
	int windowWidth;
	int windowHeight;

	HGLRC hrc;
	HDC hdc;
	HWND hwnd;

public:
	GLENGINE();
	virtual bool CreateRenderDevice(HWND hwnd);

	~GLENGINE();
};

#endif