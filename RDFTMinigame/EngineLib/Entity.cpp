#include <iostream>
#include <math.h>
#include "PhysEngineDevice.h"
#include "RDFTEngine.h"
#include "EngineCommon.h"

#define PI 3.1415926
enum velDir{ RIGHT, RIGHTUP, UP, LEFTUP, LEFT, LEFTDOWN, DOWN, RIGHTDOWN };

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

// Returns true if GLVECTOR2 pt is inside BOUNDINGXBOX box, false otherwise
bool PointInBox(GLVECTOR2 pt, BOUNDINGBOX box) {
	if (pt.x <= box.x + box.w &&
		pt.x >= box.x &&
		pt.y <= box.y + box.h &&
		pt.y >= box.y)
		return true;

	return false;
}

/* Returns true if this entity has a point in the other entity
bool entityInBox(BOUNDINGBOX thisBox, BOUNDINGBOX otherBox){
	GLVECTOR2 TL = VectorOf(thisBox.x, thisBox.y + thisBox.h);
	GLVECTOR2 TR = VectorOf(thisBox.x + thisBox.w, thisBox.y + thisBox.h);
	GLVECTOR2 BL = VectorOf(thisBox.x, thisBox.y);
	GLVECTOR2 BR = VectorOf(thisBox.x + thisBox.w, thisBox.y);
	if (PointInBox(TL, otherBox) ||
		PointInBox(TR, otherBox) ||
		PointInBox(BL, otherBox) ||
		PointInBox(BR, otherBox))
		return true;

	return false;
}
*/

