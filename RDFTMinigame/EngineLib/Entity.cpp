#include <iostream>
#include <math.h>
#include "PhysEngineDevice.h"
#include "RDFTEngine.h"
#include "EngineCommon.h"

void Ball::Think() {
	if (Vel.x == 0 && Vel.y == 0)
		return;

	// Update Pos based on velocity Vel
	// Multiply by 100 because it would be
	// too slow otherwise
	double dT = ck.DeltaT() * 100;

	double mk = Engine()->GetDouble("friction");

	double velAngle = atan2(Vel.y, Vel.x);
	double frictionMag = mk * 9.8;
	double frictionAccX = (cos(velAngle) * frictionMag);
	double frictionAccY = (sin(velAngle) * frictionMag);

	// If the computed friction component is greater than the current speed, don't do it
	if (abs(frictionAccX) <= abs(Vel.x))
		Vel.x -= (frictionAccX * dT);
	else
		Vel.x = 0;

	// Same as prev but for y
	if (abs(frictionAccY) <= abs(Vel.y))
		Vel.y -= (frictionAccY * dT);
	else
		Vel.y = 0;

	if ((Vel.x * Vel.x + Vel.y * Vel.y) < 0.001) {
		Vel.x = 0;
		Vel.y = 0;

		ck.Reset();
	}

	double scrX = Engine()->ScreenX();
	double scrY = Engine()->ScreenY();

	Pos.x += Vel.x * dT;
	if (Pos.x < 0)
		Pos.x += scrX;

	if (Pos.x > scrX)
		Pos.x -= scrX;

	Pos.y += Vel.y * dT;
	if (Pos.y < 0)
		Pos.y += scrY;

	if (Pos.y > scrY)
		Pos.y -= scrY;
}

void Ball::ApplyVelocity(float x, float y){
	Vel.x = x;
	Vel.y = y;
}

bool Ball::isStopped() {
	if (Vel.x == 0 && Vel.y == 0)
		return true;

	return false;
}


void Ball::Collide(ENTITY * other){
	GLVECTOR2 tVel = Engine()->GetPhysDevice()->DoCollision(this, other);

	Vel.x = tVel.x * Engine()->GetDouble("collision_constant");
	Vel.y = tVel.y * Engine()->GetDouble("collision_constant");
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
	box.x = Pos.x - radius / 3;
	box.y = Pos.y - radius / 3;
	box.w = 2 * radius / 3;
	box.h = 2 * radius / 3;

	return box;
}

void Hole::Draw(PGLENGINE glEngine){
	glEngine->DrawTexturedRect(this->Pos, VectorOf(100, 100), "hole");
}

// Draw methods
void Wall::Draw(PGLENGINE glEngine) {
	//glEngine->DrawRect(this->Pos, VectorOf(this->Width, this->Height), ColorOf(0.95f, 0.95f, 0.95f));
	glEngine->DrawTexturedRect(this->Pos, VectorOf(this->Width, this->Height), "wall");
}

void Ball::Draw(PGLENGINE glEngine) {
	GLVECTOR2 end;
	double mag = Magnitude(Vel);

	end.x = Pos.x + Vel.x * 6.0;
	end.y = Pos.y + Vel.y * 6.0;

	float r = (float)mag / 50;

	if (r > 1.0)
		r = 1.0;

	glEngine->DrawArrow(this->Pos, end, 4.0f, ColorOf(r, 1.0f - r, 0.0f));
	//glEngine->DrawCircle(this->Pos, VectorOf(this->radius, 0), ColorOf(0.95f, 0.95f, 0.95f));
	glEngine->DrawTexturedRect(this->Pos, VectorOf(this->radius, this->radius), "ball");
}