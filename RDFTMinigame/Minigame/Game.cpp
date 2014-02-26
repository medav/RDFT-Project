#include "Game.h"

RDFTENGINE * Engine() {
	static RDFTENGINE rdft;
	return &rdft;
}