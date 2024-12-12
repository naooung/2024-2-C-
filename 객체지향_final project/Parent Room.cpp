#include "Parent Room.h"
#include "Consola.h"
#include "BackGround.h"
#include "View.h"
#include "Controller.h"


void ParentRoom::paintInterface() {
	Box b(BackGround::interfaceFieldX, BackGround::interfaceFieldY, BackGround::width+1, 1);
	b.paintBox(WHITE);
	textbackground(WHITE);
	textcolor(BLACK);
	View::xyPutStr(BackGround::interfaceFieldX, BackGround::interfaceFieldY, "���� Ű�� ����: ");
	View::xyPutC(BackGround::interfaceFieldX + 15, BackGround::interfaceFieldY, Model::escapeKey+'0');
	View::xyPutStr(BackGround::interfaceFieldX + 16, BackGround::interfaceFieldY, " / 4");
}


void ParentRoom::eventNorthEntranceFunc(int roomNum) {
	textbackground(WHITE);
	textcolor(BLACK);
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "������ �̵��Ͻðڽ��ϱ�?");
	// Yes�� No �߿��� ������ ��, ������� �޾ƿ´�.
	bool selected = selectYesNo();
	// enter�� ������ ��, ������ ���ڰ� Yes�� ���
	if (selected) {
		isInRoom = false;
		View::clearAllText();
		Model::changeRoomNum(roomNum);
		view->getRoomVector()->at(roomNum)->setIsInRoom(true);
		model->getCharacter()->setStartLocation('D');
	}
	isTextPainted = true;
}

void ParentRoom::eventSouthEntranceFunc(int roomNum){
	textbackground(WHITE);
	textcolor(BLACK);
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "������ �̵��Ͻðڽ��ϱ�?");
	// Yes�� No �߿��� ������ ��, ������� �޾ƿ´�.
	bool selected = selectYesNo();
	// enter�� ������ ��, ������ ���ڰ� Yes�� ���
	if (selected) {
		isInRoom = false;
		View::clearAllText();
		Model::changeRoomNum(roomNum);
		view->getRoomVector()->at(roomNum)->setIsInRoom(true);
		model->getCharacter()->setStartLocation('U');
	}
	isTextPainted = true;
}
void ParentRoom::eventWestEntranceFunc(int roomNum)	{
	textbackground(WHITE);
	textcolor(BLACK);
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "������ �̵��Ͻðڽ��ϱ�?");
	// Yes�� No �߿��� ������ ��, ������� �޾ƿ´�.
	bool selected = selectYesNo();
	// enter�� ������ ��, ������ ���ڰ� Yes�� ���
	if (selected) {
		isInRoom = false;
		View::clearAllText();
		Model::changeRoomNum(roomNum);
		view->getRoomVector()->at(roomNum)->setIsInRoom(true);
		model->getCharacter()->setStartLocation('R');
	}
	isTextPainted = true;
}

void ParentRoom::eventEastEntranceFunc(int roomNum) {
	textbackground(WHITE);
	textcolor(BLACK);
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "������ �̵��Ͻðڽ��ϱ�?");
	// Yes�� No �߿��� ������ ��, ������� �޾ƿ´�.
	bool selected = selectYesNo();
	// enter�� ������ ��, ������ ���ڰ� Yes�� ���
	if (selected) {
		isInRoom = false;
		View::clearAllText();
		Model::changeRoomNum(roomNum);
		view->getRoomVector()->at(roomNum)->setIsInRoom(true);
		model->getCharacter()->setStartLocation('L');
	}
	isTextPainted = true;
}



void ParentRoom::setIsInRoom(bool value) {
	isInRoom = value;
}

void ParentRoom::addEntrance(int direction) {
	// ��� ���(����ڰ� ������ ����) ��ǥ�� ������
	int x = 0;
	int y = 0;
	int width = 0; // �Ա��� ��
	int height = 0; // �Ա��� ����

	switch (direction) {
	case NORTH:
		width = 10;
		height = 1;
		x = BackGround::x + 15;
		y = BackGround::y - height; // 1�� �Ϻη� ���̳��� ũ�⸦ �����ؼ�, ĳ���Ͱ� �Ա��� �浹�� �� �ְ� �Ѵ�.
		break;
	case SOUTH:
		width = 10;
		height = 2;
		x += BackGround::x + 15;
		y += BackGround::y + BackGround::height;
		break;
	case WEST:
		width = 2;
		height = 5;
		x = BackGround::x - width;
		y = BackGround::y + 7;
		break;
	case EAST:
		width = 4;
		height = 5;
		x = BackGround::x + BackGround::width-1;
		y = BackGround::y + 7;
		break;
	}
	Box box(x, y, width, height);

	// iterator�� ����Ͽ� �ش� �迭�� �Ա��� �̹� �ִ��� Ȯ���Ѵ�.
	vector<Box>::iterator iter = find(entranceVector.begin(), entranceVector.end(), box);
	if (iter == entranceVector.end()) { // �ش� �迭�� �Ա��� ������ �Ա� �߰�
		entranceVector.push_back(box);
	}
}
void ParentRoom::paintEntrance() {
	_setcursortype(_NOCURSOR);
	for (Box entrance : entranceVector) {
		entrance.paintBox(WHITE);
	}
}	


