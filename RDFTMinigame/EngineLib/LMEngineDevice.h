#ifndef __LMENGINEDEVICE__
#define __LMENGINEDEVICE__
#include "..\EngineLib\EngineCommon.h"

class LMENGINEDEVICE {
public:
	LMENGINEDEVICE();

	// TODO: Interface functions declared here:
	// virtual (type) NAME(args) = 0;
	virtual bool LMInitiate() = 0;
	virtual bool LMRefresh() = 0;
	virtual GLVECTOR2 LMGetVector(GLVECTOR2 start, GLVECTOR2 end) = 0;
	virtual ~LMENGINEDEVICE() = 0;
};

#endif