velDir calcVelCase(GLVECTOR2 vel){
	double testAngle = atan2(vel.y, vel.x);
	if (testAngle == 0){
		return RIGHT;
	}
	else if (testAngle > 0 && testAngle < (PI / 2)){
		return RIGHTUP;
	}
	else if (testAngle == (PI / 2)){
		return UP;
	}
	else if (testAngle > (PI / 2) && testAngle < PI){
		return LEFTUP;
	}
	else if (testAngle == PI){
		return LEFT;
	}
	else if (testAngle > PI && testAngle < (3 * PI) / 2){
		return LEFTDOWN;
	}
	else if (testAngle == (3 * PI) / 2){
		return DOWN;
	}
	else{
		return RIGHTDOWN;
	}
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
	GLVECTOR2 TR = VectorOf(box.x + box.w, box.y + box.h);
	// Bottom left corner of this box
	GLVECTOR2 BL = VectorOf(box.x, box.y);
	// Bottom right corner of this box
	GLVECTOR2 BR = VectorOf(box.x + box.w, box.y);
	// Top left corner of other box
	GLVECTOR2 OTL = VectorOf(otherBox.x, otherBox.y + otherBox.h);
	// Top right corner of other box
	GLVECTOR2 OTR = VectorOf(otherBox.x + otherBox.w, otherBox.y + otherBox.h);
	// Bottom left corner of other box
	GLVECTOR2 OBL = VectorOf(otherBox.x, otherBox.y);
	// Bottom right corner of other box
	GLVECTOR2 OBR = VectorOf(otherBox.x + otherBox.w, otherBox.y);

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
		if (PointInBox(TR, otherBox)){
			Vel.y *= -1;
			Pos.y = otherBox.y - box.w;
			//std::cout << ("Top") << std::endl;
		}
		else if (PointInBox(BL, otherBox)){
			Vel.x *= -1;
			Pos.x = otherBox.x + otherBox.w + box.w;
			//std::cout << ("Left") << std::endl;
		}
		else{
			if (calcVelCase(Vel) == RIGHTUP || calcVelCase(Vel) == UP){
				Vel.y *= -1;
				Pos.y = otherBox.y - box.w;
			}
			// TL corner
			else if (calcVelCase(Vel) == LEFTUP){
				if (PointInBox(VectorOf(box.x + 1.0, box.y + box.h), otherBox)){
					Vel.y *= -1;
					Pos.y = otherBox.y - box.w;
				}
				else{
					Vel.x *= -1;
					Pos.x = otherBox.x + otherBox.w + box.w;
				}
			}
			else if (calcVelCase(Vel) == LEFT || calcVelCase(Vel) == LEFTDOWN){
				Vel.x *= -1;
				Pos.x = otherBox.x + otherBox.w + box.w;
			}
				else{
				std::cout << ("TL ydishappen") << std::endl;
				}
			//std::cout << ("Top Left") << std::endl;
		}
	}
	else if (PointInBox(TR, otherBox)){
		if (PointInBox(BR, otherBox)){
			Vel.x *= -1;
			Pos.x = otherBox.x - box.w;
				//std::cout << ("Right") << std::endl;
			}
			// TR corner
			else{
				if (calcVelCase(Vel) == RIGHT || calcVelCase(Vel) == RIGHTDOWN){
					Vel.x *= -1;
					Pos.x = otherBox.x - box.w;
				}
				else if (calcVelCase(Vel) == RIGHTUP){
					if (PointInBox(VectorOf(box.x + box.w - 1.0, box.y + box.h), otherBox)){
						Vel.y *= -1;
						Pos.y = otherBox.y - box.w;
				}
					else{
					Vel.x *= -1;
					Pos.x = otherBox.x - box.w;
					}
				}
				else if (calcVelCase(Vel) == LEFTUP || calcVelCase(Vel) == UP){
					Vel.y *= -1;
					Pos.y = otherBox.y - box.w;
				}
				else{
					std::cout << "TR yudothis" << std::endl;
				}
				//std::cout << ("Top Right") << std::endl;
		}
	}
	else if (PointInBox(BR, otherBox)){
		if (PointInBox(BL, otherBox)){
			Vel.y *= -1;
			Pos.y = otherBox.y + otherBox.h + box.w;
			//std::cout << ("Bottom") << std::endl;
		}
		else{
			// BR corner
			if (calcVelCase(Vel) == RIGHTUP || calcVelCase(Vel) == RIGHT){
				Vel.x *= -1;
				Pos.x = otherBox.x - box.w;
			}
			else if (calcVelCase(Vel) == RIGHTDOWN){
				if (PointInBox(VectorOf(box.x + box.w, box.y + 1.0), otherBox)){
					Vel.x *= -1;
					Pos.x = otherBox.x - box.w;
				}
				else{
					Vel.y *= -1;
					Pos.y = otherBox.y + otherBox.h + box.w;
				}
			}
			else if (calcVelCase(Vel) == DOWN || calcVelCase(Vel) == LEFTDOWN){
				Vel.y *= -1;
				Pos.y = otherBox.y + otherBox.h + box.w;
			}
			else{
				std::cout << "BR nope" << std::endl;
			}
			//std::cout << ("Bottom Right") << std::endl;
		}
	}
	// BL corner
	else if (PointInBox(BL, otherBox)){
		if (calcVelCase(Vel) == LEFTUP || calcVelCase(Vel) == LEFT){
			Vel.x *= -1;
			Pos.x = otherBox.x + otherBox.w + box.w;
		}
		else if (calcVelCase(Vel) == LEFTDOWN){
			if (PointInBox(VectorOf(box.x, box.y + 1.0), otherBox)){
				Vel.x *= -1;
				Pos.x = otherBox.x + otherBox.w + box.w;
			}
			else{
				Vel.y *= -1;
				Pos.y = otherBox.y + otherBox.h + box.w;
			}
		}
		else if (calcVelCase(Vel) == DOWN || calcVelCase(Vel) == RIGHTDOWN){
			Vel.y *= -1;
			Pos.y = otherBox.y + otherBox.h + box.w;
		}
		else{
			std::cout << "BL bleh" << std::endl;
		}
		//std::cout << ("Bottom Left") << std::endl;
	}
	// If ball top collides with wall between its corners
	else if (PointInBox(OBL, box) && PointInBox(OBR, box)){
		Vel.y *= -1;
		Pos.y = otherBox.y - box.w;
	}
	// If ball right collides with wall between its corners
	else if (PointInBox(OTR, box) && PointInBox(OBR, box)){
		Vel.x *= -1;
		Pos.x = otherBox.x - box.w;
	}
	// If ball bottom collides with wall between its corners
	else if (PointInBox(OTL, box) && PointInBox(OTR, box)){
		Vel.y *= -1;
		Pos.y = otherBox.y + otherBox.h + box.w;
	}
	// If ball left collides with wall between its corners
	else if (PointInBox(OTR, box) && PointInBox(OBR, box)){
		Vel.x *= -1;
		Pos.x = otherBox.x + otherBox.w + box.w;
	}
	else{
		Vel.y *= -1;
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
	box.x = Pos.x - radius / 2;
	box.y = Pos.y - radius / 2;
	box.w = radius;
	box.h = radius;

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