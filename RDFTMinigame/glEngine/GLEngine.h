#ifndef __GLENGINE__
#define __GLENGINE__
#include "..\EngineLib\GLEngineDevice.h"
#include "..\EngineLib\PhysEngineDevice.h"
#include "..\EngineLib\EngineCommon.h"
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

GLENGINEDEVICE * __declspec(dllexport) CreateGlDevice();

#endif