
#include "Room1.h"
#include "Room2.h"
#include "Consola.h"
#include "BackGround.h"
#include "View.h"
#include "Controller.h"
#include <typeinfo>


void Room2::paintRoom() {
	addEntrance(EAST); // 0�� 
	initObstacles();


	// �Ʒ��� paint. ������ ����ؾ���
	paintBackGround();	// ��� ���

	paintEntrance();	// �Ա� ���

	paintObstacles();	// ��ֹ� ���

	paintCharacter();	// ĳ���� ���(�ݺ��� �� Ű �Է�)
}

// ����ڰ� Ư�� ��ǥ���� space Ű�� ������ ��, ĳ���Ͱ� ��ֹ��� �浹�ߴ��� Ȯ���ϴ� ��ȣ�ۿ� Ȯ�� �Լ�
bool Room2::isImpacted() {
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
	// �Ա��͵� �浹�ߴ��� Ȯ���Ѵ�.
	for (Box b : entranceVector) {
		if (b.getX() <= charX && charX <= b.getX() + b.getWidth() && b.getY() <= charY && charY <= b.getY() + b.getHeight())
			return true;
	}
	return false;
}




// --------------- obstacle --------------- // 
// ��ֹ����� ����ϴ� �Լ�
void Room2::paintObstacles() {
	for (Box b : obstacle) {
		b.paintBox(GREEN);
	}
	textbackground(GREEN);
	textcolor(BLACK);
	View::xyPutStr(BackGround::x + 18, BackGround::y + 6, "����");
	View::xyPutStr(BackGround::x + 18, BackGround::y + 7, "����");
	View::xyPutStr(BackGround::x + 18, BackGround::y + 12, "��");
	View::xyPutStr(BackGround::x + 18, BackGround::y + 13, "����");
}

// ��ֹ��� �ʱ�ȭ �Լ�
void Room2::initObstacles() {
	Box box1(BackGround::x + 18, BackGround::y + 6, 4, 2);
	Box box2(BackGround::x + 18, BackGround::y + 12, 4, 2);

	obstacle[0] = box1;
	obstacle[1] = box2;
}


// ù��° ��ֹ�(����)�� ��ȣ�ۿ����� �� ����� �Լ�
void Room2::eventOneFunc() {
	textbackground(WHITE);
	textcolor(BLACK);
	if (!didGetKey) {
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY - 2, "8 + 7 = 1111");
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY - 1, "100 - 90 = 1010");
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "300 * 0.03 = ?");
		isTextPainted = true;
	}
	else
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "�̹� Ǭ �����Դϴ�.");
}

// �ι�° ��ֹ�(���� ����)�� ��ȣ�ۿ����� �� ����� �Լ�
void Room2::eventTwoFunc() {
	View::clearAllText();
	textbackground(WHITE);
	textcolor(BLACK);
	// �ش� ��ֹ����� Ű�� ���� ���� ���¸� Ű�� ������ ���� ������ �� �ְ� �ؾ��Ѵ�.
	if (!didGetKey) {
		// ������ �ؼ� ���� ���߰� �ȸ��߰� ����
		if (playQuiz()) {
			textbackground(WHITE);
			textcolor(BLACK);
			View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "����! Ű�� ã�ҽ��ϴ�. Ű�� ȹ���Ͻðڽ��ϱ�?");
			// Yes�� No �߿��� ������ ��, ������� �޾ƿ´�.
			bool selected = selectYesNo();
			// enter�� ������ ��, ������ ���ڰ� Yes�� ���
			if (selected) {
				didGetKey = true;	// Ű�� ������� ����
				Model::plusEscapeKey(); // Ż�� Ű ���� ����
			}
		}
		else {
			View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "����! Ű�� ȹ������ ���߽��ϴ�.");
		}
	}
	else {
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "�̹� Ǭ �����Դϴ�.");
	}
	isTextPainted = true;
}


