#include "Room4.h"
#include "Consola.h"
#include "BackGround.h"
#include "View.h"
#include "Controller.h"

void Room4::paintRoom() {
	addEntrance(WEST);	
	initWall();
	initKeyBox();

	// paint method
	paintBackGround();	// ��� ���

	paintEntrance();	// �Ա� ���

	paintWall();		// �� ���

	paintKeyBox();		// ������� ���

	paintCharacter();	// ĳ���� ���(�ݺ��� �� Ű �Է�)
}

// ����ڰ� Ư�� ��ǥ���� space Ű�� ������ ��, ĳ���Ͱ� �������/�Ա��� �浹�ߴ��� Ȯ���ϴ� ��ȣ�ۿ� Ȯ�� �Լ�
bool Room4::isImpacted() {
	// ĳ���� ������ ȹ��
	Character *character = model->getCharacter();

	// ĳ������ x/y ��ǥ
	int charX = character->getXPos();
	int charY = character->getYPos();


	// ������� �浹 Ȯ��
	if (keyBox.getX() <= charX && charX <= keyBox.getX() + keyBox.getWidth() && keyBox.getY() <= charY && charY <= keyBox.getY() + keyBox.getHeight())
			return true;

	// �Ա� �浹 Ȯ��
	for (Box b : entranceVector) {
		if (b.getX() <= charX && charX <= b.getX() + b.getWidth() && b.getY() <= charY && charY <= b.getY() + b.getHeight())
			return true;
	}
	return false;
}

