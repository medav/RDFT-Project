#include "LMEngine.h"

using namespace Leap;

bool LMENGINE::initLM() {
	return true;
}

unsigned char LMENGINE::LMRefresh() {
	if (ctrl.isConnected()) {
		const Frame frame = ctrl.frame();
		if (ctrl.frame(1).hands()[0].fingers()[0].tipPosition().z - ctrl.frame(0).hands()[0].fingers()[0].tipPosition().z > 7 && init==0 || init==1){
			if (!frame.hands().isEmpty()){
				init = 1;
				const Hand hand = frame.hands()[0];
				const FingerList fingers = hand.fingers();
				if (!fingers.isEmpty()){
					Vector avgPos;
					for (int i = 0; i < fingers.count(); ++i){
						avgPos += fingers[i].tipPosition();
					}
					avgPos /= (float)fingers.count();
					if (first){
						start.x = avgPos.x;
						start.y = avgPos.y;
						first = false;
					}
					last = { avgPos.x - start.x, avgPos.y - start.y };
					if (ctrl.frame(1).hands()[0].fingers()[0].tipPosition().z - ctrl.frame(0).hands()[0].fingers()[0].tipPosition().z < -4 && init == 1){
						init = 2;
						first = true;
					}
				}
			}
			else if (init == 1){
				init = 2;
				first = true;
			}
		}
	}

	return init;
}
void LMENGINE::Reset(){
	init = 0;
}
GLVECTOR2 LMENGINE::LMGetVector() {
	return last;
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