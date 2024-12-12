#include "Room5.h"
#include "Consola.h"
#include "BackGround.h"
#include "View.h"
#include "Controller.h"

void Room5::paintRoom() {
	addEntrance(NORTH); // 0번 
	addEntrance(SOUTH); // 0번 
	initObstacles();
	initPath();

	// 아래는 paint. 순서를 고려해야함
	paintBackGround();	// 배경 출력

	paintEntrance();	// 입구 출력

	paintPath(DARKGRAY); // 길 출력

	paintObstacles(GREEN);	// 장애물 출력

	paintCharacter();	// 캐릭터 출력(반복문 및 키 입력)
}

// 사용자가 특정 좌표에서 space 키를 눌렀을 때, 캐릭터가 장애물과 충돌했는지 확인하는 상호작용 확인 함수
bool Room5::isImpacted() {
	// 캐릭터 포인터 획득
	Character* character = model->getCharacter();

	// 캐릭터의 x/y 좌표
	int charX = character->getXPos();
	int charY = character->getYPos();


	// obstacle 배열의 각 장애물들과 충돌했는지 확인한다.
	for (Box b : obstacle) {
		if (b.getX() <= charX && charX <= b.getX() + b.getWidth() && b.getY() <= charY && charY <= b.getY() + b.getHeight())
			return true;
	}

	// path 배열의 각 길과 충돌했는지 확인한다.
	for (Box b : path) {
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
void Room5::paintObstacles(char color) {
	for (Box b : obstacle) {
		b.paintBox(color);
	}
}

// 장애물들 초기화 함수
void Room5::initObstacles() {
	Box box1(BackGround::x + 3, BackGround::y + 10, 3, 2);
	Box box2(BackGround::x + 26, BackGround::y + 3, 3, 2);
	obstacle[0] = box1;
	obstacle[1] = box2;
}


// --------------- path --------------- // 
// 길을 출력하는 함수
void Room5::paintPath(char color) {
	for (Box b : path) {
		b.paintBox(color);
	}
}

// 장애물들 초기화 함수
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



// 첫번째 장애물과 상호작용했을 때 실행될 함수
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



// 현재 캐릭터가 위치한 장애물을 반환하는 함수
Box* Room5::getCurrentObstacle() {
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

	textcolor(BLACK); // 캐릭터 색상
	textbackground(WHITE);
	View::xyPutStr(character->getXPos(), character->getYPos(), "!");
	// 현재 캐릭터가 계속해서 해당 방에 존재할 것이면 반복문 계속.
	while (isInRoom) {
		paintInterface();
		key = Controller::getKey();

		// 인터페이스가 출력되는 부분에 텍스트가 출력되어있다면, 해당 부분을 지운다.
		if (isTextPainted) {
			textbackground(BLACK);
			View::clearAllText();
			isTextPainted = false;
		}

		// 충돌하지 않았다는 것은 길을 벗어났다는 것.
		if (isImpacted()) {
			// 캐릭터가 장애물과 부딪혔다면, 현재 부딪힌 장애물을 얻어온다.
			Box* currentObstacle = getCurrentObstacle();
			
			if (*currentObstacle == obstacle[0] || *currentObstacle == obstacle[1]) {
				eventObstacleFunc();
			}
			// 현재 부딪힌 객체가 장애물이 아니면 길이 안보임
			else {
				paintPath(WHITE);
				paintObstacles(WHITE);
			}
		}
		else
			// 길을 벗어나면 이전 방으로 돌아간다.
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
					// 입구에 도착한 것이라면, Room6으로 가는 이벤트를 발생시킨다.
					eventNorthEntranceFunc(6);
				else if (*currentObstacle == entranceVector.at(1))
					// 입구에 도착한 것이라면, Room1으로 가는 이벤트를 발생시킨다.
					eventSouthEntranceFunc(1);
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
