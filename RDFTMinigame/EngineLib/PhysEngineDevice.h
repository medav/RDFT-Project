#ifndef __PHYSENGINE__
#define __PHYSENGINE__
#include <Windows.h>
#include "EngineCommon.h"

class PHYSENGINEDEVICE {
public:
	PHYSENGINEDEVICE();

	// TODO: Interface functions declared here:
	// Form: virtual (type) NAME(args) = 0;

	virtual ~PHYSENGINEDEVICE() = 0;
};


class Wall : public ENTITY {
public:
	// This is basically just for clarification's sake of having a name; walls are
	// identical to ENTITY for all intensive purposes
};

class AlmostCircle : public ENTITY{
public:
	//TODO
};

class Hole : public AlmostCircle {
public:
	//TODO
};

class Ball : public AlmostCircle {
public:
	// TODO: Finish me!
};

#endif