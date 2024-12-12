#include "Room7.h"
#include "Consola.h"
#include "BackGround.h"
#include "View.h"
#include "Controller.h"

void Room7::paintRoom() {
	addEntrance(SOUTH);
	initWalls();
	initKeyBox();

	// paint method
	paintBackGround();	// 배경 출력

	paintEntrance();	// 입구 출력

	paintWalls();		// 벽 출력

	paintKeyBox();		// 열쇠상자 출력

	paintCharacter();	// 캐릭터 출력(반복문 및 키 입력)
}



// 사용자가 특정 좌표에서 space 키를 눌렀는지 확인하는 상호작용 확인 함수
bool Room7::isImpacted() {
	// 캐릭터 포인터 획득
	Character* character = model->getCharacter();

	// 캐릭터의 x/y 좌표
	int charX = character->getXPos();
	int charY = character->getYPos();


	// 열쇠상자 충돌 확인
	if (keyBox.getX() <= charX && charX <= keyBox.getX() + keyBox.getWidth() && keyBox.getY() <= charY && charY <= keyBox.getY() + keyBox.getHeight())
		return true;

	// 입구 충돌 확인
	for (Box b : entranceVector) {
		if (b.getX() <= charX && charX <= b.getX() + b.getWidth() && b.getY() <= charY && charY <= b.getY() + b.getHeight())
			return true;
	}
	return false;
}

// ------------ Wall & KeyBox ------------ //
// 벽을 초기화하는 함수
//                ##########
// 
//      ##########          ##########
// 
//                ##########
void Room7::initWalls() {
	Box box1(BackGround::x + 10, BackGround::y + 5,		20, 2);
	Box box2(BackGround::x,		 BackGround::y + 10,	15, 2);
	Box box3(BackGround::x + 25, BackGround::y + 10,	15, 2);
	Box box4(BackGround::x + 10, BackGround::y + 15,	20, 2);

	walls[0] = box1;
	walls[1] = box2;
	walls[2] = box3;
	walls[3] = box4;
}
// 벽을 출력하는 함수
void Room7::paintWalls() {
	for (Box b : walls) {
		b.paintBox(DARKGRAY);
	}
}

// 열쇠상자를 초기화하는 함수
void Room7::initKeyBox() {
	Box tempB(BackGround::x + 16, BackGround::y, 8, 1);
	keyBox = tempB;
}
// 열쇠상자를 출력하는 함수
void Room7::paintKeyBox() {
	keyBox.paintBox(GREEN);
}

// ------------ event Function ------------ // 
// 사용자가 열쇠상자와 상호작용했을 때 실행될 함수
void Room7::eventKeyBoxFunc() {
	textbackground(WHITE);
	textcolor(BLACK);
	// 해당 장애물에서 키를 얻지 않은 상태면
	// eventGameFunc() 실행하여 0이면 Game over / 1이면 열쇠를 얻을지 고를 수 있게 한다.
	if (!didGetKey) {
		if (eventGameFuc()) {
			View::clearAllText();
			textbackground(WHITE);
			textcolor(BLACK);
			View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "키를 찾았습니다. 키를 획득하시겠습니까?");
			// Yes와 No 중에서 선택한 후, 결과값을 받아온다.
			bool selected = selectYesNo();
			// enter를 눌렀을 때, 선택한 문자가 Yes인 경우
			if (selected) {
				didGetKey = true;	// 키를 얻었음을 설정
				Model::plusEscapeKey(); // 탈출 키 개수 증가
			}
		}
		else {
			View::clearAllText();
			textbackground(WHITE);
			textcolor(BLACK);
			View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "올바르게 화살표를 입력해주세요. (힌트: 이동 방법)");
		}
		
	}
	else if(didGetKey) {
		textbackground(WHITE);
		textcolor(BLACK);
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "이미 키를 획득하였습니다.");
	}
	isTextPainted = true;
}

