#include "RDFTEngine.h"

RDFTENGINE::RDFTENGINE() {
	glEngine = 0;

	hInst = 0;
	hwnd = 0;

	hGlDLL = 0;
	hPhysDLL = 0;
	hLmDLL = 0;
}

RDFTENGINE::~RDFTENGINE() {
	
}

bool RDFTENGINE::LoadDLLs() {
	bool result = true;

	hGlDLL = LoadLibrary("glEngine.dll");
	if (!hGlDLL) {
		MessageBox(NULL, "Could not load glEngine.dll", "Engine error", MB_ICONERROR | MB_OK);
		result = false;
	}

	hPhysDLL = LoadLibrary("physEngine.dll");
	if (!hPhysDLL) {
		MessageBox(NULL, "Could not load physEngine.dll", "Engine error", MB_ICONERROR | MB_OK);
		result = false;
	}

	hLmDLL = LoadLibrary("lmEngine.dll");
	if (!hLmDLL) {
		MessageBox(NULL, "Could not load lmEngine.dll", "Engine error", MB_ICONERROR | MB_OK);
		//result = false;
	}

	return result;
}

bool RDFTENGINE::CreateGlDevice() {
	if (!hGlDLL) {
		MessageBox(NULL, "glEngine.dll not loaded, could not create device", "Engine error", MB_ICONERROR | MB_OK);
		return false;
	}

	CREATEGLENGINEDEVICE _CreateGLEngineDevice = 0;
	_CreateGLEngineDevice = (CREATEGLENGINEDEVICE) GetProcAddress(hGlDLL, "CreateGlDevice");

	if (!_CreateGLEngineDevice) {
		MessageBox(NULL, "Could not call CreateGlDevice()", "Engine error", MB_ICONERROR | MB_OK);
		return false;
	}

	return _CreateGLEngineDevice(&this->glEngine, this->hwnd);
}

bool RDFTENGINE::CreatePhysDevice() {
	if (!hPhysDLL) {
		MessageBox(NULL, "physEngine.dll not loaded, could not create device", "Engine error", MB_ICONERROR | MB_OK);
		return false;
	}

	CREATEPHYSENGINEDEVICE _CreatePhysEngineDevice = 0;
	_CreatePhysEngineDevice = (CREATEPHYSENGINEDEVICE) GetProcAddress(hPhysDLL, "CreatePhysDevice");

	if (!_CreatePhysEngineDevice) {
		MessageBox(NULL, "Could not call CreatePhysDevice()", "Engine error", MB_ICONERROR | MB_OK);
		return false;
	}

	return _CreatePhysEngineDevice(&this->physEngine, this->hwnd);
}

bool RDFTENGINE::CreateLmDevice() {
	if (!hLmDLL) {
		MessageBox(NULL, "lmEngine.dll not loaded, could not create device", "Engine error", MB_ICONERROR | MB_OK);
		return false;
	}

	CREATELMENGINEDEVICE _CreateLmEngineDevice = 0;
	_CreateLmEngineDevice = (CREATELMENGINEDEVICE)GetProcAddress(hLmDLL, "CreateLmDevice");

	if (!_CreateLmEngineDevice) {
		MessageBox(NULL, "Could not call CreateLmDevice()", "Engine error", MB_ICONERROR | MB_OK);
		return false;
	}

	return _CreateLmEngineDevice(&this->lmEngine, this->hwnd);
}

bool RDFTENGINE::CreateDevices() {
	bool result = true;
	
	if (!CreateGlDevice())
		result = false;

	if (!CreatePhysDevice())
		result = false;

	//if (!CreateLmDevice())
	//	result = false;

	return result;
}