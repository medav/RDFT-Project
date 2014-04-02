#ifndef __RDFTENGINE__
#define __RDFTENGINE__
#include <map>
#include <string>
#include <math.h>
#include <mutex>
#include "GLEngineDevice.h"
#include "PhysEngineDevice.h"
#include "LMEngineDevice.h"

typedef bool(*CREATEGLENGINEDEVICE)(LPGLENGINE engine, HWND hwnd);
typedef bool (*CREATEPHYSENGINEDEVICE)(LPPHYSENGINE engine, HWND hwnd);
typedef bool(*CREATELMENGINEDEVICE)(LPLMENGINE engine, HWND hwnd);

typedef void(*RELEASEGLENGINEDEVICE)(GLENGINEDEVICE * device);
typedef void(*RELEASEPHYSENGINEDEVICE)(PHYSENGINEDEVICE * device);
typedef void(*RELEASELMENGINEDEVICE)(LMENGINEDEVICE * device);

struct ENVVAR {
	char value[128];
	double asDouble;
	bool asBool;

	bool boolset;
	bool numset;
};

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

	std::map<std::string, ENVVAR *> env;
	ENVVAR * GetEnv(const char * varname);

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

	std::mutex env_mutex;

	bool GetBool(const char * varname);
	double GetDouble(const char * varname);
	int GetInt(const char * varname);

	void SetEnv(const char * varname, ENVVAR * ev);

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