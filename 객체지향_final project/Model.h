#pragma once
#include <iostream>
#include "Character.h"


using namespace std;

class Model {
private:
	Character *character;

public:
	static int escapeKey;
	static int currentRoomNum;
	// 사용자의 행동(이동 거리, 상호작용) 점수를 증가시켜서 최종 게임 점수에 반영
	static int moveCount;
	static bool canPlayGame;

public:
	Model() {
		character = new Character();
	}
	~Model() {
		delete character;
	}


	Character* getCharacter() {
		return character;
	}


	static void plusEscapeKey();

	static void changeRoomNum(int roomNum);
	static void changeCanPlayGame(bool value);

};
