#include "PHYSEngine.h"

PHYSENGINE::PHYSENGINE(HWND hwnd) {
	this->hwnd = hwnd;
	ents = new std::vector<ENTITY *>();
}

void PHYSENGINE::Init() {

}

void PHYSENGINE::AddEntity(ENTITY * ent) {
	ents->push_back(ent);
}

void PHYSENGINE::Clear() {
	for (int i = ents->size() - 1; i >= 0; i--){
		delete (*ents)[i];
	}
	delete ents;
	ents = new std::vector<ENTITY *>();
}

bool Collide(BOUNDINGBOX b1, BOUNDINGBOX b2) {
	if (b1.x + b1.w < b2.x ||
		b2.x + b2.w < b1.x ||
		b1.y + b1.h < b2.y ||
		b2.y + b2.h < b1.y)
		return false;

	return true;
}

void PHYSENGINE::Think() {

	// Call Think() for all ENTITYs
	for (unsigned int i = 0; i < ents->size(); i++){
		(*ents)[i]->Think();

	}

	// Search for collisions
	for (unsigned int i = 0; i < ents->size(); i++){
		if ((*ents)[i]->Type() == ENTITY::MOVING){
			for (unsigned int j = 0; j < (*ents).size(); j++){
				if ((*ents)[i] != (*ents)[j]) {
					if (Collide((*ents)[i]->BoundingBox(), (*ents)[j]->BoundingBox()))
						(*ents)[i]->Collide((*ents)[j]);
				}
			}
		}
	}
}

void PHYSENGINE::Draw(PGLENGINE glEngine) {
	for (unsigned int i = 0; i < ents->size(); i++){
		(*ents)[i]->Draw(glEngine);
	}
}

PHYSENGINE::~PHYSENGINE() {

}

bool CreatePhysDevice(LPPHYSENGINE device, HWND hwnd) {
	*device = new PHYSENGINE(hwnd);

	return true;
}

bool ReleasePhysDevice(PHYSENGINEDEVICE * device) {
	if (!device)
		return true;

	PHYSENGINE * engine = (PHYSENGINE *)device;
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