#ifndef __PHYSENGINEDEVICE__
#define __PHYSENGINEDEVICE__
#include <Windows.h>
#include "EngineCommon.h"
#include "GLEngineDevice.h"

class PHYSENGINEDEVICE {
public:
	PHYSENGINEDEVICE() {}

	virtual void init() = 0;

	virtual void Think() = 0;

	virtual void AddEntity(ENTITY * ent) = 0;

	virtual ~PHYSENGINEDEVICE() {}
};

class ENTITY {
public:
	enum TYPE { STATIC, MOVING };

protected:
	GLVECTOR2 Pos;

public:

	ENTITY() {
		Pos.x = 0;
		Pos.y = 0;
	}

	ENTITY(GLVECTOR2 Pos) {
		this->Pos = Pos;
	}

	virtual void SetX(float x) {
		this->Pos.x = x;
	}

	virtual void SetY(float y) {
		this->Pos.y = y;
	}

	virtual void Think() {}
	virtual void Draw(PGLENGINE gl) {}
	virtual void Collide(ENTITY * other) {}
	virtual bool CollidesWith(ENTITY * other) = 0;
	virtual BOUNDINGBOX BoudingBox() = 0;

	virtual TYPE Type() = 0;
};

class World : public ENTITY {
protected:
	float Width;
	float Height;

public:
	World(GLVECTOR2 Pos, float w, float h) : ENTITY(Pos) {
		Width = w;
		Height = h;
	}

	virtual ENTITY::TYPE Type() {
		return ENTITY::STATIC;
	}
};

class Wall : public World {

public:
	Wall(GLVECTOR2 Pos, float w, float h) : World(Pos) {}

	virtual void Draw();
};

class Hole : public ENTITY {
public:
	Hole(GLVECTOR2 Pos) : ENTITY(Pos) {}

	virtual void Draw();

	virtual ENTITY::TYPE Type() {
		return ENTITY::STATIC;
	}
};

class Ball : public ENTITY {
private:
	// Kinetic friction coef.
	const double mk = 0.7;

	// Collision constant
	const double cc = 0.1;

	GLVECTOR2 Vel;

public:
	Ball(GLVECTOR2 Pos) : ENTITY(Pos) {
		Vel.x = 0;
		Vel.y = 0;
	}

	virtual void Think();
	virtual void Collide(ENTITY * other);

	void ApplyVelocity(float x, float y);

	virtual ENTITY::TYPE Type() {
		return ENTITY::MOVING;
	}
};

typedef PHYSENGINEDEVICE* PPHYSENGINE;
typedef PHYSENGINEDEVICE** LPPHYSENGINE;

#endif