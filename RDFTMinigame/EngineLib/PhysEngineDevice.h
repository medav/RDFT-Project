#ifndef __PHYSENGINEDEVICE__
#define __PHYSENGINEDEVICE__
#include <Windows.h>
#include "EngineCommon.h"

class PHYSENGINEDEVICE {
public:
	PHYSENGINEDEVICE() {}

	virtual void init() = 0;

	virtual ~PHYSENGINEDEVICE() {}
};


class Wall : public ENTITY {
public:
	// TODO: Finish me!

};

class AlmostCircle : public ENTITY{
public:
	//TODO
};

class Hole : public AlmostCircle {
public:
	//TODO
};

class Ball : public ENTITY {
public:
	// TODO: Finish me!
};

#endif