#include "LMEngine.h"

LMENGINE::LMENGINE(HWND hwnd) {
	this->hwnd = hwnd;
	this->LMInitiate();
}

bool LMENGINE::LMInitiate() {
	// TODO: Finish me!
	return true;
}

bool LMENGINE::LMRefresh() {
	// TODO: Finish me!
	return true;
}

GLVECTOR2 LMENGINE::LMGetVector(GLVECTOR2 start, GLVECTOR2 end) {
	// TODO: Finish me!
	GLVECTOR2 result;
	result.x = 0;
	result.y = 0;
	return result;
}


LMENGINE::~LMENGINE() {
	// TODO: Add to this as necessary
}

bool CreateLmDevice(LPLMENGINE device, HWND hwnd) {
	*device = new LMENGINE(hwnd);

	return true;
}

bool ReleaseLmDevice(LMENGINEDEVICE * device) {
	if (!device)
		return true;

	LMENGINE * engine = (LMENGINE *)device;
	delete engine;

	return true;
}

bool APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// A process is loading the DLL.
		break;
	case DLL_THREAD_ATTACH:
		// A process is creating a new thread.
		break;
	case DLL_THREAD_DETACH:
		// A thread exits normally.
		break;
	case DLL_PROCESS_DETACH:
		// A process unloads the DLL.
		break;
	}
	return true;
}