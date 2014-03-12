#ifndef __PHYSENGINEDEVICE__
#define __PHYSENGINEDEVICE__
#include <Windows.h>
#include "EngineCommon.h"

class PHYSENGINEDEVICE {
public:
	PHYSENGINEDEVICE() {}

	virtual void init() = 0;

	virtual void Think() = 0;

	virtual ~PHYSENGINEDEVICE() {}
};


class Wall : public ENTITY {
public:
	virtual void Think() {}


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
private:
	// Kinetic friction coef.
	const double mk = .7;

	// Collision constant
	const double cc = .1;

	GLVECTOR2 V;
	GLVECTOR2 R;

public:
	virtual void Think();

	void ApplyVelocity(float x, float y);
};

#endif