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
	static Minigame * _Instance;

	STATE MinigameState;
	MENUSTATE MenuState;
	GAMESTATE GameState;

	HWND hwnd;

public:

	static Minigame * Instance() {
		if (!_Instance)
			_Instance = new Minigame();

		return _Instance;
	}

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
	MinigameMenu();
	static MinigameMenu * _Instance;

	Minigame::MENUSTATE MenuState;

	void MainThink();
	void SettingsThink();

public:
	void Think();
	void Draw();
	
	void Resize();

	static MinigameMenu * Instance() {
		if (!_Instance)
			_Instance = new MinigameMenu();

		return _Instance;
	}
};

class MinigameGame {
private:
	MinigameGame();
	static MinigameGame * _Instance;

	Minigame::GAMESTATE state;

	int Level;
	int NumMoves;

	void NewMap();
	void WaitingThink();
	void RunningThink();

public:
	void Think();
	void Draw();

	static MinigameGame * Instance() {
		if (!_Instance)
			_Instance = new MinigameGame();

		return _Instance;
	}

	void Resize();
};

#endif