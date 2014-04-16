//#include <stdio.h>
//#include <string.h>
#include <math.h>
#include "Game.h"
#include <iostream>

Minigame * MG() {
	static Minigame * mg = new Minigame();
	return mg;
}

void SetupEnv();

Minigame::Minigame() {
	GameState = Minigame::WAITING;
	Level = 0;
	lmState = 0;
	Difficulty = 1;

	SetupEnv();
	NewMap();

	Engine()->GetGlDevice()->LoadTexture("Ball.bmp", "ball");
	Engine()->GetGlDevice()->LoadTexture("wall.bmp", "wall");
	Engine()->GetGlDevice()->LoadTexture("space.bmp", "background");
}

void SetEnv(const char * name, const char * value) {
	ENVVAR * ev = new ENVVAR;
	strcpy(ev->value, value);

	ev->numset = false;
	ev->boolset = false;

	Engine()->SetEnv(name, ev);
}

void SetupEnv() {
	SetEnv("friction", ".03");
	SetEnv("ball_tex", "ball");
	SetEnv("bg_tex", "background");
	SetEnv("time_mul", "1");
}


void Minigame::Resize() {
	this->NewMap();
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

	char buffer[200];
	sprintf(buffer, "Difficulty : %d    |    Move : %d    |    Level : %d", Difficulty, NumMoves, Level);
	Engine()->GetGlDevice()->DrawTextGl(VectorOf(Engine()->ScreenX() - 300, 6), ColorOf(0.0f, 0.0f, 0.0f), buffer);

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
	if (NumMoves > 0)
		Difficulty++;

	NumMoves = 0;

	Engine()->GetPhysDevice()->Clear();

	ENTITY * WorldTop = new Wall(VectorOf(Engine()->ScreenX() / 2.0, Engine()->ScreenY() - 4), Engine()->ScreenX() + 8, 16);
	ENTITY * WorldBottom = new Wall(VectorOf(Engine()->ScreenX() / 2.0, 4), Engine()->ScreenX() + 8, 32);
	ENTITY * WorldLeft = new Wall(VectorOf(4, Engine()->ScreenY() / 2.0), 16, Engine()->ScreenY() + 8);
	ENTITY * WorldRight = new Wall(VectorOf(Engine()->ScreenX() - 4, Engine()->ScreenY() / 2.0), 16, Engine()->ScreenY() + 8);

	Engine()->GetPhysDevice()->AddEntity(WorldTop);
	Engine()->GetPhysDevice()->AddEntity(WorldBottom);
	Engine()->GetPhysDevice()->AddEntity(WorldLeft);
	Engine()->GetPhysDevice()->AddEntity(WorldRight);

	int i;

	ENTITY * Obstruction;
	
	for (i = 0; i < Difficulty; i++) {
		BoxX = rand() % (int)Engine()->ScreenX;
		BoxY = rand() % (int)Engine()->ScreenY;
		if (BoxX > Boundry && BoxY > Boundry || BoxX < Engine()->ScreenX - Boundry && BoxY < Engine()->ScreenY - Boundry){
			Obstruction = new Wall(VectorOf(rand() % (int)Engine()->ScreenX(), rand() % (int)Engine()->ScreenY()), sqrt(BoxSize), sqrt(BoxSize));
			Engine()->GetPhysDevice()->AddEntity(Obstruction);
		}
		else i--;
	}

	ball = new Ball(VectorOf(50, 80));
	Engine()->GetPhysDevice()->AddEntity(ball);
}