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
	paintBackGround();	// 배경 출력

	paintEntrance();	// 입구 출력

	paintWall();		// 벽 출력

	paintKeyBox();		// 열쇠상자 출력

	paintCharacter();	// 캐릭터 출력(반복문 및 키 입력)
}

// 사용자가 특정 좌표에서 space 키를 눌렀을 때, 캐릭터가 열쇠상자/입구와 충돌했는지 확인하는 상호작용 확인 함수
bool Room4::isImpacted() {
	// 캐릭터 포인터 획득
	Character *character = model->getCharacter();

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
// 미로 벽을 초기화하는 함수
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

// 미로 벽을 출력하는 함수
void Room4::paintWall() {
	Box b(BackGround::x, BackGround::y, 2, 1);

	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			if (wall[i][j] == 1) { // 일반 벽
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

// 열쇠상자를 초기화하는 함수
void Room4::initKeyBox() {
	keyBox.setX(BackGround::x + 38);
	keyBox.setY(BackGround::y + 9);
	keyBox.setWidth(2);
	keyBox.setHeight(2);
}

// 열쇠상자를 출력하는 함수
void Room4::paintKeyBox() {
	keyBox.paintBox(GREEN);
}

// ------------ event Function ------------ // 
// 사용자가 열쇠상자와 상호작용했을 때 실행될 함수
void Room4::eventKeyBoxFunc() {
	textbackground(WHITE);
	textcolor(BLACK);

	// 해당 장애물에서 키를 얻지 않은 상태면 키를 얻을지 말지 선택할 수 있게 해야한다.
	// !!!!!View에 필요한 키를 저장하는 변수 escapeKey, 메소드 plusEscapeKey() 추가 -> model로 해야하나?!!!!!
	if (!didGetKey) {
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
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "이미 키를 획득하였습니다.");
	}
	isTextPainted = true;
}

// 현재 캐릭터가 위치한 입구를 반환하는 함수
Box* Room4::getCurrentObstacle() {
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

void Room4::paintCharacter() {
	// !!!!!Character.h에 스폰 위치를 결정하는 메소드 추가!!!!! -> 방 전환할 때 고려해서 수정 필요
	Character* character = model->getCharacter();

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

		// 현재 위치를 2차원 배열 wall 인덱스에 맞게 변환
		int mazeX = (character->getXPos() - BackGround::x) / 2;
		int mazeY = (character->getYPos() - BackGround::y);


		// 벽이면 이동 불가 처리
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

				// 캐릭터가 열쇠상자와 부딪혔다면, 열쇠상자 이벤트 발생
				if (*currentObstacle == keyBox) {
					eventKeyBoxFunc();
				}
				else {
					if (*currentObstacle == entranceVector.at(0))
						// 입구에 도착한 것이라면, Room3으로 가는 이벤트를 발생시킨다.
						eventWestEntranceFunc(3);
				}
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