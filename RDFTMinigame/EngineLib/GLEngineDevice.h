#ifndef __GLENGINE__
#define __GLENGINE__
#include <Windows.h>

class GLENGINEDEVICE {
public:
	GLENGINEDEVICE();

	virtual bool CreateRenderDevice(HWND hwnd) = 0;
	virtual void SetWindowSize(int width, int height) = 0;

	virtual bool BeginScene() = 0;
	virtual void Render(ENTITY * ent) = 0;
	virtual bool EndScene() = 0;

	virtual bool ReleaseRenderDevice() = 0;

	virtual ~GLENGINEDEVICE() = 0;
};

class ENTITY {
private:
	int PosX, PosY;

public:
	ENTITY() {
		PosX = 0;
		PosY = 0;
	}

	ENTITY(int x, int y) {
		PosX = x;
		PosY = y;
	}

	int getX() const {
		return PosX;
	}

	int getY() const {
		return PosY;
	}

	RECT getRect();
};


#endif