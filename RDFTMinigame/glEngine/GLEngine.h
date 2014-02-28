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

	GLCOLOR clearColor;

public:
	GLENGINE(HWND hwnd);
	bool CreateRenderDevice(HWND hwnd);
	void SetWindowSize(int width, int height);

	void SetClearColor(GLCOLOR bgcolor);

	bool BeginScene();
	void Render(ENTITY * ent);
	bool EndScene();

	bool ReleaseRenderDevice();
	~GLENGINE();
};

#endif