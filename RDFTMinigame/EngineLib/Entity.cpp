#include <iostream>
#include <math.h>
#include "PhysEngineDevice.h"
#include "EngineCommon.h"

#define PI 3.1415926

void Ball::Think() {
	if (Vel.x == 0 && Vel.y == 0)
		return;

	// Update Pos based on velocity Vel
	// Multiply by 100 because it would be
	// too slow otherwise
	double dT = ck.DeltaT() * 100;

	double velAngle = atan2(Vel.y, Vel.x);
	double frictionMag = mk * mass * 9.8;
	double frictionAccX = (cos(velAngle) * frictionMag) / mass;
	double frictionAccY = (sin(velAngle) * frictionMag) / mass;

	// If the computed friction component is greater than the current speed, don't do it
	if (abs(frictionAccX) <= abs(Vel.x)){
		Vel.x -= (frictionAccX * dT);
		}
	else{
		Vel.x = 0;
	}

	// Same as prev but for y
	if (abs(frictionAccY) <= abs(Vel.y)){
		Vel.y -= (frictionAccY * dT);
	}
	else{
		Vel.y = 0;
	}

	if ((Vel.x * Vel.x + Vel.y * Vel.y) < 0.001) {
		Vel.x = 0;
		Vel.y = 0;

		ck.Reset();
	}

	Pos.x += Vel.x * dT;
	Pos.y += Vel.y * dT;
	std::cout << "Pos: " << Pos.x << " , " << Pos.y << std::endl;
}

void Ball::ApplyVelocity(float x, float y){
	Vel.x = x;
	Vel.y = y;
	std::cout << Vel.x <<","<< Vel.y << std::endl;
}

bool Ball::isStopped() {
	if (Vel.x == 0 && Vel.y == 0)
		return true;

	return false;
}

// Returns true if GLVECTOR2 pt is inside BOUNDINGXBOX box, false otherwise
bool PointInBox(GLVECTOR2 pt, BOUNDINGBOX box) {
	if (pt.x <= box.x + box.w &&
		pt.x >= box.x &&
		pt.y <= box.y + box.h &&
		pt.y >= box.y)
		return true;

	return false;
}

/* Unused
bool HorizontalCollision(BOUNDINGBOX box1, BOUNDINGBOX box2) {
	// Top left corner of this box
	GLVECTOR2 TL1 = VectorOf(box1.x, box1.y + box1.h);
	// Top left corner of other box
	GLVECTOR2 TL2 = VectorOf(box2.x, box2.y + box2.h);
	// Bottom right corner of this box
	GLVECTOR2 BR1 = VectorOf(box1.x + box1.w, box1.y);
	// Bottom right corner of other box
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
*/

void Ball::Collide(ENTITY * other){
	BOUNDINGBOX box = BoundingBox();
	BOUNDINGBOX otherBox = other->BoundingBox();

	// Top left corner of this box
	GLVECTOR2 TL = VectorOf(box.x, box.y + box.h);
	// Top right corner of this box
	GLVECTOR2 TR = VectorOf(box.x + box.w, box.y);

	// Bottom left corner of this box
	GLVECTOR2 BL = VectorOf(box.x, box.y);
	// Bottom right corner of this box
	GLVECTOR2 BR = VectorOf(box.x + box.w, box.y);


	// double testAngle = atan2(Vel.y, Vel.x);
	/*
	if (HorizontalCollision(box, otherBox)) {
		Vel.y *= (-1.0 * cc);
	} 
	else {
		Vel.x *= (-1.0 * cc);
	}

	Think();
	*/


	if (PointInBox(TL, otherBox)){
		// Case 1
		if (PointInBox(TR, otherBox)){
			Vel.y *= -1;
			std::cout << ("Case 1") << std::endl;
		}
		// Case 3
		else if (PointInBox(BL, otherBox)){
			Vel.x *= -1;
			std::cout << ("Case 3 ") << std::endl;
		}
		// Case 2
		else{
			Vel.x *= -1;
			Vel.y *= -1;
			std::cout << ("Case 2") << std::endl;
		}
	}
	else if (PointInBox(TR, otherBox)){
		// Case 7
		if (PointInBox(BR, otherBox)){
			Vel.x *= -1;
			std::cout << ("Case 7") << std::endl;
		}
		// Case 8
		else{
			Vel.x *= -1;
			Vel.y *= -1;
			std::cout << ("Case 8") << std::endl;
		}
	}
	else if (PointInBox(BR, otherBox)){
		// Case 5
		if (PointInBox(BL, otherBox))
		{
			Vel.y *= -1;
			std::cout << ("Case 5") << std::endl;
		}
		// Case 6
		else{
			Vel.x *= -1;
			Vel.y *= -1;
			std::cout << ("Case 6") << std::endl;
		}
	}
	// Case 4
	else{
		Vel.x *= -1;
		Vel.y *= -1;
		std::cout << ("Case 4") << std::endl;
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
	box.x = Pos.x - radius / 2;
	box.y = Pos.y - radius / 2;
	box.w = radius;
	box.h = radius;

	return box;
}

// Draw methods
void Wall::Draw(PGLENGINE glEngine) {
	glEngine->DrawRect(this->Pos, VectorOf(this->Width, this->Height), ColorOf(0.95f, 0.95f, 0.95f));
	//glEngine->DrawTexturedRect(this->Pos, VectorOf(this->Width, this->Height), "wall");
}

void Ball::Draw(PGLENGINE glEngine) {
	GLVECTOR2 end;
	double mag = Magnitude(Vel);

	end.x = Pos.x + Vel.x * 2.0;
	end.y = Pos.y + Vel.y * 2.0;

	float r = (float)mag / 10;

	if (r > 1.0)
		r = 1.0;

	glEngine->DrawArrow(this->Pos, end, 4.0f, ColorOf(r, 1.0f - r, 0.0f));
	//glEngine->DrawCircle(this->Pos, VectorOf(this->radius, 0), ColorOf(0.95f, 0.95f, 0.95f));
	glEngine->DrawTexturedRect(this->Pos, VectorOf(this->radius, this->radius), "ball");
}