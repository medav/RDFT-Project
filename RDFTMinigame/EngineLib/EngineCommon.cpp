#include <time.h>
#include "EngineCommon.h"

GLVECTOR2 VectorOf(double x, double y) {
	GLVECTOR2 pos;
	pos.x = x;
	pos.y = y;

	return pos;
}

GLCOLORARGB AColorOf(float a, float r, float g, float b) {
	GLCOLORARGB color;
	color.a = a;
	color.r = r;
	color.g = g;
	color.b = b;

	return color;
}
GLCOLORARGB ColorOf(float r, float g, float b) {
	return AColorOf(1.0, r, g, b);
}


ClockKeeper::ClockKeeper() {
	time(&prev);
}

double ClockKeeper::DeltaT() {
	time_t temp;
	time(&temp);

	double dT = difftime(temp, prev);
	prev = temp;

	return dT;
}

