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
	float r;

	HGLRC hrc;
	HDC hdc;
	HWND hwnd;

	GLCOLORARGB clearColor;

public:
	GLENGINE(HWND hwnd);
	bool CreateRenderDevice(HWND hwnd);
	void SetWindowSize();

	void SetClearColor(GLCOLORARGB bgcolor);

	bool BeginScene();

	virtual void DrawRect(GLVERTEX2 pos, GLVECTOR2 size, GLCOLORARGB color);
	virtual void DrawCircle(GLVERTEX2 pos, GLVECTOR2 size, GLCOLORARGB color);
	virtual void DrawArrow(GLVECTOR2 begin, GLVECTOR2 end, float weight, GLCOLORARGB color);

	bool EndScene();

	bool ReleaseRenderDevice();
	~GLENGINE();
};

#endif