#ifndef __RDFTENGINE__
#define __RDFTENGINE__
#include "GLEngineDevice.h"
#include "PhysEngineDevice.h"

typedef GLENGINEDEVICE* GLENGINE;

class RDFTENGINE {
private:
	GLENGINE Device;
	HINSTANCE hInst;
	HMODULE hDLL;

public:
	RDFTENGINE(HINSTANCE hInst);
	~RDFTENGINE(void);

	HRESULT CreateDevice(const char *chAPI);

	GLENGINE GetDevice(void) { 
		return Device; 
	}

	HINSTANCE GetModule(void) { 
		return hDLL; 
	}

	void Release(void);

};

#endif