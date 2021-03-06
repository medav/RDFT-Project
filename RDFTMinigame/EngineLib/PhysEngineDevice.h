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

	virtual void SetX(double x) {
		this->Pos.x = x;
	}

	virtual void SetY(double y) {
		this->Pos.y = y;
	}

	virtual void SetPos(GLVECTOR2 newPos) {
		Pos.x = newPos.x;
		Pos.y = newPos.y;
	}

	virtual GLVECTOR2 getPos() {
		return Pos;
	}

	virtual GLVECTOR2 getVel() {
		return VectorOf(0.0, 0.0);
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
	double Width;
	double Height;

public:
	World(GLVECTOR2 Pos, double w, double h) : ENTITY(Pos) {
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
	Wall(GLVECTOR2 Pos, double w, double h) : World(Pos, w, h) {}

	virtual void Draw(PGLENGINE gl);
};

class Hole : public ENTITY {
private:
	double radius;
	bool BallCollided;

public:
	Hole(GLVECTOR2 Pos) : ENTITY(Pos) {
		radius = 45;
		BallCollided = false;
	}

	virtual void Draw(PGLENGINE glEngine);
	virtual void Collide(ENTITY * other);
	virtual BOUNDINGBOX BoundingBox();

	bool HasBallCollided() {
		return BallCollided;
	}

	virtual ENTITY::TYPE Type() {
		return ENTITY::STATIC;
	}
};

class Ball : public ENTITY {
private:
	int timeInOther = 0;
	GLVECTOR2 Vel;
	double radius;

public:
	Ball(GLVECTOR2 Pos) : ENTITY(Pos) {
		Vel.x = 0;
		Vel.y = 0;
		radius = 45;
	}

	virtual void Think();
	virtual void Draw(PGLENGINE glEngine);
	virtual void Collide(ENTITY * other);

	bool isStopped();

	virtual BOUNDINGBOX BoundingBox();

	void ApplyVelocity(float x, float y);

	virtual GLVECTOR2 getVel() {
		return Vel;
	}

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
	virtual GLVECTOR2 DoCollision(ENTITY * Moving, ENTITY * Static) = 0;

	virtual void AddEntity(ENTITY * ent) = 0;
	virtual GLVECTOR2 VectorOf(double x, double y) = 0;
	virtual double Magnitude(GLVECTOR2 vec) = 0;
	virtual void Clear() = 0;

	virtual ~PHYSENGINEDEVICE() {}
};

typedef PHYSENGINEDEVICE* PPHYSENGINE;
typedef PHYSENGINEDEVICE** LPPHYSENGINE;

#endif