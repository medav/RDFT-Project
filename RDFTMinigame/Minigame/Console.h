#ifndef __CONSOLE__
#define __CONSOLE__
#include <Windows.h>
#include <queue>
#include <mutex>
#include <condition_variable>

void SetupConsole();

enum CMDTYPE {SET, TEXTURE, NEWMAP, KILL, ENV, GETERR, HELP};

typedef struct {
	CMDTYPE cty;
	char *argv[20];
	int argc;
} COMMAND;

class Console {
private:
	HANDLE thr;
	std::queue<COMMAND *> cmdq;
	std::mutex qMutex;
	std::mutex running;

	void Exec(COMMAND * cmd);

public:
	Console();

	std::condition_variable ExecDone;
	
	void Start();
	void ExecSync();
	void Queue(COMMAND * cmd);
	void Stop();
	void WaitFor();
};

Console * Con();

#endif