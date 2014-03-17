#ifndef __PHYSENGINEDEVICE__
#define __PHYSENGINEDEVICE__
#include <Windows.h>
#include "EngineCommon.h"

class PHYSENGINEDEVICE {
public:
	PHYSENGINEDEVICE() {}

	virtual void init() = 0;

	virtual void Think() = 0;

	virtual void AddEntity(ENTITY * ent) = 0;

	virtual ~PHYSENGINEDEVICE() {}
};

class ENTITY {
public:
	enum TYPE { STATIC, MOVING };

protected:
	GLVECTOR2 pos;

public:

	ENTITY() {
		pos.x = 0;
		pos.y = 0;
	}

	ENTITY(GLVECTOR2 pos) {
		this->pos = pos;
	}

	virtual void SetX(int x) {
		this->pos.x = x;
	}

	virtual void SetY(int y) {
		this->pos.y = y;
	}

	virtual void Think();
	virtual void Collide(ENTITY * other);
	virtual TYPE Type() = 0;
};


class Wall : public ENTITY {

public:
	virtual void Think() {}


};

class Hole : public ENTITY {
public:
	//TODO
};

class Ball : public ENTITY {
private:
	// Kinetic friction coef.
	const double mk = 0.7;

	// Collision constant
	const double cc = 0.1;

	GLVECTOR2 V;
	GLVECTOR2 R;

public:
	Ball(GLVECTOR2 pos) : ENTITY(pos) {}

	virtual void Think();
	virtual void Collide(ENTITY * other);

	void ApplyVelocity(float x, float y);
};

typedef PHYSENGINEDEVICE* PPHYSENGINE;
typedef PHYSENGINEDEVICE** LPPHYSENGINE;

#endif