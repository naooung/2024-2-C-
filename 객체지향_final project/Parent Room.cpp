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
	View::xyPutStr(BackGround::interfaceFieldX, BackGround::interfaceFieldY, "남은 키의 개수: ");
	View::xyPutC(BackGround::interfaceFieldX + 15, BackGround::interfaceFieldY, Model::escapeKey+'0');
	View::xyPutStr(BackGround::interfaceFieldX + 16, BackGround::interfaceFieldY, " / 4");
}


void ParentRoom::eventNorthEntranceFunc(int roomNum) {
	textbackground(WHITE);
	textcolor(BLACK);
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "방으로 이동하시겠습니까?");
	// Yes와 No 중에서 선택한 후, 결과값을 받아온다.
	bool selected = selectYesNo();
	// enter를 눌렀을 때, 선택한 문자가 Yes인 경우
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
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "방으로 이동하시겠습니까?");
	// Yes와 No 중에서 선택한 후, 결과값을 받아온다.
	bool selected = selectYesNo();
	// enter를 눌렀을 때, 선택한 문자가 Yes인 경우
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
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "방으로 이동하시겠습니까?");
	// Yes와 No 중에서 선택한 후, 결과값을 받아온다.
	bool selected = selectYesNo();
	// enter를 눌렀을 때, 선택한 문자가 Yes인 경우
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
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "방으로 이동하시겠습니까?");
	// Yes와 No 중에서 선택한 후, 결과값을 받아온다.
	bool selected = selectYesNo();
	// enter를 눌렀을 때, 선택한 문자가 Yes인 경우
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
	// 흰색 배경(사용자가 움직일 공간) 좌표값 가져옴
	int x = 0;
	int y = 0;
	int width = 0; // 입구의 폭
	int height = 0; // 입구의 높이

	switch (direction) {
	case NORTH:
		width = 10;
		height = 1;
		x = BackGround::x + 15;
		y = BackGround::y - height; // 1씩 일부러 차이나게 크기를 설정해서, 캐릭터가 입구에 충돌할 수 있게 한다.
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

	// iterator를 사용하여 해당 배열에 입구가 이미 있는지 확인한다.
	vector<Box>::iterator iter = find(entranceVector.begin(), entranceVector.end(), box);
	if (iter == entranceVector.end()) { // 해당 배열에 입구가 없으면 입구 추가
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

	textcolor(BLACK); // 캐릭터 색상
	textbackground(WHITE);
	while ((key = Controller::getKey()) != 'q') {
		switch (key) {
		case UPKEY:		character->moveUp(); break;
		case DOWNKEY:	character->moveDown(); break;
		case LEFTKEY:	character->moveLeft(); break;
		case RIGHTKEY:	character->moveRight(); break;
		}

		if (character->getOldXPos() != character->getXPos() || character->getOldYPos() != character->getYPos()) {
			View::xyPutStr(character->getOldXPos(), character->getOldYPos(), "  "); // 잔상 처리
			View::xyPutStr(character->getXPos(), character->getYPos(), "ㅁ");
		}
	}
}

bool ParentRoom::selectYesNo() {
	// 기본 설정을 Yes를 선택하도록 둔다.
	textcolor(BLACK);
	textbackground(WHITE);
	View::xyPutStr(BackGround::textFieldX + 5, BackGround::textFieldY + 1, "Yes");
	textcolor(WHITE);
	textbackground(BLACK);
	View::xyPutStr(BackGround::textFieldX + 10, BackGround::textFieldY + 1, "No");

	// Yes나 No를 1선택 했는지 아닌지 확인하는 변수
	bool isSelected = false;
	// 현재 선택한게 뭔지 담고 있는 변수 (Yes면 1, No면 0)
	bool selected = true;

	int key = 0;
	while (!isSelected) {
		key = Controller::getKey();
		switch (key) {
		case ENTERKEY:
			isSelected = true; // enter를 누르면 선택 종료
			// 선택 종료 전에 Yes와 No를 지워준다.
			textbackground(BLACK);
			View::xyPutStr(BackGround::textFieldX + 5, BackGround::textFieldY + 1, "   ");
			View::xyPutStr(BackGround::textFieldX + 10, BackGround::textFieldY + 1, "   ");
			break;
		case LEFTKEY:
			// 선택이 Yes에 되어있으면 왼쪽 키를 눌러도 선택이 움직이지 않는다.
			if (!selected) { // No가 선택되어있으면
				selected = true; // Yes로 움직여주고, 
				textcolor(BLACK);
				textbackground(WHITE);
				View::xyPutStr(BackGround::textFieldX + 5, BackGround::textFieldY + 1, "Yes");
				textcolor(WHITE);
				textbackground(BLACK);
				View::xyPutStr(BackGround::textFieldX + 10, BackGround::textFieldY + 1, "No");
			}
			break;
		case RIGHTKEY:
			// 선택이 No에 되어있으면 오른쪽 키를 눌러도 선택이 움직이지 않는다.
			if (selected) { // Yes가 선택되어있으면
				selected = false; // No로 움직여주고, 
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