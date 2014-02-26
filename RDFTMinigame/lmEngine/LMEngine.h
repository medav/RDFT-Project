#ifndef __LMENGINE__
#define __LMENGINE__

#include "..\EngineLib\LMEngineDevice.h"

class LMENGINE : public LMENGINEDEVICE {
private:
	// Private variables go here

public:
	// Declaration of interface implementation methods go here

};

LMENGINEDEVICE * __declspec(dllexport) CreateLmDevice();

#endif