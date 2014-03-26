#ifndef __GAME__
#define __GAME__
#include "..\EngineLib\EngineCommon.h"
#include "..\EngineLib\RDFTEngine.h"
#include <math.h>

class Minigame {
public:
	enum STATE { MENU, GAME };
	enum MENUSTATE { MAIN, SETTINGS };
	enum GAMESTATE { WAITING, RUNNING };

private:
	STATE MinigameState;
	MENUSTATE MenuState;
	GAMESTATE GameState;

	HWND hwnd;

public:
	Minigame();

	void Setup(HWND hwnd);
	void Resize();

	void Think();
	void Draw();

	void SetState(STATE state) {
		MinigameState = state;
	}

	~Minigame();
};

class MinigameMenu {
private:
	Minigame::MENUSTATE MenuState;

	void MainThink();
	void SettingsThink();

	void MainDraw();
	void SettingsDraw();

public:
	MinigameMenu() {}

	void Think();
	void Draw();
	
	void Resize();
};

class MinigameGame {
private:
	Minigame::GAMESTATE GameState;

	int Level;
	int NumMoves;

	void NewMap();
	void WaitingThink();
	void RunningThink();

	void WaitingDraw();
	void RunningDraw();

public:
	MinigameGame();

	void Think();
	void Draw();

	void Resize();
};

RDFTENGINE * Engine();
Minigame * MG();
MinigameMenu * MGM();
MinigameGame * MGG();

#endif