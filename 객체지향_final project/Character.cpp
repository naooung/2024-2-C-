#include "Character.h"
#include "BackGround.h"

void Character::moveUp() {
	int y1 = BackGround::y;
	if (ypos  > y1) {
		oldxpos = xpos;
		oldypos = ypos;
		--ypos;
		++Model::moveCount;
	}
}
void Character::moveDown() {
	int y2 = BackGround::y + BackGround::height;
	if (ypos  < y2) {
		oldxpos = xpos;
		oldypos = ypos;
		++ypos;
		++Model::moveCount;
	}
}
void Character::moveLeft() {
	int x1 = BackGround::x;
	if (xpos > x1) {
		oldxpos = xpos;
		oldypos = ypos;
		--xpos;
		++Model::moveCount;
	}
}
void Character::moveRight() {
	int x2 = BackGround::x + BackGround::width;
	if (xpos + 1 < x2) {
		oldxpos = xpos;
		oldypos = ypos;
		++xpos;
		++Model::moveCount;
	}
}


