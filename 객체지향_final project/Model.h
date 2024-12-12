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
	// ������� �ൿ(�̵� �Ÿ�, ��ȣ�ۿ�) ������ �������Ѽ� ���� ���� ������ �ݿ�
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
