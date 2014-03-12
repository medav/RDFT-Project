#ifndef __GLENGINEDEVICE__
#define __GLENGINEDEVICE__
#include <Windows.h>
#include "EngineCommon.h"

class GLENGINEDEVICE {
public:
	GLENGINEDEVICE() {}

	virtual void SetWindowSize() = 0;

	//virtual void SetClearColor(ARGBCOLOR bgcolor) = 0;

	virtual bool BeginScene() = 0;
	virtual void Render(ENTITY * ent) = 0;
	virtual bool EndScene() = 0;

	virtual ~GLENGINEDEVICE() {}
};

typedef GLENGINEDEVICE* PGLENGINE;
typedef GLENGINEDEVICE** LPGLENGINE;


#endif