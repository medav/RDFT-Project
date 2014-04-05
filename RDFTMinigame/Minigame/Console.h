#ifndef __CONSOLE__
#define __CONSOLE__
#include <Windows.h>

void SetupConsole();

enum CMDTYPE {SET, TEXTURE, NEWMAP, KILL, ENV};

typedef struct {
	CMDTYPE cty;
	char *argv[20];
	int argc;
} COMMAND;

class Console {
private:
	HANDLE thr;

public:
	Console();
	
	void Start();
	void Exec(COMMAND cmd);
	void Stop();

};

Console * Con();

#endif