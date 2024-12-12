#include "Room0.h"
#include "Consola.h"
#include "BackGround.h"
#include "View.h"
#include "Controller.h"

void Room0::paintRoom() {
	addEntrance(NORTH); // 0�� 
	initObstacles();


	// �Ʒ��� paint. ������ ����ؾ���
	paintBackGround();	// ��� ���
	
	paintEntrance();	// �Ա� ���
	
	paintObstacles();	// ��ֹ� ���

	paintCharacter();	// ĳ���� ���(�ݺ��� �� Ű �Է�)
}

void Room0::paintInterface() {
	Box b(BackGround::interfaceFieldX, BackGround::interfaceFieldY, BackGround::width+1, 1);
	b.paintBox(WHITE);
	textbackground(WHITE);
	textcolor(BLACK);
	View::xyPutStr(BackGround::interfaceFieldX, BackGround::interfaceFieldY, "���� Ű�� ����: ");
	View::xyPutC(BackGround::interfaceFieldX + 15, BackGround::interfaceFieldY, Model::escapeKey + '0');
	View::xyPutStr(BackGround::interfaceFieldX + 16, BackGround::interfaceFieldY, " / 1");
}


// ����ڰ� Ư�� ��ǥ���� space Ű�� ������ ��, ĳ���Ͱ� ��ֹ��� �浹�ߴ��� Ȯ���ϴ� ��ȣ�ۿ� Ȯ�� �Լ�
bool Room0::isImpacted() {
	// ĳ���� ������ ȹ��
	Character *character = model->getCharacter();

	// ĳ������ x/y ��ǥ
	int charX = character->getXPos();
	int charY = character->getYPos();


	// obstacle �迭�� �� ��ֹ���� �浹�ߴ��� Ȯ���Ѵ�.
	for (Box b : obstacle) {
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
void Room0::paintObstacles() {
	for (Box b : obstacle) {
		b.paintBox(GREEN);
	}
}

// ��ֹ��� �ʱ�ȭ �Լ�
void Room0::initObstacles() {
	Box box1(BackGround::x + 5, BackGround::y + 5, 4, 2);
	Box box2(BackGround::x + 20, BackGround::y + 7, 4, 2);
	Box box3(BackGround::x + 10, BackGround::y + 15, 4, 2);
	obstacle[0] = box1;
	obstacle[1] = box2;
	obstacle[2] = box3;
}


// ù��° ��ֹ��� ��ȣ�ۿ����� �� ����� �Լ�
void Room0::eventOneFunc() {
	textbackground(WHITE);
	textcolor(BLACK);
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "Ű�� ã�� ���߽��ϴ�.");
	isTextPainted = true;
}
// �ι�° ��ֹ��� ��ȣ�ۿ����� �� ����� �Լ�
void Room0::eventTwoFunc() {
	textbackground(WHITE);
	textcolor(BLACK);
	// �ش� ��ֹ����� Ű�� ���� ���� ���¸� Ű�� ������ ���� ������ �� �ְ� �ؾ��Ѵ�.
	if (!didGetKey) {
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "Ű�� ã�ҽ��ϴ�. Ű�� ȹ���Ͻðڽ��ϱ�?");
		// Yes�� No �߿��� ������ ��, ������� �޾ƿ´�.
		bool selected = selectYesNo();
		// enter�� ������ ��, ������ ���ڰ� Yes�� ���
		if (selected) {
			didGetKey = true;	// Ű�� ������� ����
			Model::escapeKey++;
		}
	}
	else {
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "�̹� Ű�� ȹ���Ͽ����ϴ�.");
	}
	isTextPainted = true;
}
// ����° ��ֹ��� ��ȣ�ۿ����� �� ����� �Լ�
void Room0::eventThreeFunc() {
	textbackground(WHITE);
	textcolor(BLACK);
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "Ű�� ã�� ���߽��ϴ�.");
	isTextPainted = true;
}
// ����ڰ� �Ա��� ��ȣ�ۿ����� �� ����� �Լ�

void Room0::eventNorthEntranceFunc() {
	textbackground(WHITE);
	textcolor(BLACK);
	if (didGetKey) {
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "���� ���ðڽ��ϱ�?");
		bool selected = selectYesNo(); 
		// Yes�� �����ߴٸ�, ���� Room1���� �̵��Ѵ�. �Ʒ��� �ش� ������ �����Ѵ�.
		if (selected) {
			isInRoom = false;
			View::clearAllText();
			Model::changeRoomNum(1);
			view->getRoomVector()->at(1)->setIsInRoom(true);
			// Ʃ�丮�� �������Ƿ� Ű ���� �ʱ�ȭ
			Model::escapeKey = 0;
			// ����� ������ ���� �ʱ�ȭ
			Model::moveCount = 0;
			model->getCharacter()->setStartLocation('D');
		}
	}
	else {
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "Ű�� ������ ���� �� �� �����ϴ�.");
	}
	isTextPainted = true;
}




// ���� ĳ���Ͱ� ��ġ�� ��ֹ��� ��ȯ�ϴ� �Լ�
Box* Room0::getCurrentObstacle() {
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
	return nullptr;
}

void Room0::paintTutorial() {
	textbackground(WHITE);
	textcolor(BLACK);
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY - 4, "\"����Ű\"�� �̿��ؼ� ĳ���͸� ������ �� �ֽ��ϴ�.");
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY - 3, "\"spaceŰ\"�� �̿��ؼ� ��ֹ��̳� �Ա��� ��ȣ�ۿ� �� �� �ֽ��ϴ�.");
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY - 2, "��ֹ� �߿��� ���� Ż���� �� �ִ� ���踦 ã�Ƽ� Ż���ϼ���.");	
}


// -------------- mainCharacter ----------------- //
void Room0::paintCharacter() {
	View::clearAllText();

	Character* character = model->getCharacter();
	character->setStartLocation('D');

	int key;
	textcolor(BLACK); // ĳ���� ����
	textbackground(WHITE);
	View::xyPutStr(character->getXPos(), character->getYPos(), "!");
	// ���� ĳ���Ͱ� ����ؼ� �ش� �濡 ������ ���̸� �ݺ��� ���.
	while (isInRoom) {
		// Ű�� ã�� ������ Ʃ�丮�� ���
		if(!didGetKey)
			paintTutorial();
		paintInterface();
		key = Controller::getKey();
		paintObstacles();
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
				// ��ȣ�ۿ��� 2���� �ö�
				Model::moveCount += 2;
				// ĳ���Ͱ� ��ֹ��� �ε����ٸ�, ���� �ε��� ��ֹ��� ���´�.
				Box* currentObstacle = getCurrentObstacle();
				if (*currentObstacle == obstacle[0]) {
					eventOneFunc();
				}
				else if (*currentObstacle == obstacle[1]) {
					eventTwoFunc();
				}
				else if (*currentObstacle == obstacle[2]) {
					eventThreeFunc();
				}
				else {
					for (int i = 0; i < entranceVector.size(); ++i) {
						if (*currentObstacle == entranceVector.at(i))
							// �Ա��� ������ ���̶��, Room1���� ���� �̺�Ʈ�� �߻���Ų��.
							eventNorthEntranceFunc();
					}
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
