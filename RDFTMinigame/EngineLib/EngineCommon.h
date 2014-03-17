#ifndef __ENGINECOMMON__
#define __ENGINECOMMON__
#include <Windows.h>

typedef struct {
	double r, b, g, a;
} GLCOLOR;

typedef struct {
	double x, y;
} GLVECTOR2, GLVERTEX2;


GLVECTOR2 VectorOf(float x, float y);

#endif