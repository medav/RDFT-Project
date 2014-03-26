#ifndef __LMENGINEDEVICE__
#define __LMENGINEDEVICE__
#include "..\EngineLib\EngineCommon.h"

class LMENGINEDEVICE {
public:
	LMENGINEDEVICE() {}

	// TODO: Interface functions declared here:
	// virtual (type) NAME(args) = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual bool LMRefresh() = 0;
	virtual GLVECTOR2 LMGetVector() = 0;
	virtual ~LMENGINEDEVICE() {}
};

typedef LMENGINEDEVICE* PLMENGINE;
typedef LMENGINEDEVICE** LPLMENGINE;
typedef bool(*CREATELMENGINEDEVICE)(LPLMENGINE engine, HWND hwnd);

#endif