// 열쇠상자와 상호작용 후 호출할 게임을 실행하는 함수
bool Room7::eventGameFuc() {
	textbackground(WHITE);
	textcolor(BLACK);
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "아래에 표시된 화살표를 누르세요.");

	textcolor(BLACK);
	textbackground(WHITE);
	View::xyPutStr(BackGround::textFieldX + 5, BackGround::textFieldY + 1, "→ ↑ ← ↓ → ↓");

	int answer[] = { LEFTKEY, DOWNKEY, RIGHTKEY, UPKEY, LEFTKEY, UPKEY };
	for (int i = 0; i < 6; i++) {
		int key = Controller::getKey();

		if (key == answer[i]) 
			continue;
		else
			return false;
	}
	return true;
}


// 현재 캐릭터가 위치한 장애물을 반환하는 함수
Box* Room7::getCurrentObstacle() {
	// 캐릭터 포인터 획득
	Character* character = model->getCharacter();

	// 캐릭터의 x/y 좌표
	int charX = character->getXPos();
	int charY = character->getYPos();

	// 열쇠상자 반환
	if (keyBox.getX() <= charX && charX <= keyBox.getX() + keyBox.getWidth() && keyBox.getY() <= charY && charY <= keyBox.getY() + keyBox.getHeight())
		return &keyBox;

	// 입구 반환
	for (Box b : entranceVector) {
		if (b.getX() <= charX && charX <= b.getX() + b.getWidth() && b.getY() <= charY && charY <= b.getY() + b.getHeight())
			return &b;
	}
	return nullptr;
}

// 키보드 상하좌우를 반대로 인식하게 처리하는 함수
void Room7::paintCharacter() {
	Character* character = model->getCharacter();
	character->setStartLocation('D');

	int key;

	textcolor(BLACK); // 캐릭터 색상
	textbackground(WHITE);
	View::xyPutStr(character->getXPos(), character->getYPos(), "!");
	// 현재 캐릭터가 계속해서 해당 방에 존재할 것이면 반복문 계속.
	while (isInRoom) {
		paintInterface();
		key = Controller::getKey();
		paintKeyBox();
		// 인터페이스가 출력되는 부분에 텍스트가 출력되어있다면, 해당 부분을 지운다.
		if (isTextPainted) {
			textbackground(BLACK);
			View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "                                                                   ");
			View::xyPutStr(BackGround::textFieldX + 5, BackGround::textFieldY + 1, "\t");
			View::xyPutStr(BackGround::textFieldX + 10, BackGround::textFieldY + 1, "\t");
			isTextPainted = false;
		}

		// 키 이동 위치가 벽이라면 이동 불가 처리(possiveToMove 메소드) & 상하좌우 반대로 처리
		switch (key) {
		case UPKEY:		
			if (possibleToMove(character->getXPos(), character->getYPos() + 1))
				character->moveDown(); 
			break;
		case DOWNKEY:	
			if (possibleToMove(character->getXPos(), character->getYPos() - 1))
				character->moveUp(); 
			break;
		case LEFTKEY:	
			if (possibleToMove(character->getXPos() + 1, character->getYPos()))
				character->moveRight(); 
			break;
		case RIGHTKEY:	
			if (possibleToMove(character->getXPos() - 1, character->getYPos()))
				character->moveLeft(); 
			break;

		case SPACEKEY:
			if (isImpacted()) {
				Model::moveCount += 2;
				Box* currentObstacle = getCurrentObstacle();

				if (*currentObstacle == keyBox) {
					eventKeyBoxFunc();
				}
				else if (*currentObstacle == entranceVector.at(0))
					// 6번 방으로 이동
					eventSouthEntranceFunc(6);
			}
			break;
		}
		if (!isInRoom) continue;

		textbackground(WHITE);
		textcolor(BLACK);
		View::xyPutStr(character->getOldXPos(), character->getOldYPos(), " "); // 잔상 처리
		View::xyPutStr(character->getXPos(), character->getYPos(), "!");
	}
}

// 키가 이동할 위치를 받아서 벽의 위치와 비교 후 이동 가능한지 확인하는 함수
bool Room7::possibleToMove(int futureXPos, int futureYPos) {

	for (Box b : walls) {
		if (b.getX() <= futureXPos && futureXPos < b.getX() + b.getWidth() && b.getY() <= futureYPos && futureYPos < b.getY() + b.getHeight())
			return false;
	}
	return true;
}

