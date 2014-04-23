#ifndef __GAME__
#define __GAME__
#include "..\EngineLib\RDFTEngine.h"
#include <math.h>


class Minigame {
public:
	enum GAMESTATE { WAITING, RUNNING, WINNING };

private:
	Minigame::GAMESTATE GameState;
	unsigned char lmState;

	HWND hwnd;
	void Setup(HWND hwnd);

	int Level;
	int NumMoves;

	Ball * ball;
	Hole * hole;

	void WaitingThink();
	void RunningThink();
	void WinningThink();

	void WaitingDraw();
	void RunningDraw();
	void WinningDraw();

public:
	Minigame();
	void Think();
	void Draw();
	void NewMap();
	void NewGame();

	void IncMoves() {
		NumMoves++;
	}

	void SetState(GAMESTATE state) {
		GameState = state;
	}

	Ball * GetBall() {
		return ball;
	}

	void Resize();
};


Minigame * MG();

#endif