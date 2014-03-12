#ifndef __RDFTENGINE__
#define __RDFTENGINE__
#include "GLEngineDevice.h"
#include "PhysEngineDevice.h"

typedef bool(*CREATEGLENGINEDEVICE)(LPGLENGINE engine, HWND hwnd);
typedef bool (*CREATEPHYSENGINEDEVICE)(LPPHYSENGINE engine, HWND hwnd);

class RDFTENGINE {
private:
	PGLENGINE glEngine;

	HINSTANCE hInst;
	HWND hwnd;

	HMODULE hGlDLL;
	HMODULE hPhysDLL;
	HMODULE hLmDLL;

	

public:
	RDFTENGINE();
	~RDFTENGINE();

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

};

#endif