// ------------ Wall & KeyBox ------------ //
// �̷� ���� �ʱ�ȭ�ϴ� �Լ�
void Room4::initWall() {
	int tempWall[20][20] = {
	  {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//1
	  {0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0},
	  {0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
	  {0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	  {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},//5
	  {0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0},
	  {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1},
	  {0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0},
	  {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0},
	  {0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0},//10
	  {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0},//11
	  {0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
	  {0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0},
	  {0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	  {0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},//15
	  {0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
	  {0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0},
	  {0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0},
	  {0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0},
	  {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0} //20
	};

	for (int i = 0; i < 20; ++i)
		for (int j = 0; j < 20; ++j)
			wall[i][j] = tempWall[i][j];
}

// �̷� ���� ����ϴ� �Լ�
void Room4::paintWall() {
	Box b(BackGround::x, BackGround::y, 2, 1);

	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			if (wall[i][j] == 1) { // �Ϲ� ��
				b.paintBox(DARKGRAY);
			}
			else {
				b.paintBox(WHITE);
			}
			b.plusX(2);
		}
		b.setX(BackGround::x);
		b.plusY(1);
	}
}

// ������ڸ� �ʱ�ȭ�ϴ� �Լ�
void Room4::initKeyBox() {
	keyBox.setX(BackGround::x + 38);
	keyBox.setY(BackGround::y + 9);
	keyBox.setWidth(2);
	keyBox.setHeight(2);
}

// ������ڸ� ����ϴ� �Լ�
void Room4::paintKeyBox() {
	keyBox.paintBox(GREEN);
}

// ------------ event Function ------------ // 
// ����ڰ� ������ڿ� ��ȣ�ۿ����� �� ����� �Լ�
void Room4::eventKeyBoxFunc() {
	textbackground(WHITE);
	textcolor(BLACK);

	// �ش� ��ֹ����� Ű�� ���� ���� ���¸� Ű�� ������ ���� ������ �� �ְ� �ؾ��Ѵ�.
	// !!!!!View�� �ʿ��� Ű�� �����ϴ� ���� escapeKey, �޼ҵ� plusEscapeKey() �߰� -> model�� �ؾ��ϳ�?!!!!!
	if (!didGetKey) {
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "Ű�� ã�ҽ��ϴ�. Ű�� ȹ���Ͻðڽ��ϱ�?");
		// Yes�� No �߿��� ������ ��, ������� �޾ƿ´�.
		bool selected = selectYesNo();
		// enter�� ������ ��, ������ ���ڰ� Yes�� ���
		if (selected) {
			didGetKey = true;	// Ű�� ������� ����
			Model::plusEscapeKey(); // Ż�� Ű ���� ����
		}
	}
	else {
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "�̹� Ű�� ȹ���Ͽ����ϴ�.");
	}
	isTextPainted = true;
}

// ���� ĳ���Ͱ� ��ġ�� �Ա��� ��ȯ�ϴ� �Լ�
Box* Room4::getCurrentObstacle() {
	// ĳ���� ������ ȹ��
	Character* character = model->getCharacter();

	// ĳ������ x/y ��ǥ
	int charX = character->getXPos();
	int charY = character->getYPos();

	// ������� ��ȯ
	if (keyBox.getX() <= charX && charX <= keyBox.getX() + keyBox.getWidth() && keyBox.getY() <= charY && charY <= keyBox.getY() + keyBox.getHeight())
		return &keyBox;

	// �Ա� ��ȯ
	for (Box b : entranceVector) {
		if (b.getX() <= charX && charX <= b.getX() + b.getWidth() && b.getY() <= charY && charY <= b.getY() + b.getHeight())
			return &b;
	}
	return nullptr;
}

void Room4::paintCharacter() {
	// !!!!!Character.h�� ���� ��ġ�� �����ϴ� �޼ҵ� �߰�!!!!! -> �� ��ȯ�� �� ����ؼ� ���� �ʿ�
	Character* character = model->getCharacter();

	int key;

	textcolor(BLACK); // ĳ���� ����
	textbackground(WHITE);
	View::xyPutStr(character->getXPos(), character->getYPos(), "!");
	// ���� ĳ���Ͱ� ����ؼ� �ش� �濡 ������ ���̸� �ݺ��� ���.
	while (isInRoom) {
		paintInterface();
		key = Controller::getKey();
		paintKeyBox();
		// �������̽��� ��µǴ� �κп� �ؽ�Ʈ�� ��µǾ��ִٸ�, �ش� �κ��� �����.
		if (isTextPainted) {
			textbackground(BLACK);
			View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "                                                                   ");
			View::xyPutStr(BackGround::textFieldX + 5, BackGround::textFieldY + 1, "\t");
			View::xyPutStr(BackGround::textFieldX + 10, BackGround::textFieldY + 1, "\t");
			isTextPainted = false;
		}

		// ���� ��ġ�� 2���� �迭 wall �ε����� �°� ��ȯ
		int mazeX = (character->getXPos() - BackGround::x) / 2;
		int mazeY = (character->getYPos() - BackGround::y);


		// ���̸� �̵� �Ұ� ó��
		switch (key) {
		case UPKEY:
			if (wall[mazeY - 1][mazeX] == 0) {
				character->moveUp();
			}
			break;
		case DOWNKEY:
			if (wall[mazeY + 1][mazeX] == 0) {
				character->moveDown();
			}
			break;
		case LEFTKEY:
			if (wall[mazeY][mazeX - 1] == 0) {
				character->moveLeft();
			}
			break;
		case RIGHTKEY:
			if (wall[mazeY][mazeX + 1] == 0) {
				character->moveRight();
			}
			break;
		case SPACEKEY:
			if (isImpacted()) {
				Model::moveCount += 2;
				Box* currentObstacle = getCurrentObstacle();

				// ĳ���Ͱ� ������ڿ� �ε����ٸ�, ������� �̺�Ʈ �߻�
				if (*currentObstacle == keyBox) {
					eventKeyBoxFunc();
				}
				else {
					if (*currentObstacle == entranceVector.at(0))
						// �Ա��� ������ ���̶��, Room3���� ���� �̺�Ʈ�� �߻���Ų��.
						eventWestEntranceFunc(3);
				}
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