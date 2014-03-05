#ifndef __PHYSENGINE__
#define __PHYSENGINE__
#include <Windows.h>
#include "..\EngineLib\PhysEngineDevice.h"
#include "..\EngineLib\EngineCommon.h"

class PHYSENGINE : public PHYSENGINEDEVICE {
private:
	HWND hwnd;

public:
	PHYSENGINE(HWND hwnd);

	virtual void init();

	~PHYSENGINE();
};

#endif