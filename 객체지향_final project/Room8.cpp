#include "Room8.h"
#include "Consola.h"
#include "View.h"
#include "Controller.h"
#include <thread>   
#include <chrono>
#include <string>

void Room8::paintRoom() {
	addEntrance(WEST); // 0��  
	addEntrance(EAST); // 1�� 
	initObstacle();



	// �Ʒ��� paint. ������ ����ؾ���
	paintBackGround();	// ��� ���

	paintEntrance();	// �Ա� ���

	paintObstacle();

	paintCharacter();	// ĳ���� ���(�ݺ��� �� Ű �Է�)
}

// ����ڰ� Ư�� ��ǥ���� space Ű�� ������ ��, ĳ���Ͱ� ��ֹ��� �浹�ߴ��� Ȯ���ϴ� ��ȣ�ۿ� Ȯ�� �Լ�
bool Room8::isImpacted() {
	// ĳ���� ������ ȹ��
	Character* character = model->getCharacter();

	// ĳ������ x/y ��ǥ
	int charX = character->getXPos();
	int charY = character->getYPos();

	if (obstacle.getX() <= charX && charX <= obstacle.getX() + obstacle.getWidth() && obstacle.getY() <= charY && charY <= obstacle.getY() + obstacle.getHeight())
		return true;

	// �Ա��͵� �浹�ߴ��� Ȯ���Ѵ�.
	for (Box b : entranceVector) {
		if (b.getX() <= charX && charX <= b.getX() + b.getWidth() && b.getY() <= charY && charY <= b.getY() + b.getHeight())
			return true;
	}
	return false;
}

void Room8::paintObstacle() {
	obstacle.paintBox(GREEN);

	textbackground(GREEN);
	textcolor(BLACK);
	View::xyPutStr(BackGround::x + 19, BackGround::y + 9, "����");
	View::xyPutStr(BackGround::x + 19, BackGround::y + 10, "����");
	
}

// ��ֹ��� �ʱ�ȭ �Լ�
void Room8::initObstacle() {
	Box box(BackGround::x + 19, BackGround::y + 9, 4, 2);

	obstacle = box;
}

void Room8::eventObstacleFunc() {
	if (!didGetKey) {
		while (remainChance>0) {
			View::clearAllText();
			textbackground(WHITE);
			textcolor(BLACK);
			View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY - 2, "���� ������ �濡�� �� 3���� ��ȣ ���ڵ��� �־����ϴ�.");
			View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY - 1, "���ݱ��� ������ ���� ���ڸ� ������.");
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
					break;
				}
			}
			else {
				textbackground(WHITE);
				textcolor(BLACK);
				View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "����! Ű�� ȹ������ ���߽��ϴ�.");
				std::this_thread::sleep_for(std::chrono::seconds(1));  // 1�� ���� ���
				// ���� ��ȸ �����͸� ���̰� �� �ڿ� ���� �� �۰� ��������
				--remainChance;
				// ���� �۰� ����� �Լ�
				makeRoomSmaller(remainChance);
				std::this_thread::sleep_for(std::chrono::milliseconds(500));  // 0.5�� ���� ���
			}
			isTextPainted = true;
		}
		// ���� ��� ��ȸ�� �����ߴٸ�
		if (remainChance == 0) {
			isInRoom = false;
			View::clearAllText();

			paintEndPage(false);
		}
	}
	else {
		View::clearAllText();
		textbackground(WHITE);
		textcolor(BLACK);
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "�̹� Ǭ �����Դϴ�.");
		isTextPainted = true;
	}
}

void Room8::makeRoomSmaller(int i) {
	// �ѹ� Ʋ���� ���
	if (i == 2)
		walls[0]->paintBox(DARKGRAY);
	else if (i == 1) {
		walls[0]->paintBox(DARKGRAY);
		walls[2]->paintBox(DARKGRAY);
	}
	else if (i == 0){
		for (Box* b : walls)
			b->paintBox(DARKGRAY);
	}
}


