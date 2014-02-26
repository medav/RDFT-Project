#ifndef __GLENGINEDEVICE__
#define __GLENGINEDEVICE__
#include <Windows.h>

class GLENGINEDEVICE {
public:
	GLENGINEDEVICE();

	virtual bool CreateRenderDevice(HWND hwnd) = 0;
	virtual void SetWindowSize(int width, int height) = 0;

	virtual void SetClearColor(ARGBCOLOR bgcolor) = 0;

	virtual bool BeginScene() = 0;
	virtual void Render(ENTITY * ent) = 0;
	virtual bool EndScene() = 0;

	virtual bool ReleaseRenderDevice() = 0;

	virtual ~GLENGINEDEVICE() = 0;
};

#endif