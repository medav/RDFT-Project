#include "PHYSEngine.h"

enum velDir{ RIGHT, RIGHTUP, UP, LEFTUP, LEFT, LEFTDOWN, DOWN, RIGHTDOWN };
#define PI 3.1415926

PHYSENGINE::PHYSENGINE(HWND hwnd) {
	this->hwnd = hwnd;
	ents = new std::vector<ENTITY *>();
}

void PHYSENGINE::Init() {

}

void PHYSENGINE::AddEntity(ENTITY * ent) {
	ents->push_back(ent);
}

void PHYSENGINE::Clear() {
	for (int i = ents->size() - 1; i >= 0; i--){
		delete (*ents)[i];
	}
	delete ents;
	ents = new std::vector<ENTITY *>();
}

bool Collide(BOUNDINGBOX b1, BOUNDINGBOX b2) {
	if (b1.x + b1.w < b2.x ||
		b2.x + b2.w < b1.x ||
		b1.y + b1.h < b2.y ||
		b2.y + b2.h < b1.y)
		return false;

	return true;
}

void PHYSENGINE::Think() {

	// Call Think() for all ENTITYs
	for (unsigned int i = 0; i < ents->size(); i++){
		(*ents)[i]->Think();

	}

	// Search for collisions
	for (unsigned int i = 0; i < ents->size(); i++){
		if ((*ents)[i]->Type() == ENTITY::MOVING){
			for (unsigned int j = 0; j < (*ents).size(); j++){
				if ((*ents)[i] != (*ents)[j]) {
					if (Collide((*ents)[i]->BoundingBox(), (*ents)[j]->BoundingBox()))
						(*ents)[i]->Collide((*ents)[j]);
				}
			}
		}
	}
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
	else if (testAngle >(PI / 2) && testAngle < PI){
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

GLVECTOR2 PHYSENGINE::DoCollision(ENTITY * Moving, ENTITY * Static) {

	BOUNDINGBOX box = Moving->BoundingBox();
	BOUNDINGBOX otherBox = Static->BoundingBox();

	GLVECTOR2 Vel = Moving->getVel();
	GLVECTOR2 Pos = Moving->getPos();

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

	int reposVal = 25;

	if (PointInBox(TL, otherBox)){
		if (PointInBox(TR, otherBox)){
			Vel.y *= -1;
			Pos.y = otherBox.y - reposVal;
			//std::cout << ("Top") << std::endl;
		}
		else if (PointInBox(BL, otherBox)){
			Vel.x *= -1;
			Pos.x = otherBox.x + otherBox.w + reposVal;
			//std::cout << ("Left") << std::endl;
		}
		else{
			if (calcVelCase(Vel) == RIGHTUP || calcVelCase(Vel) == UP){
				Vel.y *= -1;
				Pos.y = otherBox.y - reposVal;
			}
			// TL corner
			else if (calcVelCase(Vel) == LEFTUP){
				if (PointInBox(VectorOf(box.x + 20, box.y + box.h), otherBox)){
					Vel.y *= -1;
					Pos.y = otherBox.y - reposVal;
				}
				else{
					Vel.x *= -1;
					Pos.x = otherBox.x + otherBox.w + reposVal;
				}
			}
			else if (calcVelCase(Vel) == LEFT || calcVelCase(Vel) == LEFTDOWN){
				Vel.x *= -1;
				Pos.x = otherBox.x + otherBox.w + reposVal;
			}
		}
	}
	else if (PointInBox(TR, otherBox)) {
		if (PointInBox(BR, otherBox)) {
			Vel.x *= -1;
			Pos.x = otherBox.x - reposVal;
		}
		// TR corner
		else {
			if (calcVelCase(Vel) == RIGHT || calcVelCase(Vel) == RIGHTDOWN) {
				Vel.x *= -1;
				Pos.x = otherBox.x - reposVal;
			}
			else if (calcVelCase(Vel) == RIGHTUP) {
				if (PointInBox(VectorOf(box.x + box.w - 20, box.y + box.h), otherBox)) {
					Vel.y *= -1;
					Pos.y = otherBox.y - reposVal;
				}
				else {
					Vel.x *= -1;
					Pos.x = otherBox.x - reposVal;
				}
			}
			else if (calcVelCase(Vel) == LEFTUP || calcVelCase(Vel) == UP) {
				Vel.y *= -1;
				Pos.y = otherBox.y - reposVal;
			}
		}
	}
	else if (PointInBox(BR, otherBox)) {
		if (PointInBox(BL, otherBox)) {
			Vel.y *= -1;
			Pos.y = otherBox.y + otherBox.h + reposVal;
		}
		else{
			// BR corner
			if (calcVelCase(Vel) == RIGHTUP || calcVelCase(Vel) == RIGHT) {
				Vel.x *= -1;
				Pos.x = otherBox.x - reposVal;
			}
			else if (calcVelCase(Vel) == RIGHTDOWN) {
				if (PointInBox(VectorOf(box.x + box.w, box.y + 20), otherBox)) {
					Vel.x *= -1;
					Pos.x = otherBox.x - reposVal;
				}
				else {
					Vel.y *= -1;
					Pos.y = otherBox.y + otherBox.h + reposVal;
				}
			}
			else if (calcVelCase(Vel) == DOWN || calcVelCase(Vel) == LEFTDOWN) {
				Vel.y *= -1;
				Pos.y = otherBox.y + otherBox.h + reposVal;
			}
		}
	}
	// BL corner
	else if (PointInBox(BL, otherBox)) {
		if (calcVelCase(Vel) == LEFTUP || calcVelCase(Vel) == LEFT) {
			Vel.x *= -1;
			Pos.x = otherBox.x + otherBox.w + reposVal;
		}
		else if (calcVelCase(Vel) == LEFTDOWN) {
			if (PointInBox(VectorOf(box.x, box.y + 20), otherBox)) {
				Vel.x *= -1;
				Pos.x = otherBox.x + otherBox.w + reposVal;
			}
			else {
				Vel.y *= -1;
				Pos.y = otherBox.y + otherBox.h + reposVal;
			}
		}
		else if (calcVelCase(Vel) == DOWN || calcVelCase(Vel) == RIGHTDOWN) {
			Vel.y *= -1;
			Pos.y = otherBox.y + otherBox.h + reposVal;
		}
	}
	// If ball top collides with wall between its corners
	else if (PointInBox(OBL, box) && PointInBox(OBR, box)) {
		Vel.y *= -1;
		Pos.y = otherBox.y - reposVal;
	}
	// If ball right collides with wall between its corners
	else if (PointInBox(OTR, box) && PointInBox(OBR, box)) {
		Vel.x *= -1;
		Pos.x = otherBox.x - reposVal;
	}
	// If ball bottom collides with wall between its corners
	else if (PointInBox(OTL, box) && PointInBox(OTR, box)) {
		Vel.y *= -1;
		Pos.y = otherBox.y + otherBox.h + reposVal;
	}
	// If ball left collides with wall between its corners
	else if (PointInBox(OTR, box) && PointInBox(OBR, box)) {
		Vel.x *= -1;
		Pos.x = otherBox.x + otherBox.w + reposVal;
	}
	else {
		if (abs(Vel.x) > abs(Vel.y))
			Vel.x *= -1;
		else
			Vel.y *= -1;
	}

	Moving->SetPos(Pos);
	return Vel;
}

void PHYSENGINE::Draw(PGLENGINE glEngine) {
	for (unsigned int i = 0; i < ents->size(); i++){
		(*ents)[i]->Draw(glEngine);
	}
}

PHYSENGINE::~PHYSENGINE() {

}

bool CreatePhysDevice(LPPHYSENGINE device, HWND hwnd) {
	*device = new PHYSENGINE(hwnd);

	return true;
}

bool ReleasePhysDevice(PHYSENGINEDEVICE * device) {
	if (!device)
		return true;

	PHYSENGINE * engine = (PHYSENGINE *)device;
	delete engine;

	return true;
}

bool APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// A process is loading the DLL.
		break;
	case DLL_THREAD_ATTACH:
		// A process is creating a new thread.
		break;
	case DLL_THREAD_DETACH:
		// A thread exits normally.
		break;
	case DLL_PROCESS_DETACH:
		// A process unloads the DLL.
		break;
	}
	return true;
}