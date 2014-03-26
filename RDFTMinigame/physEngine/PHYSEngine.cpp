#include "PHYSEngine.h"

PHYSENGINE::PHYSENGINE(HWND hwnd) {
	this->hwnd = hwnd;

}

void PHYSENGINE::init() {

}
void PHYSENGINE::AddEntity(ENTITY * ent){
	ents.push_back(ent);
}
void PHYSENGINE::Clear(){
	for (unsigned int i = 0; i < ents.size(); i++){
		delete ents[i];
	}
}
void PHYSENGINE::Think() {
	ENTITY * temp;

	// Call Think() for all ENTITYs
	for (unsigned int i = 0; i < ents.size(); i++){
		ents[i]->Think();
		if (ents[i]->Type() == ENTITY::MOVING){
			temp = ents[i];
		}
	}

	// Search for collisions
	for (unsigned int i = 0; i < ents.size(); i++){

	}
}

PHYSENGINE::~PHYSENGINE() {

}
/*
bool CreatePhysDevice(LPLMENGINE device, HWND hwnd) {
	*device = new LMENGINE(hwnd);

	return true;
}

bool ReleasePhysDevice(LMENGINEDEVICE * device) {
	if (!device)
		return true;

	LMENGINE * engine = (LMENGINE *)device;
	delete engine;

	return true;
}*/

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