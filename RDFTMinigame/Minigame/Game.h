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
	STATE MinigameState;
	MENUSTATE MenuState;
	GAMESTATE GameState;

	Minigame();

	void MenuThink();
	void MenuMainThink();
	void MenuSettingsThink();

	void GameThink();
	void GameWaitingThink();
	void GameRunningThink();

public:

	static Minigame * Instance();
	void Think();

	~Minigame();
};

#endif