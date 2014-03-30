//#include <stdio.h>
//#include <string.h>
#include "Game.h"


RDFTENGINE * Engine() {
	static RDFTENGINE * rdft = new RDFTENGINE();
	return rdft;
}

Minigame * MG() {
	static Minigame * mg = new Minigame();
	return mg;
}

MinigameMenu * MGM() {
	static MinigameMenu * mgm = new MinigameMenu();
	return mgm;
}

MinigameGame * MGG() {
	static MinigameGame * mgg = new MinigameGame();
	return mgg;
}

Minigame::Minigame() {
	MinigameState = GAME;
}

void Minigame::Think() {
	switch (MinigameState) {
	case MENU:
		MGM()->Think();
		break;
	case GAME:
		MGG()->Think();
		break;
	default:
		break;
	}
}

void Minigame::Draw() {
	switch (MinigameState) {
	case MENU:
		MGM()->Draw();
		break;
	case GAME:
		MGG()->Draw();
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
	GameState = Minigame::RUNNING;
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
	//Engine()->GetLmDevice()->LMRefresh();
	Engine()->GetPhysDevice()->Think();
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
	Engine()->GetGlDevice()->BeginScene();
	Engine()->GetPhysDevice()->Draw(Engine()->GetGlDevice());
	Engine()->GetGlDevice()->EndScene();
}

/************************************************************/

void MinigameGame::NewMap() {
	Engine()->GetPhysDevice()->Clear();

	//char buffer[500];
	//sprintf_s(buffer, "Screen height = %lf\nScreen width = %lf", Engine()->ScreenY(), Engine()->ScreenX());

	//MessageBox(NULL, buffer, "Engine Info", MB_ICONINFORMATION | MB_OK);

	ENTITY * WorldTop = new Wall(VectorOf(Engine()->ScreenX() / 2.0, Engine()->ScreenY() - 4), Engine()->ScreenX() + 8, 16);
	ENTITY * WorldBottom = new Wall(VectorOf(Engine()->ScreenX() / 2.0, 4), Engine()->ScreenX() + 8, 16);
	ENTITY * WorldLeft = new Wall(VectorOf(4, Engine()->ScreenY() / 2.0), 16, Engine()->ScreenY() + 8);
	ENTITY * WorldRight = new Wall(VectorOf(Engine()->ScreenX() - 4, Engine()->ScreenY() / 2.0), 16, Engine()->ScreenY() + 8);

	Engine()->GetPhysDevice()->AddEntity(WorldTop);
	Engine()->GetPhysDevice()->AddEntity(WorldBottom);
	Engine()->GetPhysDevice()->AddEntity(WorldLeft);
	Engine()->GetPhysDevice()->AddEntity(WorldRight);

	ENTITY * Obstruction1 = new Wall(VectorOf(500, 400), 600, 50);
	Engine()->GetPhysDevice()->AddEntity(Obstruction1);

	ENTITY * Obstruction2 = new Wall(VectorOf(700, 200), 50, 300);
	Engine()->GetPhysDevice()->AddEntity(Obstruction2);

	Ball * ball = new Ball(VectorOf(50, 600));
	ball->ApplyVelocity(10, 2);


	Engine()->GetPhysDevice()->AddEntity(ball);

}