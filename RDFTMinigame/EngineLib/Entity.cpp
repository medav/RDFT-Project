#include "PhysEngineDevice.h"

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
	Vel.x = -1 * (Vel.x * cc);
	Vel.y = -1 * (Vel.y * cc);
}