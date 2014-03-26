#ifndef __RDFTENGINE__
#define __RDFTENGINE__
#include "GLEngineDevice.h"
#include "PhysEngineDevice.h"
#include "LMEngineDevice.h"

typedef bool(*CREATEGLENGINEDEVICE)(LPGLENGINE engine, HWND hwnd);
typedef bool (*CREATEPHYSENGINEDEVICE)(LPPHYSENGINE engine, HWND hwnd);
typedef bool(*CREATELMENGINEDEVICE)(LPLMENGINE engine, HWND hwnd);

class RDFTENGINE {
private:

	PGLENGINE glEngine;
	PPHYSENGINE physEngine;
	PLMENGINE lmEngine;

	HINSTANCE hInst;
	HWND hwnd;

	HMODULE hGlDLL;
	HMODULE hPhysDLL;
	HMODULE hLmDLL;

public:
	RDFTENGINE();

	void SetHWND(HWND hwnd) {
		this->hwnd = hwnd;
	}

	bool GetOK();
	bool LoadDLLs();
	bool CreateDevices();

	bool CreateGlDevice();
	bool CreatePhysDevice();
	bool CreateLmDevice();

	PGLENGINE GetGlDevice() {
		return glEngine; 
	}

	PPHYSENGINE GetPhysDevice() {
		return physEngine;
	}

	PLMENGINE GetLmDevice() {
		return lmEngine;
	}

	HINSTANCE GetGlModule() { 
		return hGlDLL; 
	}

	HINSTANCE GetPhysModule() {
		return hPhysDLL;
	}

	HINSTANCE GetLmModule() {
		return hLmDLL;
	}

	void ReleaseGl();
	void ReleasePhys();
	void ReleaseLm();

	~RDFTENGINE();
};

#endif