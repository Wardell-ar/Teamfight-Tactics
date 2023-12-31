#include "myPosition.h"

myPosition::myPosition() {
	x = y = -1;
	state = 0;
}

myPosition::myPosition(int xx, int yy) {
	x = xx;
	y = yy;
	state = 0;
}

void myPosition::Setsprite() {
	state = 1;
}

void myPosition::Removesprite() {
	state = 0;
}

bool myPosition::IsEmpty() {
	return state == 0;
}

void myPosition::operator=(myPosition p) {
	x = p.x;
	y = p.y;
	state = p.state;
}

