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

class ENTITY {
private:
	RECT rect;
	GLCOLOR colors[4];

public:
	enum VERTEX {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};

	ENTITY() {
		rect.left = 0;
		rect.right = 0;
		rect.top = 0;
		rect.bottom = 0;
	}

	ENTITY(int x, int y, int w, int h) {
		rect.left = x;
		rect.right = x + w;
		rect.top = y;
		rect.bottom = y + h;
	}

	virtual void Collide(ENTITY * other) = 0;

	GLCOLOR getColor(VERTEX v);

	// Required for rendering
	RECT getRect();
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