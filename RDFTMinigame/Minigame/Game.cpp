//#include <stdio.h>
//#include <string.h>
#include "Game.h"

Minigame * MG() {
	static Minigame * mg = new Minigame();
	return mg;
}


Minigame::Minigame() {
	GameState = Minigame::WAITING;
	Level = 0;
	lmState = 0;

	NewMap();
	NumMoves = 0;
	Engine()->GetGlDevice()->LoadTexture("Ball.bmp", "ball");
	Engine()->GetGlDevice()->LoadTexture("bricks.bmp", "wall");
	Engine()->GetGlDevice()->LoadTexture("space.bmp", "background");
}


void Minigame::Resize() {

}

void Minigame::Think() {
	gameMutex.lock();

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

	gameMutex.unlock();
}

void Minigame::WaitingThink() {
	lmState = Engine()->GetLmDevice()->LMRefresh();

	if (lmState == 2) {
		GLVECTOR2 vec = Engine()->GetLmDevice()->LMGetVector();
		ball->ApplyVelocity(-vec.x / 4, -vec.y / 4);
		SetState(GAMESTATE::RUNNING);
		NumMoves++;
		lmState = 0;
		Engine()->GetLmDevice()->Reset();
	}
}

void Minigame::RunningThink() {
	Engine()->GetPhysDevice()->Think();
	if (ball->isStopped())
		SetState(GAMESTATE::WAITING);
}

void Minigame::Draw() {
	gameMutex.lock();
	Engine()->GetGlDevice()->BeginScene();
	Engine()->GetGlDevice()->DrawTexturedRect(VectorOf(Engine()->ScreenX() / 2, Engine()->ScreenY() / 2), VectorOf(Engine()->ScreenX(), Engine()->ScreenY()), "background");
	//Engine()->GetGlDevice()->DrawTextGl("Level "<<Level);
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

	//Engine()->GetGlDevice()->DrawTextGl(VectorOf(20.0, 20.0), ColorOf(1.0f, 0.0f, 0.0f), "Test!");

	Engine()->GetGlDevice()->EndScene();
	gameMutex.unlock();
}

void Minigame::WaitingDraw() {
	if (lmState) {
		GLVECTOR2 beg = ball->getPos();
		GLVECTOR2 vec = Engine()->GetLmDevice()->LMGetVector();
		vec.x *= -2;
		vec.y *= -2;
		GLVECTOR2 end = VectorOf(beg.x + vec.x, beg.y + vec.y);

		Engine()->GetGlDevice()->DrawArrow(beg, end, 8, ColorOf(0.0f, 1.0f, 0.0f));
	}
	
	Engine()->GetPhysDevice()->Draw(Engine()->GetGlDevice());
	
}

void Minigame::RunningDraw() {
	Engine()->GetPhysDevice()->Draw(Engine()->GetGlDevice());
}

/************************************************************/

void Minigame::NewMap() {
	Engine()->GetPhysDevice()->Clear();

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

	//ENTITY * Obstruction2 = new Wall(VectorOf(700, 200), 50, 300);
	//Engine()->GetPhysDevice()->AddEntity(Obstruction2);

	ball = new Ball(VectorOf(50, 60));

	Engine()->GetPhysDevice()->AddEntity(ball);
}