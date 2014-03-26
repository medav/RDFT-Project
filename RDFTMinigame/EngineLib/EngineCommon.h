#ifndef __ENGINECOMMON__
#define __ENGINECOMMON__
#include <Windows.h>

typedef struct {
	float r, b, g, a;
} GLCOLORARGB;

typedef struct {
	double x, y;
} GLVECTOR2, GLVERTEX2;

typedef struct {
	double x, y, w, h;
} BOUNDINGBOX;

class ClockKeeper {
private:
	time_t prev;

public:
	ClockKeeper();

	double DeltaT();
};

GLVECTOR2 VectorOf(double x, double y);
GLCOLORARGB AColorOf(float a, float r, float g, float b);
GLCOLORARGB ColorOf(float r, float g, float b);

double Magnitude(GLVECTOR2 vec);

#endif