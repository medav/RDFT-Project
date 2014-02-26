#ifndef __RDFTENGINE__
#define __RDFTENGINE__
#include "GLEngineDevice.h"
#include "PhysEngineDevice.h"

typedef GLENGINEDEVICE* GLENGINE;

class RDFTENGINE {
private:
	GLENGINE glDevice;
	HINSTANCE hInst;
	HMODULE hGlDLL;
	HMODULE hPhysDLL;
	HMODULE hLmDLL;

public:
	RDFTENGINE(HINSTANCE hInst);
	~RDFTENGINE(void);

	HRESULT CreateGlDevice();
	HRESULT CreatePhysDevice();
	HRESULT CreateLmDevice();

	GLENGINE GetGlDevice(void) { 
		return glDevice; 
	}

	HINSTANCE GetGlModule(void) { 
		return hGlDLL; 
	}

	HINSTANCE GetPhysModule(void) {
		return hPhysDLL;
	}

	HINSTANCE GetLmModule(void) {
		return hLmDLL;
	}

	void ReleaseGl(void);
	void ReleasePhys(void);
	void ReleaseLm(void);

};

#endif