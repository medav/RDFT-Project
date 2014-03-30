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
	bool init=false;
	GLVECTOR2 start;	
	GLVECTOR2 last;

public:
	LMENGINE(HWND hwnd) : ctrl() {
		this->hwnd = hwnd;

		last.x = 0;
		last.y = 0;
	}

	virtual bool LMRefresh();
	virtual GLVECTOR2 LMGetVector();
	virtual bool initLM();

	~LMENGINE();
};


#endif