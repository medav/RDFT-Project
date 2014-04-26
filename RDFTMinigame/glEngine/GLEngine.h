#ifndef __GLENGINE__
#define __GLENGINE__
#include "..\EngineLib\GLEngineDevice.h"
#include "..\EngineLib\PhysEngineDevice.h"
#include "..\EngineLib\EngineCommon.h"
#include <gl\GL.h>
#include <gl\GLU.h>
#include <map>
#include <mutex>

typedef struct {
	uint8_t* datBuff[2];
	BITMAPFILEHEADER* bmpHeader;
	BITMAPINFOHEADER* bmpInfo;
	uint8_t* pixels;
} bmp_t;

struct TEXTURE {
	GLuint texID;
	uint8_t * pixels;
};

class GLENGINE : public GLENGINEDEVICE {
private:
	int windowWidth;
	int windowHeight;
	float r;

	HGLRC hrc;
	HDC hdc;
	HWND hwnd;

	GLuint listbase;

	std::map<std::string, TEXTURE *> textures;

	GLCOLORARGB bgColor;

	GLuint PrintErrorLine(int line);

	bmp_t LoadBMP(const char * file);
	bool CreateTex(const char* location, GLuint *texture, uint8_t ** pixels, const char * mask);

public:
	GLENGINE(HWND hwnd);
	bool CreateRenderDevice(HWND hwnd);
	virtual void SetWindowSize();

	virtual void SetClearColor(GLCOLORARGB bgcolor);
	virtual bool LoadTexture(const char * filename, const char * name, bool mask);
	virtual bool UnloadTexture(const char * name);
	virtual void PrintTextures();

	virtual void PrintError();

	virtual bool BeginScene();

	virtual void DrawRect(GLVERTEX2 pos, GLVECTOR2 size, GLCOLORARGB color);
	virtual void DrawTexturedRect(GLVERTEX2 pos, GLVECTOR2 size, const char * textureName);
	virtual void DrawCircle(GLVERTEX2 pos, GLVECTOR2 size, GLCOLORARGB color);
	virtual void DrawCircleHollow(GLVERTEX2 pos, GLVECTOR2 size, GLCOLORARGB color);
	virtual void DrawArrow(GLVECTOR2 begin, GLVECTOR2 end, float weight, GLCOLORARGB color);
	virtual void DrawTextGl(GLVECTOR2 pos, GLCOLORARGB color, const char * text);

	virtual bool EndScene();

	bool ReleaseRenderDevice();
	~GLENGINE();
};

#endif