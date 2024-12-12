
#include "Room1.h"
#include "Room2.h"
#include "Consola.h"
#include "BackGround.h"
#include "View.h"
#include "Controller.h"
#include <typeinfo>


void Room2::paintRoom() {
	addEntrance(EAST); // 0번 
	initObstacles();


	// 아래는 paint. 순서를 고려해야함
	paintBackGround();	// 배경 출력

	paintEntrance();	// 입구 출력

	paintObstacles();	// 장애물 출력

	paintCharacter();	// 캐릭터 출력(반복문 및 키 입력)
}

// 사용자가 특정 좌표에서 space 키를 눌렀을 때, 캐릭터가 장애물과 충돌했는지 확인하는 상호작용 확인 함수
bool Room2::isImpacted() {
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
	// 입구와도 충돌했는지 확인한다.
	for (Box b : entranceVector) {
		if (b.getX() <= charX && charX <= b.getX() + b.getWidth() && b.getY() <= charY && charY <= b.getY() + b.getHeight())
			return true;
	}
	return false;
}




// --------------- obstacle --------------- // 
// 장애물들을 출력하는 함수
void Room2::paintObstacles() {
	for (Box b : obstacle) {
		b.paintBox(GREEN);
	}
	textbackground(GREEN);
	textcolor(BLACK);
	View::xyPutStr(BackGround::x + 18, BackGround::y + 6, "문제");
	View::xyPutStr(BackGround::x + 18, BackGround::y + 7, "보기");
	View::xyPutStr(BackGround::x + 18, BackGround::y + 12, "답");
	View::xyPutStr(BackGround::x + 18, BackGround::y + 13, "제출");
}

// 장애물들 초기화 함수
void Room2::initObstacles() {
	Box box1(BackGround::x + 18, BackGround::y + 6, 4, 2);
	Box box2(BackGround::x + 18, BackGround::y + 12, 4, 2);

	obstacle[0] = box1;
	obstacle[1] = box2;
}


// 첫번째 장애물(문제)과 상호작용했을 때 실행될 함수
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
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "이미 푼 문제입니다.");
}

// 두번째 장애물(정답 제출)과 상호작용했을 때 실행될 함수
void Room2::eventTwoFunc() {
	View::clearAllText();
	textbackground(WHITE);
	textcolor(BLACK);
	// 해당 장애물에서 키를 얻지 않은 상태면 키를 얻을지 말지 선택할 수 있게 해야한다.
	if (!didGetKey) {
		// 게임을 해서 답을 맞추고 안맞추고를 구분
		if (playQuiz()) {
			textbackground(WHITE);
			textcolor(BLACK);
			View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "정답! 키를 찾았습니다. 키를 획득하시겠습니까?");
			// Yes와 No 중에서 선택한 후, 결과값을 받아온다.
			bool selected = selectYesNo();
			// enter를 눌렀을 때, 선택한 문자가 Yes인 경우
			if (selected) {
				didGetKey = true;	// 키를 얻었음을 설정
				Model::plusEscapeKey(); // 탈출 키 개수 증가
			}
		}
		else {
			View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "오답! 키를 획득하지 못했습니다.");
		}
	}
	else {
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "이미 푼 문제입니다.");
	}
	isTextPainted = true;
}


// 문제를 풀고 정답을 입력받는 함수. 정답을 맞추면 true, 못맞추면 false 반환
bool Room2::playQuiz() {
	textcolor(BLACK);
	textbackground(WHITE);
	View::xyPutStr(BackGround::textFieldX + 5, BackGround::textFieldY + 1, "_");
	
	textcolor(WHITE);
	textbackground(BLACK);
	View::xyPutStr(BackGround::textFieldX + 7, BackGround::textFieldY + 1, "_");
	View::xyPutStr(BackGround::textFieldX + 9, BackGround::textFieldY + 1, "_");
	View::xyPutStr(BackGround::textFieldX + 11, BackGround::textFieldY + 1, "_");


	// 정답을 제출 했는지 아닌지 확인하는 변수
	bool isSubmitted = false;
	// 답이 올바른지 확인하는 변수
	bool isCorrect = true;
	// 몇번째 칸에 답을 작성하고 있는지 저장하는 변수
	int currentBlock = 0;
	// 사용자가 입력할 답 배열
	int answer[4] = { 0,0,0,0 };
	// 최종 정답
	int resultAnswer[4] = { 1,0,0,1 };

	int key = 0;
	while (!isSubmitted) {
		key = Controller::getKey();
		switch (key) {
		case ENTERKEY:
			isSubmitted = true; // enter를 누르면 선택 종료
			for (int i = 0; i < 4; ++i) {
				if (answer[i] != resultAnswer[i]) {
					isCorrect = false;
					break;
				}
			}
			View::clearAllText();
			break;
		case LEFTKEY:
			// 왼쪽을 눌렀을 때 가장 왼쪽 칸이면 왼쪽으로 못감
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
			// 오른쪽을 눌렀을 때 가장 오른쪽 칸이면 오른쪽으로 못감
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
			// 누른 키의 타입이 0~9까지의 숫자일때만 가능
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

// 현재 캐릭터가 위치한 장애물을 반환하는 함수
Box* Room2::getCurrentObstacle() {
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



// -------------- mainCharacter ----------------- //
void Room2::paintCharacter() {
	Character* character = model->getCharacter();

	int key;

	textcolor(BLACK); // 캐릭터 색상
	textbackground(WHITE);
	View::xyPutStr(character->getXPos(), character->getYPos(), "!");
	// 현재 캐릭터가 계속해서 해당 방에 존재할 것이면 반복문 계속.
	while (isInRoom) {
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
				Model::moveCount += 2;
				// 캐릭터가 장애물과 부딪혔다면, 현재 부딪힌 장애물을 얻어온다.
				Box* currentObstacle = getCurrentObstacle();
				if (*currentObstacle == obstacle[0]) {
					eventOneFunc();
				}
				else if (*currentObstacle == obstacle[1]) {
					eventTwoFunc();
				}
				else {
					if (*currentObstacle == entranceVector.at(0))
						// 입구에 도착한 것이라면, Room1으로 가는 이벤트를 발생시킨다.
						eventEastEntranceFunc(1);
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
