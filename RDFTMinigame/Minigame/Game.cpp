#include "Game.h"

//enum STATE { /* Fill this in */ };

RDFTENGINE * Engine() {
	static RDFTENGINE rdft;
	return &rdft;
}
/*
void GameThink() {
	STATE st;

	switch (st) {
	case STATE::MENU:
		DO_MENU_THINK();
		break;
	case STATE::GAME_PLAYING:
		DO_GAME_WAITING_THINK();
		break;
	default:

	}
}
void GameDraw();
*/