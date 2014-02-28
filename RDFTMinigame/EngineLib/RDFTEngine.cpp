#include "RDFTEngine.h"


bool RDFTENGINE::LoadDLLs() {
	hGlDLL = LoadLibrary("glEngine.dll");
	if (!hGlDLL) {
		MessageBox(NULL, "Could not load glEngine.dll", "Engine error", MB_ICONERROR | MB_OK);
		//return false;
	}

	hPhysDLL = LoadLibrary("physEngine.dll");
	if (!hPhysDLL) {
		MessageBox(NULL, "Could not load physEngine.dll", "Engine error", MB_ICONERROR | MB_OK);
		return false;
	}

	hPhysDLL = LoadLibrary("lmEngine.dll");
	if (!hPhysDLL) {
		MessageBox(NULL, "Could not load physEngine.dll", "Engine error", MB_ICONERROR | MB_OK);
		return false;
	}

}

bool CreateDevices();