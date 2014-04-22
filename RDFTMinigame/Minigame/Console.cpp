#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include "Game.h"
#include "Console.h"

using namespace std;

// maximum mumber of lines the output console should have
static const WORD MAX_CONSOLE_LINES = 100000;

void SetupConsole() {
	int hConHandle;
	long lStdHandle;
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	FILE *fp;

	// allocate a console for this app
	AllocConsole();

	// set the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	coninfo.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

	// redirect unbuffered STDOUT to the console
	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "w");

	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);

	// redirect unbuffered STDIN to the console
	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "r");
	*stdin = *fp;
	setvbuf(stdin, NULL, _IONBF, 0);

	// redirect unbuffered STDERR to the console
	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "w");
	*stderr = *fp;
	setvbuf(stderr, NULL, _IONBF, 0);

	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
	// point to console as well
	ios::sync_with_stdio();

}

int BuildArgs(char *args[], char * buf) {
	char arg[50];
	int ct = 0;

	char * start = buf;
	int len = strlen(buf);

	while ((buf - start) < len && sscanf(buf, "%s ", arg) == 1 && ct < 20) {
		buf += (strlen(arg) + 1);
		args[ct] = new char[50];
		strcpy_s(args[ct], 50, arg);
		ct++;
	}

	return ct;
}

void FreeCMD(COMMAND * cmd) {
	int i;
	for (i = 0; i < cmd->argc; i++) {
		delete cmd->argv[i];
	}

	delete cmd;
}

void Dispatch(char * buf, int size, Console * con) {
	COMMAND * cmd = new COMMAND;

	if (strstr(buf, "env") != 0)
		cmd->cty = CMDTYPE::ENV;
	else if (strstr(buf, "texture") != 0)
		cmd->cty = CMDTYPE::TEXTURE;
	else if (strstr(buf, "new_map") != 0)
		cmd->cty = CMDTYPE::NEWMAP;
	else if (strstr(buf, "exit") != 0)
		cmd->cty = CMDTYPE::KILL;
	else if (strstr(buf, "err") != 0)
		cmd->cty = CMDTYPE::GETERR;
	else
		return;

	cmd->argc = BuildArgs(cmd->argv, buf);

	con->Queue(cmd);
}

void Console::Queue(COMMAND * cmd) {
	qMutex.lock();
	cmdq.push(cmd);
	qMutex.unlock();
	
}

DWORD WINAPI Worker(void * params) {
	Console * con = (Console *)params;
	char buf[200];

	while (1) {
		Con()->WaitFor();
		cout << "$>";
		cin.getline(buf, 200);
		Dispatch(buf, 200, con);
	}
}

Console::Console() : cmdq() {
	SetupConsole();
}

void Console::Start() {
	std::cout << "Initializing user input thread...\n";
	thr = CreateThread(0, 0, Worker, this, 0, 0);
}

void Console::ExecSync() {
	
	qMutex.lock();
	bool hasCmd = !cmdq.empty();

	while (!cmdq.empty()) {
		Exec(cmdq.front());
		FreeCMD(cmdq.front());
		cmdq.pop();
	}

	qMutex.unlock();

	if (hasCmd)
		cout << "$>";

}

void Console::WaitFor() {
	running.lock();
	running.unlock();
}

void Console::Exec(COMMAND * cmd) {

	if (cmd->cty == CMDTYPE::NEWMAP) {
		MG()->gameMutex.lock();
		MG()->NewMap();
		MG()->gameMutex.unlock();
	}
	else if (cmd->cty == CMDTYPE::TEXTURE) {
		if (cmd->argc == 4 && strcmp(cmd->argv[1], "load") == 0) {
			Engine()->GetGlDevice()->LoadTexture(cmd->argv[2], cmd->argv[3]);
		}	
		else if (cmd->argc == 3 && strcmp(cmd->argv[1], "unload") == 0) {
			Engine()->GetGlDevice()->UnloadTexture(cmd->argv[2]);
		}
		else
			Engine()->GetGlDevice()->PrintTextures();
	}
	else if (cmd->cty == CMDTYPE::ENV) {
		ENVVAR * ev;
		if (cmd->argc == 4) {
			ev = new ENVVAR;
			strcpy(ev->value, cmd->argv[3]);
			ev->boolset = false;
			ev->numset = false;

			Engine()->SetEnv(cmd->argv[2], ev);
		}
		else
			Engine()->PrintEnv();
	}
	else if (cmd->cty == CMDTYPE::GETERR) {
		Engine()->GetGlDevice()->PrintError();
	}
}

void Console::Stop() {
	TerminateThread(thr, 0);
}

Console * Con() {
	static Console * con = new Console();
	return con;
}