// ������ Ǯ�� ������ �Է¹޴� �Լ�. ������ ���߸� true, �����߸� false ��ȯ
bool Room2::playQuiz() {
	textcolor(BLACK);
	textbackground(WHITE);
	View::xyPutStr(BackGround::textFieldX + 5, BackGround::textFieldY + 1, "_");
	
	textcolor(WHITE);
	textbackground(BLACK);
	View::xyPutStr(BackGround::textFieldX + 7, BackGround::textFieldY + 1, "_");
	View::xyPutStr(BackGround::textFieldX + 9, BackGround::textFieldY + 1, "_");
	View::xyPutStr(BackGround::textFieldX + 11, BackGround::textFieldY + 1, "_");


	// ������ ���� �ߴ��� �ƴ��� Ȯ���ϴ� ����
	bool isSubmitted = false;
	// ���� �ùٸ��� Ȯ���ϴ� ����
	bool isCorrect = true;
	// ���° ĭ�� ���� �ۼ��ϰ� �ִ��� �����ϴ� ����
	int currentBlock = 0;
	// ����ڰ� �Է��� �� �迭
	int answer[4] = { 0,0,0,0 };
	// ���� ����
	int resultAnswer[4] = { 1,0,0,1 };

	int key = 0;
	while (!isSubmitted) {
		key = Controller::getKey();
		switch (key) {
		case ENTERKEY:
			isSubmitted = true; // enter�� ������ ���� ����
			for (int i = 0; i < 4; ++i) {
				if (answer[i] != resultAnswer[i]) {
					isCorrect = false;
					break;
				}
			}
			View::clearAllText();
			break;
		case LEFTKEY:
			// ������ ������ �� ���� ���� ĭ�̸� �������� ����
			if (currentBlock > 0) { 
				textcolor(WHITE);
				textbackground(BLACK);
				View::xyPutC(BackGround::textFieldX + 5 + currentBlock * 2, BackGround::textFieldY + 1, (char)answer[currentBlock] + '0');
				--currentBlock;
				textcolor(BLACK);
				textbackground(WHITE);
				View::xyPutC(BackGround::textFieldX + 5 + currentBlock * 2, BackGround::textFieldY + 1, (char)answer[currentBlock] + '0');
			}
			break;
		case RIGHTKEY:
			// �������� ������ �� ���� ������ ĭ�̸� ���������� ����
			if (currentBlock < 3) {
				textcolor(WHITE);
				textbackground(BLACK);
				View::xyPutC(BackGround::textFieldX + 5 + currentBlock * 2, BackGround::textFieldY + 1, (char)answer[currentBlock] + '0');
				++currentBlock;
				textcolor(BLACK);
				textbackground(WHITE);
				View::xyPutC(BackGround::textFieldX + 5 + currentBlock * 2, BackGround::textFieldY + 1, (char)answer[currentBlock] + '0');
			}
			break;
		default:
			// ���� Ű�� Ÿ���� 0~9������ �����϶��� ����
			if (0x30 <= key && 0x39 >= key) {
				int num = key - (int)'0';
				answer[currentBlock] = num;
				textcolor(BLACK);
				textbackground(WHITE);
				View::xyPutC(BackGround::textFieldX + 5 + currentBlock * 2, BackGround::textFieldY + 1, (char)answer[currentBlock]+'0');
			}
			
		}

	}
	return isCorrect;
}

// ���� ĳ���Ͱ� ��ġ�� ��ֹ��� ��ȯ�ϴ� �Լ�
Box* Room2::getCurrentObstacle() {
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



// -------------- mainCharacter ----------------- //
void Room2::paintCharacter() {
	Character* character = model->getCharacter();

	int key;

	textcolor(BLACK); // ĳ���� ����
	textbackground(WHITE);
	View::xyPutStr(character->getXPos(), character->getYPos(), "!");
	// ���� ĳ���Ͱ� ����ؼ� �ش� �濡 ������ ���̸� �ݺ��� ���.
	while (isInRoom) {
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
				Model::moveCount += 2;
				// ĳ���Ͱ� ��ֹ��� �ε����ٸ�, ���� �ε��� ��ֹ��� ���´�.
				Box* currentObstacle = getCurrentObstacle();
				if (*currentObstacle == obstacle[0]) {
					eventOneFunc();
				}
				else if (*currentObstacle == obstacle[1]) {
					eventTwoFunc();
				}
				else {
					if (*currentObstacle == entranceVector.at(0))
						// �Ա��� ������ ���̶��, Room1���� ���� �̺�Ʈ�� �߻���Ų��.
						eventEastEntranceFunc(1);
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
