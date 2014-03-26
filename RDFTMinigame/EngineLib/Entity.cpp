#include <math.h>
#include "PhysEngineDevice.h"
#include <math.h>

#define PI 3.1415926

void Ball::Think() {
	if (Vel.x == 0 && Vel.y == 0)
		return;

	// Update Pos based on velocity Vel
	double dT = ck.DeltaT();

	Pos.x += Vel.x * 0.5;
	Pos.y += Vel.y * 0.5;

	// Reduce Vel according to mk
	Vel.x *= mk;
	Vel.y *= mk;

	if ((Vel.x * Vel.x + Vel.y * Vel.y) < 0.001) {
		Vel.x = 0;
		Vel.y = 0;
	}
}

void Ball::ApplyVelocity(float x, float y){
	Vel.x = x;
	Vel.y = y;
}

bool PointInBox(GLVECTOR2 pt, BOUNDINGBOX box) {
	if (pt.x <= box.x + box.w &&
		pt.x >= box.x &&
		pt.y <= box.y + box.h &&
		pt.y >= box.y)
		return true;

	return false;
}

void Ball::Collide(ENTITY * other){
	BOUNDINGBOX box = BoundingBox();

	GLVECTOR2 TL = VectorOf(box.x, box.y + box.h);
	GLVECTOR2 TR = VectorOf(box.x + box.w, box.y + box.h);
	GLVECTOR2 BL = VectorOf(box.x, box.y);
	GLVECTOR2 BR = VectorOf(box.x + box.w, box.y);

	BOUNDINGBOX otherBox = other->BoundingBox();

	if (PointInBox(TL, otherBox)) {
		if (TR.y >= otherBox.y && BL.y < otherBox.y)
			Vel.y *= (-1 * cc);
		else
			Vel.x *= (-1 * cc);
	} 
	else if (PointInBox(TR, otherBox)) {
		if (TL.y >= otherBox.y && BL.y < otherBox.y)
			Vel.y *= (-1 * cc);
		else
			Vel.x *= (-1 * cc);
	}
	else if (PointInBox(BR, otherBox)) {
		if (PointInBox(BL, otherBox))
			Vel.y *= (-1 * cc);
	}

	//Vel.y = (sin(secondAngle) * vectorMagnitude) * cc;
	//Vel.x = (cos(secondAngle) * vectorMagnitude) * cc;
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

	GLVECTOR2 end;
	end.x = Pos.x + Vel.x * 50;
	end.y = Pos.y + Vel.y * 50;

	glEngine->DrawArrow(this->Pos, end, 4.0, ColorOf(0.0f, 0.95f, 0.0f));
}