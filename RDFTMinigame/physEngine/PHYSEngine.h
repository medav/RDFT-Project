#ifndef __PHYSENGINE__
#define __PHYSENGINE__
#include <vector>
#include "..\EngineLib\PhysEngineDevice.h"
#include "..\EngineLib\EngineCommon.h"

class PHYSENGINE : public PHYSENGINEDEVICE {
private:
	HWND hwnd;
	std::vector<ENTITY *> * ents;

public:
	PHYSENGINE(HWND hwnd);

	virtual void Init();

	virtual void AddEntity(ENTITY * ent);
	virtual void Clear();

	virtual void Think();
	virtual void Draw(PGLENGINE glEngine);

	virtual GLVECTOR2 DoCollision(ENTITY * Moving, ENTITY * Static);

	virtual GLVECTOR2 VectorOf(double x, double y) {
		GLVECTOR2 pos;
		pos.x = x;
		pos.y = y;

		return pos;
	}

	virtual double Magnitude(GLVECTOR2 vec) {
		return sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	~PHYSENGINE();
};

#endif