#ifndef __LMENGINE__
#define __LMENGINE__
#include <Windows.h>
#include <Leap.h>

#include "..\EngineLib\LMEngineDevice.h"
#include "..\EngineLib\EngineCommon.h"



class LMENGINE : public LMENGINEDEVICE {
private:
	HWND hwnd;
	Leap::Controller ctrl;
	bool init;
	GLVECTOR2 start;
	GLVECTOR2 last;

public:
	LMENGINE(HWND hwnd) : ctrl() {
		this->hwnd = hwnd;
	}
	virtual bool LMRefresh();
	virtual GLVECTOR2 LMGetVector(GLVECTOR2 vector);

	~LMENGINE();
};


#endif