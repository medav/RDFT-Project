#include "PhysEngineDevice.h"

void Ball::Think() {
	// Update Pos based on velocity Vel
	SetX(Pos.x + (Vel.x * ck.DeltaT()));
	SetY(Pos.y + (Vel.y * ck.DeltaT()));

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

// Bounding Box Methods
BOUNDINGBOX World::BoudingBox() {
	BOUNDINGBOX box;
	box.x = Pos.x - Width / 2;
	box.y = Pos.y - Height / 2;
	box.w = Width;
	box.h = Height;

	return box;
}

BOUNDINGBOX Ball::BoudingBox() {
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