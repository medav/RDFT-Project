#ifndef __GLENGINEDEVICE__
#define __GLENGINEDEVICE__
#include <Windows.h>
#include "EngineCommon.h"

class GLENGINEDEVICE {
public:
	GLENGINEDEVICE() {}

	virtual void SetWindowSize() = 0;

	virtual void SetClearColor(GLCOLORARGB bgcolor) = 0;
	virtual bool LoadTexture(const char * filename, const char * name) = 0;
	virtual bool UnloadTexture(const char * name) = 0;
	virtual void PrintTextures() = 0;

	virtual void PrintError() = 0;

	virtual bool BeginScene() = 0;

	virtual void DrawRect(GLVERTEX2 pos, GLVECTOR2 size, GLCOLORARGB color) = 0;
	virtual void DrawTexturedRect(GLVERTEX2 pos, GLVECTOR2 size, const char * textureName) = 0;
	virtual void DrawCircle(GLVERTEX2 pos, GLVECTOR2 size, GLCOLORARGB color) = 0;
	virtual void DrawCircleHollow(GLVERTEX2 pos, GLVECTOR2 size, GLCOLORARGB color) = 0;
	virtual void DrawArrow(GLVECTOR2 begin, GLVECTOR2 end, float weight, GLCOLORARGB color) = 0;
	virtual void DrawTextGl(GLVECTOR2 pos, GLCOLORARGB color, const char * text) = 0;

	virtual bool EndScene() = 0;

	virtual ~GLENGINEDEVICE() {}
};

typedef GLENGINEDEVICE* PGLENGINE;
typedef GLENGINEDEVICE** LPGLENGINE;


#endif