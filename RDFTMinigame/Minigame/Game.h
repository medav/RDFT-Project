#ifndef __GAME__
#define __GAME__
#include "..\EngineLib\RDFTEngine.h"
#include <math.h>
#include <mutex>


class Minigame {
public:
	enum GAMESTATE { WAITING, RUNNING };

private:
	Minigame::GAMESTATE GameState;
	unsigned char lmState;

	HWND hwnd;
	void Setup(HWND hwnd);

	int Level;
	int NumMoves;
	int Difficulty;
	Ball * ball;
	
	void WaitingThink();
	void RunningThink();

	void WaitingDraw();
	void RunningDraw();

public:
	Minigame();
	void Think();
	void Draw();
	void NewMap();

	std::mutex gameMutex;

	void SetState(GAMESTATE state) {
		GameState = state;
	}

	void Resize();
};


Minigame * MG();

#endif