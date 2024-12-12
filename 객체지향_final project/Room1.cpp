#include "Room1.h"
#include "Consola.h"
#include "BackGround.h"
#include "View.h"
#include "Controller.h"
#include <thread>   
#include <chrono>

void Room1::paintRoom() {
	addEntrance(WEST); // 0��  
	addEntrance(EAST); // 1�� 
	addEntrance(NORTH); // 2��



	// �Ʒ��� paint. ������ ����ؾ���
	paintBackGround();	// ��� ���

	paintEntrance();	// �Ա� ���

	paintCharacter();	// ĳ���� ���(�ݺ��� �� Ű �Է�)
}

void Room1::paintPattern() {
	int pattern[20][20] = {
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//1
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},//5
	  {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},//10
	  {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},//11
	  {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},//15
	  {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}//20
	};

	Box b(BackGround::x, BackGround::y, 2, 1);

	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			if (pattern[i][j] == 1) { // �Ϲ� ��
				b.paintBox(RED);
			}
			b.plusX(2);
		}
		b.setX(BackGround::x);
		b.plusY(1);
	}
}


// ����ڰ� Ư�� ��ǥ���� space Ű�� ������ ��, ĳ���Ͱ� ��ֹ��� �浹�ߴ��� Ȯ���ϴ� ��ȣ�ۿ� Ȯ�� �Լ�
bool Room1::isImpacted() {
	// ĳ���� ������ ȹ��
	Character* character = model->getCharacter();

	// ĳ������ x/y ��ǥ
	int charX = character->getXPos();
	int charY = character->getYPos();


	// �Ա��͵� �浹�ߴ��� Ȯ���Ѵ�.
	for (Box b : entranceVector) {
		if (b.getX() <= charX && charX <= b.getX() + b.getWidth() && b.getY() <= charY && charY <= b.getY() + b.getHeight())
			return true;
	}
	return false;
}

// ���� ���� ��ȣ�ۿ����� �� ����� �Լ�
void Room1::eventNorthEntranceFunc() {
	textbackground(WHITE);
	textcolor(BLACK);
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "������ �̵��Ͻðڽ��ϱ�?");
	// Yes�� No �߿��� ������ ��, ������� �޾ƿ´�.
	bool selected = selectYesNo();
	// enter�� ������ ��, ������ ���ڰ� Yes�� ���
	if (selected) {
		isInRoom = false;
		View::clearAllText();
		Model::changeRoomNum(5);
		// 5������ ���� �� ������ ���ش�.
		view->getRoomVector()->at(5)->setPrevRoom(1);
		view->getRoomVector()->at(5)->setPrevRoom(1);
		view->getRoomVector()->at(5)->setIsInRoom(true);
		model->getCharacter()->setStartLocation('D');
	}
	isTextPainted = true;
}


// ���� ĳ���Ͱ� ��ġ�� ��ֹ��� ��ȯ�ϴ� �Լ�
Box* Room1::getCurrentObstacle() {
	// ĳ���� ������ ȹ��
	Character* character = model->getCharacter();

	// ĳ������ x/y ��ǥ
	int charX = character->getXPos();
	int charY = character->getYPos();

	for (Box b : entranceVector) {
		if (b.getX() <= charX && charX <= b.getX() + b.getWidth() && b.getY() <= charY && charY <= b.getY() + b.getHeight())
			return &b;
	}
	return nullptr;
}

void Room1::paintTutorial() {
	textbackground(WHITE);
	textcolor(BLACK);
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY - 4, "����� ���ݺ��� 4���� ������� ��� �� �̷θ� Ż���ؾ� �մϴ�!");
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY - 3, "�� �濡�� ������ ������ ������, �ش� �������� Ǯ�� ������ ���� ");
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY - 2, "���踦 ��� Ż���ϼ���!");
	std::this_thread::sleep_for(std::chrono::seconds(5));  // 2�� ���� ���
	View::clearAllText();
	playedTutorial = true;
}

// -------------- mainCharacter ----------------- //
void Room1::paintCharacter() {
	Character* character = model->getCharacter();

	int key;
	
	if(!playedTutorial)
		paintTutorial();

	textcolor(BLACK); // ĳ���� ����
	textbackground(WHITE);
	View::xyPutStr(character->getXPos(), character->getYPos(), "!");
	paintPattern();
	// ���� ĳ���Ͱ� ����ؼ� �ش� �濡 ������ ���̸� �ݺ��� ���.
	while (isInRoom) {
		paintInterface();
		key = Controller::getKey();
		// �������̽��� ��µǴ� �κп� �ؽ�Ʈ�� ��µǾ��ִٸ�, �ش� �κ��� �����.
		if (isTextPainted) {
			textbackground(BLACK);
			View::clearAllText();
			isTextPainted = false;
		}
		
		switch (key) {
		case UPKEY:		character->moveUp(); break;
		case DOWNKEY:	character->moveDown(); break;
		case LEFTKEY:	character->moveLeft(); break;
		case RIGHTKEY:	character->moveRight(); break;
		case SPACEKEY:
			if (isImpacted()) {
				Model::moveCount += 2;
				// ĳ���Ͱ� ��ֹ��� �ε����ٸ�, ���� �ε��� ��ֹ��� ���´�.
				Box* currentObstacle = getCurrentObstacle();
				if (*currentObstacle == entranceVector.at(0))
					eventWestEntranceFunc(2);
				else if (*currentObstacle == entranceVector.at(1))
					eventEastEntranceFunc(3);
				else if (*currentObstacle == entranceVector.at(2))
					eventNorthEntranceFunc();	
			}
			break;
		}
		if (!isInRoom) continue;

		paintPattern();

		textbackground(WHITE);
		textcolor(BLACK);
		View::xyPutStr(character->getOldXPos(), character->getOldYPos(), " "); // �ܻ� ó��
		View::xyPutStr(character->getXPos(), character->getYPos(), "!");
	}

}
