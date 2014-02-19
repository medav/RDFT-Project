#ifndef __GLENGINEDEVICE__
#define __GLENGINEDEVICE__
#include "..\EngineLib\GLEngineDevice.h"
#include <gl\GL.h>
#include <gl\GLU.h>

class GLENGINE : public GLENGINEDEVICE {
private:
	int windowWidth;
	int windowHeight;

	HGLRC hrc;
	HDC hdc;
	HWND hwnd;

	ARGBCOLOR clearColor;

public:
	GLENGINE();
	virtual bool CreateRenderDevice(HWND hwnd);
	virtual void SetWindowSize(int width, int height);

	virtual void SetClearColor(ARGBCOLOR bgcolor);

	virtual bool BeginScene();
	virtual void Render(ENTITY * ent);
	virtual bool EndScene();

	virtual bool ReleaseRenderDevice();
	~GLENGINE();
};

#endif