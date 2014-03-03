#ifndef __PHYSENGINE__
#define __PHYSENGINE__
#include <Windows.h>
#include "EngineCommon.h"

class PHYSENGINEDEVICE {
public:
	PHYSENGINEDEVICE();

	// TODO: Interface functions declared here:
	// virtual (type) NAME(args) = 0;

	virtual ~PHYSENGINEDEVICE() = 0;
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