#ifndef __GAME__
#define __GAME__
#include "..\EngineLib\EngineCommon.h"
#include "..\EngineLib\RDFTEngine.h"
#include <math.h>

RDFTENGINE * Engine();

class Minigame {
public:
	enum STATE { MENU, GAME };
	enum MENUSTATE { MAIN, SETTINGS };
	enum GAMESTATE { WAITING, RUNNING };

private:
	Minigame();

	STATE MinigameState;
	MENUSTATE MenuState;
	GAMESTATE GameState;

	HWND hwnd;

public:

	static Minigame * Instance() {
		return NULL;
	}

	void Setup(HWND hwnd);
	void Resize();

	void Think();

	void SetState(STATE state) {
		MinigameState = state;
	}

	~Minigame();
};

class MinigameMenu {
private:
	MinigameMenu();

	Minigame::MENUSTATE MenuState;

public:
	void Think();
	void MainThink();
	void SettingsThink();
	void Resize();

	static MinigameMenu * Instance() {
		return NULL;
	}
};

class MinigameGame {
private:
	MinigameGame();

	Minigame::GAMESTATE state;

	int Level;
	int NumMoves;

	void NewMap();
	void Resize();

public:
	void Think();
	void WaitingThink();
	void RunningThink();

	static MinigameGame * Instance() {
		return NULL;
	}
};

#endif