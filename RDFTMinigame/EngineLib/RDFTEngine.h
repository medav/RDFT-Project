#ifndef __RDFTENGINE__
#define __RDFTENGINE__
#include <math.h>
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

	bool CreateGlDevice();
	bool CreatePhysDevice();
	bool CreateLmDevice();

public:
	RDFTENGINE();

	void SetHWND(HWND hwnd) {
		this->hwnd = hwnd;
	}

	bool GetOK();
	bool LoadDLLs();
	bool CreateDevices();

	

	PGLENGINE GetGlDevice() {
		return glEngine; 
	}

	PPHYSENGINE GetPhysDevice() {
		return physEngine;
	}

	PLMENGINE GetLmDevice() {
		return lmEngine;
	}

	double ScreenX() {
		RECT r;
		GetClientRect(hwnd, &r);
		return fabs((double)r.right - (double)r.left);
	}

	double ScreenY() {
		RECT r;
		GetClientRect(hwnd, &r);
		return fabs((double)r.bottom - (double)r.top);
	}

	void ReleaseGl();
	void ReleasePhys();
	void ReleaseLm();

	~RDFTENGINE();
};

#endif