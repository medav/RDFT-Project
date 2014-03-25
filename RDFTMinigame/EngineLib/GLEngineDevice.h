#ifndef __GLENGINEDEVICE__
#define __GLENGINEDEVICE__
#include <Windows.h>
#include "EngineCommon.h"

class GLENGINEDEVICE {
public:
	GLENGINEDEVICE() {}

	virtual void SetWindowSize() = 0;

	//virtual void SetClearColor(ARGBCOLOR bgcolor) = 0;

	virtual void DrawRect(GLVERTEX2 pos, GLVECTOR2 size, GLCOLOR color) = 0;
	virtual void DrawCircle(GLVERTEX2 pos, GLVECTOR2 size, GLCOLOR color) = 0;

	virtual bool BeginScene() = 0;
	virtual bool EndScene() = 0;

	virtual ~GLENGINEDEVICE() {}
};

typedef GLENGINEDEVICE* PGLENGINE;
typedef GLENGINEDEVICE** LPGLENGINE;


#endif