#ifndef __RDFTENGINE__
#define __RDFTENGINE__
#include <math.h>
#include "GLEngineDevice.h"
#include "PhysEngineDevice.h"
#include "LMEngineDevice.h"

typedef bool(*CREATEGLENGINEDEVICE)(LPGLENGINE engine, HWND hwnd);
typedef bool (*CREATEPHYSENGINEDEVICE)(LPPHYSENGINE engine, HWND hwnd);
typedef bool(*CREATELMENGINEDEVICE)(LPLMENGINE engine, HWND hwnd);

typedef void(*RELEASEGLENGINEDEVICE)(GLENGINEDEVICE * device);
typedef void(*RELEASEPHYSENGINEDEVICE)(PHYSENGINEDEVICE * device);
typedef void(*RELEASELMENGINEDEVICE)(LMENGINEDEVICE * device);

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

	void ReleaseGlDevice();
	void ReleasePhysDevice();
	void ReleaseLmDevice();

public:
	RDFTENGINE();

	void SetHWND(HWND hwnd) {
		this->hwnd = hwnd;
	}

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

	~RDFTENGINE();
};

#endif