#include "PhysEngineDevice.h"
#include <math.h>
#define PI 3.14159265358979323846

void Ball::Think() {
	// Update Pos based on velocity Vel
	SetX(Pos.x + (Vel.x * deltaT));
	SetY(Pos.y + (Vel.y * deltaT));

	// Reduce Vel according to mk
	Vel.x *= mk;
	Vel.y *= mk;
}

void Ball::ApplyVelocity(float x, float y){
	Vel.x = x;
	Vel.y = y;
}

void Ball::Collide(ENTITY * other){
	double angleBetween = atan2(Vel.y, Vel.x);
	double secondAngle = (2 * PI) - angleBetween;
	double vectorMagnitude = sqrt(((Vel.x * Vel.x) + (Vel.y * Vel.y)));

	Vel.y = (sin(secondAngle) * vectorMagnitude) * cc;
	Vel.x = (cos(secondAngle) * vectorMagnitude) * cc;
}