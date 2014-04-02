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
static const WORD MAX_CONSOLE_LINES = 500;

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

void Dispatch(const char * buf, int size, Console * con) {
	COMMAND cmd;
	if (strstr(buf, "set") != 0)
		cmd.cty = CMDTYPE::SET;
	else if (strstr(buf, "print") != 0)
		cmd.cty = CMDTYPE::PRINT;
	else if (strstr(buf, "new_map") != 0)
		cmd.cty = CMDTYPE::NEWMAP;
	else if (strstr(buf, "exit") != 0)
		cmd.cty = CMDTYPE::KILL;
	else
		return;

	strcpy_s(cmd.args, buf);

	con->Exec(cmd);
}

DWORD WINAPI Worker(void * params) {
	Console * con = (Console *)params;
	char buf[200];

	while (1) {
		cout << "$>";
		cin.getline(buf, 200);
		
		Dispatch(buf, 200, con);
	}
}

Console::Console() {
	SetupConsole();
}

void Console::Start() {
	std::cout << "Initializing user input thread...\n";
	thr = CreateThread(0, 0, Worker, this, 0, 0);
}

void Console::Exec(COMMAND cmd) {
	if (cmd.cty == CMDTYPE::NEWMAP) {
		MG()->gameMutex.lock();
		MG()->NewMap();
		MG()->gameMutex.unlock();
	}
}

void Console::Stop() {
	TerminateThread(thr, 0);
}

Console * Con() {
	static Console * con = new Console();
	return con;
}