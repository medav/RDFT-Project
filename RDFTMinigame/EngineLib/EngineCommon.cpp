#include <time.h>
#include "EngineCommon.h"
#include "RDFTEngine.h"


GLVECTOR2 VectorOf(double x, double y) {
	return Engine()->GetPhysDevice()->VectorOf(x, y);
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
	run = false;
}

double ClockKeeper::DeltaT() {
	using namespace std::chrono;

	high_resolution_clock::time_point temp;
	temp = high_resolution_clock::now();

	if (!run) {
		run = true;
		prev = temp;
		return 0.00;
	}

	duration<long double> time_span = duration_cast<duration<double>>(temp - prev);
	prev = temp;
	
	return time_span.count() / 4;
}

void ClockKeeper::Reset() {
	run = false;
}


double Magnitude(GLVECTOR2 vec) {
	return Engine()->GetPhysDevice()->Magnitude(vec);
}

RDFTENGINE * Engine() {
	static RDFTENGINE * rdft = new RDFTENGINE();
	return rdft;
}