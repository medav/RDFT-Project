#ifndef __PHYSENGINEDEVICE__
#define __PHYSENGINEDEVICE__
#include <Windows.h>
#include "EngineCommon.h"
#include "GLEngineDevice.h"

class ENTITY {
public:
	enum TYPE { STATIC, MOVING };

protected:
	GLVECTOR2 Pos;
	ClockKeeper ck;

public:

	ENTITY() : ck() {
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
	virtual void Draw(PGLENGINE glEngine) {}
	virtual void Collide(ENTITY * other) {}
	virtual bool CollidesWith(ENTITY * other) { return false; }
	virtual BOUNDINGBOX BoundingBox() = 0;

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

	virtual BOUNDINGBOX BoundingBox();

	virtual ENTITY::TYPE Type() {
		return ENTITY::STATIC;
	}
};

class Wall : public World {

public:
	Wall(GLVECTOR2 Pos, float w, float h) : World(Pos, w, h) {}

	virtual void Draw(PGLENGINE gl);
};

class Hole : public ENTITY {
public:
	Hole(GLVECTOR2 Pos) : ENTITY(Pos) {}

	virtual void Draw(PGLENGINE glEngine);

	virtual ENTITY::TYPE Type() {
		return ENTITY::STATIC;
	}
};

class Ball : public ENTITY {
private:
	// Kinetic friction coef. (This isn't the traditional definition)
	const double mk = 0.997;

	// Collision constant: How much to decrease speed by after collision
	const double cc = 1.0;

	GLVECTOR2 Vel;

	double radius;

public:
	Ball(GLVECTOR2 Pos) : ENTITY(Pos) {
		Vel.x = 0;
		Vel.y = 0;
		radius = 8;
	}

	virtual void Think();
	virtual void Draw(PGLENGINE glEngine);
	virtual void Collide(ENTITY * other);

	virtual BOUNDINGBOX BoundingBox();

	void ApplyVelocity(float x, float y);

	virtual ENTITY::TYPE Type() {
		return ENTITY::MOVING;
	}
};

class PHYSENGINEDEVICE {
public:
	PHYSENGINEDEVICE() {}

	virtual void Init() = 0;
	virtual void Think() = 0;
	virtual void Draw(PGLENGINE glEngine) = 0;

	virtual void AddEntity(ENTITY * ent) = 0;
	virtual void Clear() = 0;

	virtual ~PHYSENGINEDEVICE() {}
};

typedef PHYSENGINEDEVICE* PPHYSENGINE;
typedef PHYSENGINEDEVICE** LPPHYSENGINE;

#endif