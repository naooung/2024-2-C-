#include "Model.h"
#include "BackGround.h"

int Model::escapeKey = 0;
int Model::currentRoomNum = 0;
int Model::moveCount = 0;
bool Model::canPlayGame = true;

void Model::plusEscapeKey() {
	escapeKey++;
}

void Model::changeRoomNum(int roomNum) {
	currentRoomNum = roomNum;
}
void Model::changeCanPlayGame(bool value) {
	canPlayGame = value;
}