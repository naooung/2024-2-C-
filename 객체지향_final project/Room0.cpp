#include "Room0.h"
#include "Consola.h"
#include "BackGround.h"
#include "View.h"
#include "Controller.h"

void Room0::paintRoom() {
	addEntrance(NORTH); // 0번 
	initObstacles();


	// 아래는 paint. 순서를 고려해야함
	paintBackGround();	// 배경 출력
	
	paintEntrance();	// 입구 출력
	
	paintObstacles();	// 장애물 출력

	paintCharacter();	// 캐릭터 출력(반복문 및 키 입력)
}

void Room0::paintInterface() {
	Box b(BackGround::interfaceFieldX, BackGround::interfaceFieldY, BackGround::width+1, 1);
	b.paintBox(WHITE);
	textbackground(WHITE);
	textcolor(BLACK);
	View::xyPutStr(BackGround::interfaceFieldX, BackGround::interfaceFieldY, "남은 키의 개수: ");
	View::xyPutC(BackGround::interfaceFieldX + 15, BackGround::interfaceFieldY, Model::escapeKey + '0');
	View::xyPutStr(BackGround::interfaceFieldX + 16, BackGround::interfaceFieldY, " / 1");
}


// 사용자가 특정 좌표에서 space 키를 눌렀을 때, 캐릭터가 장애물과 충돌했는지 확인하는 상호작용 확인 함수
bool Room0::isImpacted() {
	// 캐릭터 포인터 획득
	Character *character = model->getCharacter();

	// 캐릭터의 x/y 좌표
	int charX = character->getXPos();
	int charY = character->getYPos();


	// obstacle 배열의 각 장애물들과 충돌했는지 확인한다.
	for (Box b : obstacle) {
		if (b.getX() <= charX && charX <= b.getX() + b.getWidth() && b.getY() <= charY && charY <= b.getY() + b.getHeight())
			return true;
	}
	// 입구와도 충돌했는지 확인한다.
	for (Box b : entranceVector) {
		if (b.getX() <= charX && charX <= b.getX() + b.getWidth() && b.getY() <= charY && charY <= b.getY() + b.getHeight())
			return true;
	}
	return false;
}




// --------------- obstacle --------------- // 
// 장애물들을 출력하는 함수
void Room0::paintObstacles() {
	for (Box b : obstacle) {
		b.paintBox(GREEN);
	}
}

// 장애물들 초기화 함수
void Room0::initObstacles() {
	Box box1(BackGround::x + 5, BackGround::y + 5, 4, 2);
	Box box2(BackGround::x + 20, BackGround::y + 7, 4, 2);
	Box box3(BackGround::x + 10, BackGround::y + 15, 4, 2);
	obstacle[0] = box1;
	obstacle[1] = box2;
	obstacle[2] = box3;
}


// 첫번째 장애물과 상호작용했을 때 실행될 함수
void Room0::eventOneFunc() {
	textbackground(WHITE);
	textcolor(BLACK);
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "키를 찾지 못했습니다.");
	isTextPainted = true;
}
// 두번째 장애물과 상호작용했을 때 실행될 함수
void Room0::eventTwoFunc() {
	textbackground(WHITE);
	textcolor(BLACK);
	// 해당 장애물에서 키를 얻지 않은 상태면 키를 얻을지 말지 선택할 수 있게 해야한다.
	if (!didGetKey) {
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "키를 찾았습니다. 키를 획득하시겠습니까?");
		// Yes와 No 중에서 선택한 후, 결과값을 받아온다.
		bool selected = selectYesNo();
		// enter를 눌렀을 때, 선택한 문자가 Yes인 경우
		if (selected) {
			didGetKey = true;	// 키를 얻었음을 설정
			Model::escapeKey++;
		}
	}
	else {
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "이미 키를 획득하였습니다.");
	}
	isTextPainted = true;
}
// 세번째 장애물과 상호작용했을 때 실행될 함수
void Room0::eventThreeFunc() {
	textbackground(WHITE);
	textcolor(BLACK);
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "키를 찾지 못했습니다.");
	isTextPainted = true;
}
// 사용자가 입구와 상호작용했을 때 실행될 함수

void Room0::eventNorthEntranceFunc() {
	textbackground(WHITE);
	textcolor(BLACK);
	if (didGetKey) {
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "문을 여시겠습니까?");
		bool selected = selectYesNo(); 
		// Yes를 선택했다면, 이제 Room1으로 이동한다. 아래에 해당 과정을 구현한다.
		if (selected) {
			isInRoom = false;
			View::clearAllText();
			Model::changeRoomNum(1);
			view->getRoomVector()->at(1)->setIsInRoom(true);
			// 튜토리얼 끝났으므로 키 개수 초기화
			Model::escapeKey = 0;
			// 사용자 움직임 점수 초기화
			Model::moveCount = 0;
			model->getCharacter()->setStartLocation('D');
		}
	}
	else {
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "키가 없으면 문을 열 수 없습니다.");
	}
	isTextPainted = true;
}




// 현재 캐릭터가 위치한 장애물을 반환하는 함수
Box* Room0::getCurrentObstacle() {
	// 캐릭터 포인터 획득
	Character* character = model->getCharacter();

	// 캐릭터의 x/y 좌표
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
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY - 4, "\"방향키\"를 이용해서 캐릭터를 움직일 수 있습니다.");
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY - 3, "\"space키\"를 이용해서 장애물이나 입구에 상호작용 할 수 있습니다.");
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY - 2, "장애물 중에서 방을 탈출할 수 있는 열쇠를 찾아서 탈출하세요.");	
}


// -------------- mainCharacter ----------------- //
void Room0::paintCharacter() {
	View::clearAllText();

	Character* character = model->getCharacter();
	character->setStartLocation('D');

	int key;
	textcolor(BLACK); // 캐릭터 색상
	textbackground(WHITE);
	View::xyPutStr(character->getXPos(), character->getYPos(), "!");
	// 현재 캐릭터가 계속해서 해당 방에 존재할 것이면 반복문 계속.
	while (isInRoom) {
		// 키를 찾기 전까지 튜토리얼 출력
		if(!didGetKey)
			paintTutorial();
		paintInterface();
		key = Controller::getKey();
		paintObstacles();
		// 인터페이스가 출력되는 부분에 텍스트가 출력되어있다면, 해당 부분을 지운다.
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
				// 상호작용은 2점이 올라감
				Model::moveCount += 2;
				// 캐릭터가 장애물과 부딪혔다면, 현재 부딪힌 장애물을 얻어온다.
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
							// 입구에 도착한 것이라면, Room1으로 가는 이벤트를 발생시킨다.
							eventNorthEntranceFunc();
					}
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
