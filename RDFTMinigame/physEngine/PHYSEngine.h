#ifndef __PHYSENGINE__
#define __PHYSENGINE__
#include <Windows.h>
#include <vector>
#include "..\EngineLib\PhysEngineDevice.h"
#include "..\EngineLib\EngineCommon.h"

class PHYSENGINE : public PHYSENGINEDEVICE {
private:
	HWND hwnd;
	std::vector<ENTITY *> ents;

public:
	PHYSENGINE(HWND hwnd);

	virtual void init();

	virtual void AddEntity(ENTITY * ent) = 0;
	virtual void Clear() = 0;

	virtual void Think();

	~PHYSENGINE();
};

#endif