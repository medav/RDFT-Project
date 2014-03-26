#include <math.h>
#include "PhysEngineDevice.h"
#include <math.h>

#define PI 3.1415926

void Ball::Think() {
	if (Vel.x == 0 && Vel.y == 0)
		return;

	double frictionAcc = -1 * mk;
	// Update Pos based on velocity Vel
	double dT = ck.DeltaT();

	Pos.x += Vel.x * dT;
	Pos.y += Vel.y * dT;


	Vel.x += (frictionAcc * dT);
	Vel.y += (frictionAcc * dT);

	if ((Vel.x * Vel.x + Vel.y * Vel.y) < 0.0005) {
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

bool HorizontalCollision(BOUNDINGBOX box1, BOUNDINGBOX box2) {
	GLVECTOR2 TL1 = VectorOf(box1.x, box1.y + box1.h);
	GLVECTOR2 TL2 = VectorOf(box2.x, box2.y + box2.h);
	GLVECTOR2 BR1 = VectorOf(box1.x + box1.w, box1.y);
	GLVECTOR2 BR2 = VectorOf(box2.x + box2.w, box2.y);

	if (TL1.y >= BR2.y && BR1.y <= BR2.y &&
		( (TL1.x >= TL2.x && TL1.x <= BR2.x) || 
		  (BR1.x <= BR2.x && BR1.x >= TL2.x) ) )
		return true;

	if (BR1.y <= TL2.y && TL1.y >= TL2.y &&
		((TL1.x >= TL2.x && TL1.x <= BR2.x) ||
		(BR1.x <= BR2.x && BR1.x >= TL2.x)))
		return true;

	return false;
}

void Ball::Collide(ENTITY * other){
	BOUNDINGBOX box = BoundingBox();
	BOUNDINGBOX otherBox = other->BoundingBox();

	if (HorizontalCollision(box, otherBox)) {
		Vel.y *= (-1.0 * cc);
	} 
	else {
		Vel.x *= (-1.0 * cc);
	}

	Think();
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
	GLVECTOR2 end;
	double mag = sqrt(Vel.x * Vel.x + Vel.y * Vel.y);

	end.x = Pos.x + Vel.x * 10.0;
	end.y = Pos.y + Vel.y * 10.0;

	float r = (float)mag / 10;

	if (r > 1.0)
		r = 1.0;

	glEngine->DrawArrow(this->Pos, end, 4.0, ColorOf(r, 1.0 - r, 0.0f));

	glEngine->DrawCircle(this->Pos, VectorOf(this->radius, 0), ColorOf(0.95f, 0.95f, 0.95f));
}