// ������ Ǯ�� ������ �Է¹޴� �Լ�. ������ ���߸� true, �����߸� false ��ȯ
bool Room8::playQuiz() {
	textcolor(BLACK);
	textbackground(WHITE);
	View::xyPutC(BackGround::textFieldX + 5, BackGround::textFieldY + 1, '0');

	textcolor(WHITE);
	textbackground(BLACK);
	View::xyPutC(BackGround::textFieldX + 7, BackGround::textFieldY + 1, '?');
	View::xyPutC(BackGround::textFieldX + 9, BackGround::textFieldY + 1, '!');
	View::xyPutC(BackGround::textFieldX + 11, BackGround::textFieldY + 1, 'm');


	// ������ ���� �ߴ��� �ƴ��� Ȯ���ϴ� ����
	bool isSubmitted = false;
	// ���� �ùٸ��� Ȯ���ϴ� ����
	bool isCorrect = true;
	// ���° ĭ�� ���� �ۼ��ϰ� �ִ��� �����ϴ� ����
	int currentBlock = 0;
	// ���� ����
	char resultAnswer = 'm';
	char selectArray[4] = { '0', '?', '!', 'm' };

	int key = 0;
	while (!isSubmitted) {
		key = Controller::getKey();
		switch (key) {
		case ENTERKEY:
			isSubmitted = true; // enter�� ������ ���� ����
			if (selectArray[currentBlock] != resultAnswer)
				isCorrect = false;
			View::clearAllText();
			break;
		case LEFTKEY:
			// ������ ������ �� ���� ���� ĭ�̸� �������� ����
			if (currentBlock > 0) {
				textcolor(WHITE);
				textbackground(BLACK);
				View::xyPutC(BackGround::textFieldX + 5 + currentBlock * 2, BackGround::textFieldY + 1, selectArray[currentBlock]);
				--currentBlock;
				textcolor(BLACK);
				textbackground(WHITE);
				View::xyPutC(BackGround::textFieldX + 5 + currentBlock * 2, BackGround::textFieldY + 1, selectArray[currentBlock]);
			}
			break;
		case RIGHTKEY:
			// �������� ������ �� ���� ������ ĭ�̸� ���������� ����
			if (currentBlock < 3) {
				textcolor(WHITE);
				textbackground(BLACK);
				View::xyPutC(BackGround::textFieldX + 5 + currentBlock * 2, BackGround::textFieldY + 1, selectArray[currentBlock]);
				++currentBlock;
				textcolor(BLACK);
				textbackground(WHITE);
				View::xyPutC(BackGround::textFieldX + 5 + currentBlock * 2, BackGround::textFieldY + 1, selectArray[currentBlock]);
			}
			break;

		}

	}
	return isCorrect;
}

// ���� ���� ��ȣ�ۿ����� �� ����� �Լ� (������ ���� ��)
// Ű�� ��Ҵ��� Ȯ���ؾ� �ϹǷ� �Լ� �������̵� �ؼ� ���
void Room8::eventEastEntranceFunc() {
	textbackground(WHITE);
	textcolor(BLACK);

	// ���� ��� Ű�� ���� ���ߴٸ�, �׳� �Լ� �����Ŵ
	if (Model::escapeKey != 4) {
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "��� Ű�� ���� ���ÿ��� Ż���� �� �ֽ��ϴ�!");
		isTextPainted = true;
		return;
	}

	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "���ÿ��� Ż���Ͻðڽ��ϱ�?");
	// Yes�� No �߿��� ������ ��, ������� �޾ƿ´�.
	bool selected = selectYesNo();
	// enter�� ������ ��, ������ ���ڰ� Yes�� ���
	if (selected) {
		isInRoom = false;
		View::clearAllText();
		// �������̽� â ����
		Box b(BackGround::interfaceFieldX, BackGround::interfaceFieldY, BackGround::width + 1, 1);
		b.paintBox(BLACK);

		paintEndPage(true);
	}
	isTextPainted = true;
}

void Room8::paintEndPage(bool didEscape) {
	int scr_x1 = 0;
	int scr_x2 = BackGround::x + BackGround::width + 5;
	int scr_y1 = 0;
	int scr_y2 = BackGround::y + BackGround::height + 3;

	char level = 0;
	if (Model::moveCount <= 780)
		level = 'S';
	else if (Model::moveCount > 780 && Model::moveCount <= 850)
		level = 'A';
	else if (Model::moveCount > 850 && Model::moveCount <= 950)
		level = 'B';
	else if (Model::moveCount > 950 && Model::moveCount <= 1050)
		level = 'C';
	else if (Model::moveCount > 1050 && Model::moveCount <= 1250)
		level = 'D';
	else 
		level = 'F';


	string point = to_string(Model::moveCount);


	_setcursortype(_NOCURSOR);
	View::fillBox(scr_x1, scr_y1, scr_x2, scr_y2, BLACK);

	textbackground(WHITE);
	textcolor(BLACK);
	if(didEscape)
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY-3, "���� ����. ������ Ż���߽��ϴ�!");
	else
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY - 3, "���� ����. ������ Ż������ ���߽��ϴ�.");
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY+-2, "ȹ�� ���� : ");
	View::xyPutStr(BackGround::textFieldX+10, BackGround::textFieldY-2, point);
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY-1, "��� : ");
	if (!didEscape)
		level = 'F';
	View::xyPutC(BackGround::textFieldX + 5, BackGround::textFieldY - 1, level);
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "������ �����Ͻðڽ��ϱ�?");

	bool selected = selectYesNo();
	// ������ �����Ѵٸ� view�� canfPlayGame�� false�� ����
	if(selected)
		Model::canPlayGame = false;
	// ������ �������� �ʴ´ٸ�, ������ �ٽ� ���۽�Ŵ
	else {
		ParentRoom* room0 = new Room0(model, view);
		ParentRoom* room1 = new Room1(model, view);
		ParentRoom* room2 = new Room2(model, view);
		ParentRoom* room3 = new Room3(model, view);
		ParentRoom* room4 = new Room4(model, view);
		ParentRoom* room5 = new Room5(model, view);
		ParentRoom* room6 = new Room6(model, view);
		ParentRoom* room7 = new Room7(model, view);
		ParentRoom* room8 = new Room8(model, view);
		
		// roomVector�� ���빰�� ���� �����, �ٽ� vector�� ����� �����ؼ� �������
		view->getRoomVector()->clear();

		// ������ ��� ��� ���Ϳ� ������� ����ֱ�
		view->getRoomVector()->push_back(room0);
		view->getRoomVector()->push_back(room1);
		view->getRoomVector()->push_back(room2);
		view->getRoomVector()->push_back(room3);
		view->getRoomVector()->push_back(room4);
		view->getRoomVector()->push_back(room5);
		view->getRoomVector()->push_back(room6);
		view->getRoomVector()->push_back(room7);
		view->getRoomVector()->push_back(room8);

		Model::escapeKey = 0;
		Model::currentRoomNum = 0;
		Model::moveCount = 0;
		Model::canPlayGame = true;
	}
}





