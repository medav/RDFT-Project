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
		MenuThink();
		break;
	case GAME:
		GameThink();
		break;
	default:
	}
}

void Minigame::MenuThink() {
	switch (MenuState) {
	case MAIN:
		MenuMainThink();
		break;
	case SETTINGS:
		MenuSettingsThink();
		break;
	default:
	}
}

void Minigame::MenuMainThink() {
	// TODO:
}

void Minigame::MenuSettingsThink() {
	// TODO:
}

void Minigame::GameThink() {
	// TODO:
}

void Minigame::GameWaitingThink() {
	// TODO:
}

void Minigame::GameRunningThink() {
	// TODO:
}
