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


public:
	LMENGINE(HWND hwnd) : ctrl() {
		this->hwnd = hwnd;
	}

	virtual bool LMInitiate();
	virtual bool LMRefresh();
	virtual GLVECTOR2 LMGetVector(GLVECTOR2 start, GLVECTOR2 end);

	~LMENGINE();
};


#endif