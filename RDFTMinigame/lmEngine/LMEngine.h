#ifndef __LMENGINE__
#define __LMENGINE__
#include <Windows.h>
#include "..\EngineLib\LMEngineDevice.h"
#include "Leap.h"
#include "LeapMath.h"

class LMENGINE : public LMENGINEDEVICE {
private:
	// Private variables go here

public:
	virtual bool LMInitiate();
	virtual bool LMRefresh();
	virtual GLVECTOR2 LMGetVector(GLVECTOR2 start, GLVECTOR2 end);
};

static Leap::Controller& getController()
{
	static Leap::Controller s_controller;
	return  s_controller;
}
#endif