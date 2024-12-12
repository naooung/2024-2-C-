#include "Room5.h"
#include "Consola.h"
#include "BackGround.h"
#include "View.h"
#include "Controller.h"

void Room5::paintRoom() {
	addEntrance(NORTH); // 0�� 
	addEntrance(SOUTH); // 0�� 
	initObstacles();
	initPath();

	// �Ʒ��� paint. ������ ����ؾ���
	paintBackGround();	// ��� ���

	paintEntrance();	// �Ա� ���

	paintPath(DARKGRAY); // �� ���

	paintObstacles(GREEN);	// ��ֹ� ���

	paintCharacter();	// ĳ���� ���(�ݺ��� �� Ű �Է�)
}

// ����ڰ� Ư�� ��ǥ���� space Ű�� ������ ��, ĳ���Ͱ� ��ֹ��� �浹�ߴ��� Ȯ���ϴ� ��ȣ�ۿ� Ȯ�� �Լ�
bool Room5::isImpacted() {
	// ĳ���� ������ ȹ��
	Character* character = model->getCharacter();

	// ĳ������ x/y ��ǥ
	int charX = character->getXPos();
	int charY = character->getYPos();


	// obstacle �迭�� �� ��ֹ���� �浹�ߴ��� Ȯ���Ѵ�.
	for (Box b : obstacle) {
		if (b.getX() <= charX && charX <= b.getX() + b.getWidth() && b.getY() <= charY && charY <= b.getY() + b.getHeight())
			return true;
	}

	// path �迭�� �� ��� �浹�ߴ��� Ȯ���Ѵ�.
	for (Box b : path) {
		if (b.getX() <= charX && charX <= b.getX() + b.getWidth() && b.getY() <= charY && charY <= b.getY() + b.getHeight())
			return true;
	}

	// �Ա��͵� �浹�ߴ��� Ȯ���Ѵ�.
	for (Box b : entranceVector) {
		if (b.getX() <= charX && charX <= b.getX() + b.getWidth() && b.getY() <= charY && charY <= b.getY() + b.getHeight())
			return true;
	}
	return false;
}




// --------------- obstacle --------------- // 
// ��ֹ����� ����ϴ� �Լ�
void Room5::paintObstacles(char color) {
	for (Box b : obstacle) {
		b.paintBox(color);
	}
}

// ��ֹ��� �ʱ�ȭ �Լ�
void Room5::initObstacles() {
	Box box1(BackGround::x + 3, BackGround::y + 10, 3, 2);
	Box box2(BackGround::x + 26, BackGround::y + 3, 3, 2);
	obstacle[0] = box1;
	obstacle[1] = box2;
}


// --------------- path --------------- // 
// ���� ����ϴ� �Լ�
void Room5::paintPath(char color) {
	for (Box b : path) {
		b.paintBox(color);
	}
}

// ��ֹ��� �ʱ�ȭ �Լ�
void Room5::initPath() {
	Box box1(BackGround::x + 19, BackGround::y + 10, 3, 10);
	Box box2(BackGround::x + 3, BackGround::y + 10, 16, 2);
	Box box3(BackGround::x + 3, BackGround::y + 3, 3, 7);
	Box box4(BackGround::x + 6, BackGround::y + 3, 20, 2);
	Box box5(BackGround::x + 26, BackGround::y + 3, 3, 10);
	Box box6(BackGround::x + 29, BackGround::y + 11, 5, 2);
	Box box7(BackGround::x + 33, BackGround::y, 3, 13);
	Box box8(BackGround::x + 15, BackGround::y, 18, 2);

	path[0] = box1;
	path[1] = box2;
	path[2] = box3;
	path[3] = box4;
	path[4] = box5;
	path[5] = box6;
	path[6] = box7;
	path[7] = box8;
}



// ù��° ��ֹ��� ��ȣ�ۿ����� �� ����� �Լ�
void Room5::eventObstacleFunc() {
	paintPath(DARKGRAY);
	paintObstacles(GREEN);
}

void Room5::eventGoBackPrevRoom() {
	isInRoom = false;
	View::clearAllText();
	Model::changeRoomNum(prevRoom);
	view->getRoomVector()->at(prevRoom)->setIsInRoom(true);
	if(prevRoom == 1)
		model->getCharacter()->setStartLocation('U');
	else if(prevRoom == 6)
		model->getCharacter()->setStartLocation('D');
}



// ���� ĳ���Ͱ� ��ġ�� ��ֹ��� ��ȯ�ϴ� �Լ�
Box* Room5::getCurrentObstacle() {
	// ĳ���� ������ ȹ��
	Character* character = model->getCharacter();

	// ĳ������ x/y ��ǥ
	int charX = character->getXPos();
	int charY = character->getYPos();

	for (Box b : obstacle) {
		if (b.getX() <= charX && charX <= b.getX() + b.getWidth() && b.getY() <= charY && charY <= b.getY() + b.getHeight())
			return &b;
	}
	
	for (Box b : entranceVector) {
		if (b.getX() <= charX && charX <= b.getX() + b.getWidth() && b.getY() <= charY && charY <= b.getY() + b.getHeight())
			return &b;
	}
	for (Box b : path) {
		if (b.getX() <= charX && charX <= b.getX() + b.getWidth() && b.getY() <= charY && charY <= b.getY() + b.getHeight())
			return &b;
	}
	return nullptr;
}



// -------------- mainCharacter ----------------- //
void Room5::paintCharacter() {
	Character* character = model->getCharacter();

	int key;

	textcolor(BLACK); // ĳ���� ����
	textbackground(WHITE);
	View::xyPutStr(character->getXPos(), character->getYPos(), "!");
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

		// �浹���� �ʾҴٴ� ���� ���� ����ٴ� ��.
		if (isImpacted()) {
			// ĳ���Ͱ� ��ֹ��� �ε����ٸ�, ���� �ε��� ��ֹ��� ���´�.
			Box* currentObstacle = getCurrentObstacle();
			
			if (*currentObstacle == obstacle[0] || *currentObstacle == obstacle[1]) {
				eventObstacleFunc();
			}
			// ���� �ε��� ��ü�� ��ֹ��� �ƴϸ� ���� �Ⱥ���
			else {
				paintPath(WHITE);
				paintObstacles(WHITE);
			}
		}
		else
			// ���� ����� ���� ������ ���ư���.
			eventGoBackPrevRoom();


		switch (key) {
		case UPKEY:		character->moveUp(); break;
		case DOWNKEY:	character->moveDown(); break;
		case LEFTKEY:	character->moveLeft(); break;
		case RIGHTKEY:	character->moveRight(); break;
		case SPACEKEY:
			if (isImpacted()) {
				Model::moveCount += 2;
				Box* currentObstacle = getCurrentObstacle();
				if (*currentObstacle == entranceVector.at(0))
					// �Ա��� ������ ���̶��, Room6���� ���� �̺�Ʈ�� �߻���Ų��.
					eventNorthEntranceFunc(6);
				else if (*currentObstacle == entranceVector.at(1))
					// �Ա��� ������ ���̶��, Room1���� ���� �̺�Ʈ�� �߻���Ų��.
					eventSouthEntranceFunc(1);
			}			
			break;
		}
		if (!isInRoom) continue;

		textbackground(WHITE);
		textcolor(BLACK);
		View::xyPutStr(character->getOldXPos(), character->getOldYPos(), " "); // �ܻ� ó��
		View::xyPutStr(character->getXPos(), character->getYPos(), "!");
	}

}
