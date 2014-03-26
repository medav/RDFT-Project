#include <math.h>
#include "PhysEngineDevice.h"
#include <math.h>

#define PI 3.1415926

void Ball::Think() {
	// Update Pos based on velocity Vel
	double dT = ck.DeltaT();

	Pos.x += Vel.x * 0.5;
	Pos.y += Vel.y * 0.5;

	// Reduce Vel according to mk
	//Vel.x *= mk;
	//Vel.y *= mk;
}

void Ball::ApplyVelocity(float x, float y){
	Vel.x = x;
	Vel.y = y;
}

void Ball::Collide(ENTITY * other){
	//Vel.x = -1 * (Vel.x);
	//Vel.y = -1 * (Vel.y);

	/*
	double angleBetween = atan2(Vel.y, Vel.x);
	double secondAngle = -1 * angleBetween;
	double vectorMagnitude = sqrt(((Vel.x * Vel.x) + (Vel.y * Vel.y)));

	Vel.y = (sin(secondAngle) * vectorMagnitude) * cc;
	Vel.x = (cos(secondAngle) * vectorMagnitude) * cc;
	*/

	// If y's are intersecting
	if ((this->BoundingBox().y + this->BoundingBox().h == other->BoundingBox().h) || 
		(this->BoundingBox().y == other->BoundingBox().y + other->BoundingBox().h))
	{
		Vel.y = -1 * Vel.y;
	}
	else
	{
		Vel.x = -1 * Vel.x;
	}
}

// Bounding Box Methods
BOUNDINGBOX World::BoundingBox() {
	BOUNDINGBOX box;
	box.x = Pos.x - Width / 2;
	box.y = Pos.y - Height / 2;
	box.w = Width;
	box.h = Height;

	return box;
}

BOUNDINGBOX Ball::BoundingBox() {
	BOUNDINGBOX box;
	box.x = Pos.x - radius;
	box.y = Pos.y - radius;
	box.w = radius * 2;
	box.h = radius * 2;

	return box;
}

// Draw methods
void Wall::Draw(PGLENGINE glEngine) {
	glEngine->DrawRect(this->Pos, VectorOf(this->Width, this->Height), ColorOf(0.95f, 0.95f, 0.95f));
}

void Ball::Draw(PGLENGINE glEngine) {
	glEngine->DrawCircle(this->Pos, VectorOf(this->radius, 0), ColorOf(0.95f, 0.95f, 0.95f));
}