// ���� ĳ���Ͱ� ��ġ�� ��ֹ��� ��ȯ�ϴ� �Լ�
Box* Room8::getCurrentObstacle() {
	// ĳ���� ������ ȹ��
	Character* character = model->getCharacter();

	// ĳ������ x/y ��ǥ
	int charX = character->getXPos();
	int charY = character->getYPos();

	if (obstacle.getX() <= charX && charX <= obstacle.getX() + obstacle.getWidth() && obstacle.getY() <= charY && charY <= obstacle.getY() + obstacle.getHeight())
		return &obstacle;

	for (Box b : entranceVector) {
		if (b.getX() <= charX && charX <= b.getX() + b.getWidth() && b.getY() <= charY && charY <= b.getY() + b.getHeight())
			return &b;
	}
	return nullptr;
}



// -------------- mainCharacter ----------------- //
void Room8::paintCharacter() {
	Character* character = model->getCharacter();

	int key;

	textcolor(BLACK); // ĳ���� ����
	textbackground(WHITE);
	View::xyPutStr(character->getXPos(), character->getYPos(), "!");
	// ���� ĳ���Ͱ� ����ؼ� �ش� �濡 ������ ���̸� �ݺ��� ���.
	while (isInRoom) {
		paintInterface();
		makeRoomSmaller(remainChance);

		key = Controller::getKey();

		paintObstacle();

		// �������̽��� ��µǴ� �κп� �ؽ�Ʈ�� ��µǾ��ִٸ�, �ش� �κ��� �����.
		if (isTextPainted) {
			textbackground(BLACK);
			View::clearAllText();
			isTextPainted = false;
		}

		switch (key) {
		case UPKEY:
			if (possibleToMove(character->getXPos(), character->getYPos() - 1))
				character->moveUp();
			break;
		case DOWNKEY:
			if (possibleToMove(character->getXPos(), character->getYPos() + 1))
				character->moveDown();
			break;
		case LEFTKEY:
			if (possibleToMove(character->getXPos() - 1, character->getYPos()))
				character->moveLeft();
			break;
		case RIGHTKEY:
			if (possibleToMove(character->getXPos() + 1, character->getYPos()))
				character->moveRight();
			break;
		case SPACEKEY:
			if (isImpacted()) {
				Model::moveCount += 2;
				// ĳ���Ͱ� ��ֹ��� �ε����ٸ�, ���� �ε��� ��ֹ��� ���´�.
				Box* currentObstacle = getCurrentObstacle();
				if (*currentObstacle == obstacle)
					eventObstacleFunc();
				else if (*currentObstacle == entranceVector.at(0))
					eventWestEntranceFunc(6);
				else if (*currentObstacle == entranceVector.at(1))
					eventEastEntranceFunc();
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

bool Room8::possibleToMove(int futureXPos, int futureYPos) {
	if(remainChance==2)
		if (walls[0]->getX() <= futureXPos && futureXPos < walls[0]->getX() + walls[0]->getWidth() && walls[0]->getY() <= futureYPos && futureYPos < walls[0]->getY() + walls[0]->getHeight())
			return false;
	if (remainChance == 1) {
		if (walls[0]->getX() <= futureXPos && futureXPos < walls[0]->getX() + walls[0]->getWidth() && walls[0]->getY() <= futureYPos && futureYPos < walls[0]->getY() + walls[0]->getHeight())
			return false;
		if (walls[2]->getX() <= futureXPos && futureXPos < walls[2]->getX() + walls[2]->getWidth() && walls[2]->getY() <= futureYPos && futureYPos < walls[2]->getY() + walls[2]->getHeight())
			return false;
	}
	return true;
}
