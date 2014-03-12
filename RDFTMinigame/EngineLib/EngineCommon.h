#ifndef __ENGINECOMMON__
#define __ENGINECOMMON__
#include <Windows.h>

typedef struct {
	double r, b, g, a;
} GLCOLOR;

typedef struct {
	double x, y;
} GLVECTOR2, GLVERTEX2;

class ENTITY {
private:
	float x, y;

public:

	ENTITY() {
		x = 0;
		y = 0;
	}

	ENTITY(float x, float y) {
		SetX(x);
		SetY(y);
	}

	virtual void SetX(int x) {
		this->x = x;
	}

	virtual void SetY(int y) {
		this->y = y;
	}

	virtual void Think();
	virtual void Collide(ENTITY * other);

};

#endif