#include "Game.h"

RDFTENGINE * Engine() {
	static RDFTENGINE rdft;
	return &rdft;
}

Minigame::Minigame() {
	MinigameState = GAME;
	MenuState = MAIN;
	GameState = WAITING;
}

void Minigame::Think() {
	switch (MinigameState) {
	case MENU:
		MinigameMenu::Instance()->Think();
		break;
	case GAME:
		MinigameGame::Instance()->Think();
		break;
	default:
		break;
	}
}

void Resize() {

}

/************************************************************/

void MinigameMenu::Think() {
	switch (MenuState) {
	case Minigame::MAIN:
		MainThink();
		break;
	case Minigame::SETTINGS:
		SettingsThink();
		break;
	default:
		break;
	}
}

void MinigameMenu::MainThink() {
	// TODO:
}

void MinigameMenu::SettingsThink() {
	// TODO:
}

/************************************************************/

MinigameGame::MinigameGame() {
	Level = 0;
	NewMap();
}

void MinigameGame::Think() {
	// TODO:
}

void MinigameGame::WaitingThink() {
	// TODO:
}

void MinigameGame::RunningThink() {
	// TODO:
}

/************************************************************/

void MinigameGame::NewMap() {
	Engine()->GetPhysDevice()->Clear();

}