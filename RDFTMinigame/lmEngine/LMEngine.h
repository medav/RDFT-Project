#ifndef __LMENGINE__
#define __LMENGINE__
#include <Windows.h>
#include "..\EngineLib\LMEngineDevice.h"

class LMENGINE : public LMENGINEDEVICE {
private:
	// Private variables go here

public:
	virtual bool LMInitiate();
	virtual bool LMRefresh();
	virtual GLVECTOR2 LMGetVector(GLVECTOR2 start, GLVECTOR2 end);
};


#endif