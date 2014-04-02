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


Minigame::Minigame() {
	GameState = Minigame::RUNNING;
	Level = 0;

	NewMap();

	Engine()->GetGlDevice()->LoadTexture("Ball.bmp", "ball");
	Engine()->GetGlDevice()->LoadTexture("bricks.bmp", "wall");
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
	if (Engine()->GetLmDevice()->LMRefresh()) {
		GLVECTOR2 vec = Engine()->GetLmDevice()->LMGetVector();
		ball->ApplyVelocity(vec.x / 16, vec.y / 16);
	}
}

void Minigame::RunningThink() {
	
	if (Engine()->GetLmDevice()->LMRefresh()) {
		GLVECTOR2 vec = Engine()->GetLmDevice()->LMGetVector();
		ball->ApplyVelocity(vec.x / 16, vec.y / 16);
	}
	Engine()->GetPhysDevice()->Think();
}

void Minigame::Draw() {
	gameMutex.lock();

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

	gameMutex.unlock();
}

void Minigame::WaitingDraw() {
	Engine()->GetGlDevice()->BeginScene();

	GLVECTOR2 beg = ball->getPos();
	GLVECTOR2 vec = Engine()->GetLmDevice()->LMGetVector();
	GLVECTOR2 end = VectorOf(beg.x + vec.x, beg.y + vec.y);

	Engine()->GetGlDevice()->DrawArrow(beg, end, 8, ColorOf(0.0f, 1.0f, 0.0f));
	Engine()->GetPhysDevice()->Draw(Engine()->GetGlDevice());

	Engine()->GetGlDevice()->EndScene();
}

void Minigame::RunningDraw() {
	Engine()->GetGlDevice()->BeginScene();
	
	GLVECTOR2 beg = ball->getPos();
	GLVECTOR2 vec = Engine()->GetLmDevice()->LMGetVector();
	GLVECTOR2 end = VectorOf(beg.x + vec.x, beg.y + vec.y);

	Engine()->GetGlDevice()->DrawArrow(beg, end, 8, ColorOf(0.0f, 1.0f, 0.0f));
	Engine()->GetPhysDevice()->Draw(Engine()->GetGlDevice());
	
	Engine()->GetGlDevice()->EndScene();
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

	ENTITY * Obstruction2 = new Wall(VectorOf(700, 200), 50, 300);
	Engine()->GetPhysDevice()->AddEntity(Obstruction2);

	ball = new Ball(VectorOf(50, 60));
	ball->ApplyVelocity(80, 20);

	Engine()->GetPhysDevice()->AddEntity(ball);
}