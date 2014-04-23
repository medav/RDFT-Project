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

	SetupEnv();
	NewMap();

	// Load default textures
	Engine()->GetGlDevice()->LoadTexture("ball.bmp", "ball");
	Engine()->GetGlDevice()->LoadTexture("hole.bmp", "hole");
	Engine()->GetGlDevice()->LoadTexture("wall.bmp", "wall");
	Engine()->GetGlDevice()->LoadTexture("you_suck.bmp", "you_suck");
	Engine()->GetGlDevice()->LoadTexture("you_rock.bmp", "you_rock");
	Engine()->GetGlDevice()->LoadTexture("background.bmp", "background");
}

void Minigame::NewGame() {
	GameState = Minigame::WAITING;
	Level = 0;
	lmState = 0;

	SetupEnv();
	NewMap();
}

// Helper function to set an environment variable to a value
void SetEnv(const char * name, const char * value) {
	ENVVAR * ev = new ENVVAR;
	strcpy(ev->value, value);

	ev->numset = false;
	ev->boolset = false;

	Engine()->SetEnv(name, ev);
}

// Helper function to set an environment variable to a value
void SetEnv(const char * name, double value) {
	ENVVAR * ev = new ENVVAR;
	sprintf(ev->value, "%lf", value);
	ev->asDouble = value;

	ev->numset = true;
	ev->boolset = false;

	Engine()->SetEnv(name, ev);
}

// Set up the default env values
void SetupEnv() {
	SetEnv("friction", "0.03");
	SetEnv("cc", "0.95");
	SetEnv("ball_tex", "ball");
	SetEnv("bg_tex", "background");
	SetEnv("wall_tex", "wall");
	SetEnv("hole_tex", "hole");
	SetEnv("time_mul", "0.25");
	SetEnv("boundary", "200");
	SetEnv("boxsize", "100");
	SetEnv("difficulty", "1");
}


void Minigame::Resize() {
	// We make a new map on window resize because
	// It would be all weird otherwise
	this->NewMap();
}

void Minigame::Think() {

	switch (GameState) {
	case Minigame::WAITING:
		WaitingThink();
		break;
	case Minigame::RUNNING:
		RunningThink();
		break;
	case Minigame::WINNING:
		WinningThink();
		break;
	default:
		break;
	}

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

	if (hole->HasBallCollided()) {
		Engine()->GetLmDevice()->Reset();
		SetState(GAMESTATE::WINNING);
	}
}

void Minigame::WinningThink() {
	lmState = Engine()->GetLmDevice()->LMRefresh();

	if (lmState == 2) {
		NewMap();
		SetState(GAMESTATE::WAITING);
		Engine()->GetLmDevice()->Reset();
	}
}

void Minigame::Draw() {
	Engine()->GetGlDevice()->BeginScene();
	Engine()->GetGlDevice()->DrawTexturedRect(VectorOf(Engine()->ScreenX() / 2, Engine()->ScreenY() / 2), VectorOf(Engine()->ScreenX(), Engine()->ScreenY()), Engine()->GetString("bg_tex"));
	switch (GameState) {
	case Minigame::WAITING:
		WaitingDraw();
		break;
	case Minigame::RUNNING:
		RunningDraw();
		break;
	case Minigame::WINNING:
		WinningDraw();
		break;
	default:
		break;
	}

	char buffer[200];
	sprintf(buffer, "Difficulty : %d    |    Move : %d    |    Level : %d", Engine()->GetInt("difficulty") , NumMoves, Level);
	Engine()->GetGlDevice()->DrawTextGl(VectorOf(Engine()->ScreenX() - 300, 6), ColorOf(0.0f, 0.0f, 0.0f), buffer);

	Engine()->GetGlDevice()->EndScene();
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

void Minigame::WinningDraw() {
	Engine()->GetPhysDevice()->Draw(Engine()->GetGlDevice());

	if (NumMoves <= (int) log2(Engine()->GetInt("difficulty") + 2) )
		Engine()->GetGlDevice()->DrawTexturedRect(VectorOf(Engine()->ScreenX() / 2, Engine()->ScreenY() / 2), 
												  VectorOf(Engine()->ScreenX() * 0.7, Engine()->ScreenY() * 0.7), "you_rock");
	else
		Engine()->GetGlDevice()->DrawTexturedRect(VectorOf(Engine()->ScreenX() / 2, Engine()->ScreenY() / 2), 
												  VectorOf(Engine()->ScreenX() * 0.7, Engine()->ScreenY() * 0.7), "you_suck");
}

/************************************************************/

void Minigame::NewMap() {
	if (NumMoves > 0) {
		SetEnv("difficulty", Engine()->GetInt("difficulty") + rand() % 3 + 1);
		SetEnv("boxsize", 100 - Engine()->GetInt("difficulty"));
		Level++;
	}
	
	int Difficulty = Engine()->GetInt("difficulty");



	NumMoves = 0;

	double Boundary = Engine()->GetDouble("boundary");
	double BoxX, BoxY;
	double BoxSize = Engine()->GetDouble("boxsize");

	Engine()->GetPhysDevice()->Clear();

	// The world!
	ENTITY * WorldTop = new Wall(VectorOf(Engine()->ScreenX() / 2.0, Engine()->ScreenY() + 16), Engine()->ScreenX() + 8, 64);
	ENTITY * WorldBottom = new Wall(VectorOf(Engine()->ScreenX() / 2.0, - 8), Engine()->ScreenX() + 8, 64);
	ENTITY * WorldLeft = new Wall(VectorOf(-16, Engine()->ScreenY() / 2.0), 64, Engine()->ScreenY() + 8);
	ENTITY * WorldRight = new Wall(VectorOf(Engine()->ScreenX() + 16, Engine()->ScreenY() / 2.0), 64, Engine()->ScreenY() + 8);

	Engine()->GetPhysDevice()->AddEntity(WorldTop);
	Engine()->GetPhysDevice()->AddEntity(WorldBottom);
	Engine()->GetPhysDevice()->AddEntity(WorldLeft);
	Engine()->GetPhysDevice()->AddEntity(WorldRight);

	int i;

	ENTITY * Obstruction;
	
	for (i = 0; i < Difficulty; i++) {
		BoxX = rand() % (int)Engine()->ScreenX();
		BoxY = rand() % (int)Engine()->ScreenY();

		if ((BoxX > Boundary || BoxY > Boundary) &&
			(BoxX < Engine()->ScreenX() - Boundary || BoxY < Engine()->ScreenY() - Boundary)) {
			Obstruction = new Wall(VectorOf(BoxX, BoxY), BoxSize, BoxSize);
			Engine()->GetPhysDevice()->AddEntity(Obstruction);
		}
		else 
			i--;
	}

	hole = new Hole(VectorOf(Engine()->ScreenX() - 100, Engine()->ScreenY() - 100));
	Engine()->GetPhysDevice()->AddEntity(hole);

	ball = new Ball(VectorOf(50, 80));
	Engine()->GetPhysDevice()->AddEntity(ball);
}