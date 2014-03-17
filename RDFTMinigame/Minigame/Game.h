#ifndef __GAME__
#define __GAME__
#include "..\EngineLib\EngineCommon.h"
#include "..\EngineLib\RDFTEngine.h"
#include <math.h>

RDFTENGINE * Engine();

class MinigameMenu {
private:
	MinigameMenu();

	Minigame::MENUSTATE MenuState;

public:
	void Think();
	void MainThink();
	void SettingsThink();

	static MinigameMenu * Instance();
};

class MinigameGame {
private:
	MinigameGame();

	Minigame::GAMESTATE state;

public:
	void Think();
	void WaitingThink();
	void RunningThink();

	static MinigameGame * Instance();
};

class Minigame {
public:
	enum STATE { MENU, GAME };
	enum MENUSTATE { MAIN, SETTINGS };
	enum GAMESTATE { WAITING, RUNNING };

private:
	STATE MinigameState;
	MENUSTATE MenuState;
	GAMESTATE GameState;

	Minigame();

public:

	static Minigame * Instance();
	void Think();

	~Minigame();
};

#endif