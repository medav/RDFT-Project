#ifndef __PHYSENGINE__
#define __PHYSENGINE__
#include <Windows.h>

class PHYSENGINEDEVICE {

};

class PHYSENGINECONTEXT {

};

class ENTITY {
private:
	int PosX, PosY;

public:
	ENTITY() {
		PosX = 0;
		PosY = 0;
	}

	ENTITY(int x, int y) {
		PosX = x;
		PosY = y;
	}

	int getX() const {
		return PosX;
	}

	int getY() const {
		return PosY;
	}

	// TODO: Need a way to get vertex info to the GL Engine

	virtual void Collide(ENTITY * other) = 0;

	RECT getRect();
};

class Rectangle : public ENTITY {
public:
	// TODO: Finish me!

};

class Ball : public Rectangle {
public:
	// TODO: Finish me!
};

#endif