void ParentRoom::paintBackGround() {
	int scr_x1 = BackGround::x;
	int scr_x2 = BackGround::x + BackGround::width;
	int scr_y1 = BackGround::y;
	int scr_y2 = BackGround::y + BackGround::height+1;

	
	_setcursortype(_NOCURSOR);
	View::fillBox(scr_x1 - 4, scr_y1-4, scr_x2 + 4, scr_y2+4, BLACK);
	View::fillBox(scr_x1, scr_y1, scr_x2, scr_y2, WHITE);
}


void ParentRoom::paintCharacter() {
	Character* character = model->getCharacter();

	int key;

	textcolor(BLACK); // ĳ���� ����
	textbackground(WHITE);
	while ((key = Controller::getKey()) != 'q') {
		switch (key) {
		case UPKEY:		character->moveUp(); break;
		case DOWNKEY:	character->moveDown(); break;
		case LEFTKEY:	character->moveLeft(); break;
		case RIGHTKEY:	character->moveRight(); break;
		}

		if (character->getOldXPos() != character->getXPos() || character->getOldYPos() != character->getYPos()) {
			View::xyPutStr(character->getOldXPos(), character->getOldYPos(), "  "); // �ܻ� ó��
			View::xyPutStr(character->getXPos(), character->getYPos(), "��");
		}
	}
}

bool ParentRoom::selectYesNo() {
	// �⺻ ������ Yes�� �����ϵ��� �д�.
	textcolor(BLACK);
	textbackground(WHITE);
	View::xyPutStr(BackGround::textFieldX + 5, BackGround::textFieldY + 1, "Yes");
	textcolor(WHITE);
	textbackground(BLACK);
	View::xyPutStr(BackGround::textFieldX + 10, BackGround::textFieldY + 1, "No");

	// Yes�� No�� 1���� �ߴ��� �ƴ��� Ȯ���ϴ� ����
	bool isSelected = false;
	// ���� �����Ѱ� ���� ��� �ִ� ���� (Yes�� 1, No�� 0)
	bool selected = true;

	int key = 0;
	while (!isSelected) {
		key = Controller::getKey();
		switch (key) {
		case ENTERKEY:
			isSelected = true; // enter�� ������ ���� ����
			// ���� ���� ���� Yes�� No�� �����ش�.
			textbackground(BLACK);
			View::xyPutStr(BackGround::textFieldX + 5, BackGround::textFieldY + 1, "   ");
			View::xyPutStr(BackGround::textFieldX + 10, BackGround::textFieldY + 1, "   ");
			break;
		case LEFTKEY:
			// ������ Yes�� �Ǿ������� ���� Ű�� ������ ������ �������� �ʴ´�.
			if (!selected) { // No�� ���õǾ�������
				selected = true; // Yes�� �������ְ�, 
				textcolor(BLACK);
				textbackground(WHITE);
				View::xyPutStr(BackGround::textFieldX + 5, BackGround::textFieldY + 1, "Yes");
				textcolor(WHITE);
				textbackground(BLACK);
				View::xyPutStr(BackGround::textFieldX + 10, BackGround::textFieldY + 1, "No");
			}
			break;
		case RIGHTKEY:
			// ������ No�� �Ǿ������� ������ Ű�� ������ ������ �������� �ʴ´�.
			if (selected) { // Yes�� ���õǾ�������
				selected = false; // No�� �������ְ�, 
				textcolor(WHITE);
				textbackground(BLACK);
				View::xyPutStr(BackGround::textFieldX + 5, BackGround::textFieldY + 1, "Yes");
				textcolor(BLACK);
				textbackground(WHITE);
				View::xyPutStr(BackGround::textFieldX + 10, BackGround::textFieldY + 1, "No");
			}
			break;
		}

	}
	return selected;
}