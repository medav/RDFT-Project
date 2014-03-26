#include "Game.h"

RDFTENGINE * Engine() {
	return RDFTENGINE::Instance();
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

void Minigame::Draw() {
	switch (MinigameState) {
	case MENU:
		MinigameMenu::Instance()->Draw();
		break;
	case GAME:
		MinigameGame::Instance()->Draw();
		break;
	default:
		break;
	}
}

void Minigame::Resize() {

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

void MinigameMenu::Draw() {
	switch (MenuState) {
	case Minigame::MAIN:
		MainDraw();
		break;
	case Minigame::SETTINGS:
		SettingsDraw();
		break;
	default:
		break;
	}
}

void MinigameMenu::MainDraw() {

}

void MinigameMenu::SettingsDraw() {

}

/************************************************************/

MinigameGame::MinigameGame() {
	Level = 0;
	NewMap();
}

void MinigameGame::Think() {
	switch (GameState) {
	case Minigame::WAITING:
		WaitingThink();
		break;
	case Minigame::RUNNING:
		RunningThink();
		break;
	default:
		break;
	}
}

void MinigameGame::WaitingThink() {
	
}

void MinigameGame::RunningThink() {
	// TODO:
}

void MinigameGame::Draw() {
	switch (GameState) {
	case Minigame::WAITING:
		WaitingDraw();
		break;
	case Minigame::RUNNING:
		RunningDraw();
		break;
	default:
		break;
	}
}

void MinigameGame::WaitingDraw() {

}

void MinigameGame::RunningDraw() {

}

/************************************************************/

void MinigameGame::NewMap() {
	Engine()->GetPhysDevice()->Clear();

}