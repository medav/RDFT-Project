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
	RECT rect;
	int w, h;
	GLCOLOR colors[4];

public:
	enum VERTEX { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT };

	ENTITY() {
		rect.left = 0;
		rect.right = 0;
		rect.top = 0;
		rect.bottom = 0;
	}

	ENTITY(int x, int y, int w, int h) {
		SetX(x);
		SetY(y);
		SetW(w);
		SetH(h);
	}

	void SetX(int x) {
		rect.left = x;
	}

	void SetY(int y) {
		rect.top = y;
	}

	void SetW(int w) {
		this->w = w;
	}

	void SetH(int h) {
		this->h = h;
	}
	//virtual void Think();
	//virtual void Collide(ENTITY * other);

	//GLCOLOR getColor(VERTEX v);

	// Required for rendering
	const RECT& getRect() {
		rect.right = rect.left + w;
		rect.bottom = rect.top + h;

		return rect;
	}
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