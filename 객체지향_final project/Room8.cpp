#include "Room8.h"
#include "Consola.h"
#include "View.h"
#include "Controller.h"
#include <thread>   
#include <chrono>
#include <string>

void Room8::paintRoom() {
	addEntrance(WEST); // 0번  
	addEntrance(EAST); // 1번 
	initObstacle();



	// 아래는 paint. 순서를 고려해야함
	paintBackGround();	// 배경 출력

	paintEntrance();	// 입구 출력

	paintObstacle();

	paintCharacter();	// 캐릭터 출력(반복문 및 키 입력)
}

// 사용자가 특정 좌표에서 space 키를 눌렀을 때, 캐릭터가 장애물과 충돌했는지 확인하는 상호작용 확인 함수
bool Room8::isImpacted() {
	// 캐릭터 포인터 획득
	Character* character = model->getCharacter();

	// 캐릭터의 x/y 좌표
	int charX = character->getXPos();
	int charY = character->getYPos();

	if (obstacle.getX() <= charX && charX <= obstacle.getX() + obstacle.getWidth() && obstacle.getY() <= charY && charY <= obstacle.getY() + obstacle.getHeight())
		return true;

	// 입구와도 충돌했는지 확인한다.
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
	View::xyPutStr(BackGround::x + 19, BackGround::y + 9, "문제");
	View::xyPutStr(BackGround::x + 19, BackGround::y + 10, "보기");
	
}

// 장애물들 초기화 함수
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
			View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY - 2, "현재 지나온 방에는 총 3개의 기호 문자들이 있었습니다.");
			View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY - 1, "지금까지 나오지 않은 문자를 고르세요.");
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
					break;
				}
			}
			else {
				textbackground(WHITE);
				textcolor(BLACK);
				View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "오답! 키를 획득하지 못했습니다.");
				std::this_thread::sleep_for(std::chrono::seconds(1));  // 1초 동안 대기
				// 남은 기회 데이터를 줄이고 난 뒤에 방을 더 작게 만들어야함
				--remainChance;
				// 방을 작게 만드는 함수
				makeRoomSmaller(remainChance);
				std::this_thread::sleep_for(std::chrono::milliseconds(500));  // 0.5초 동안 대기
			}
			isTextPainted = true;
		}
		// 만약 모든 기회를 소진했다면
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
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "이미 푼 문제입니다.");
		isTextPainted = true;
	}
}

void Room8::makeRoomSmaller(int i) {
	// 한번 틀렸을 경우
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


// 문제를 풀고 정답을 입력받는 함수. 정답을 맞추면 true, 못맞추면 false 반환
bool Room8::playQuiz() {
	textcolor(BLACK);
	textbackground(WHITE);
	View::xyPutC(BackGround::textFieldX + 5, BackGround::textFieldY + 1, '0');

	textcolor(WHITE);
	textbackground(BLACK);
	View::xyPutC(BackGround::textFieldX + 7, BackGround::textFieldY + 1, '?');
	View::xyPutC(BackGround::textFieldX + 9, BackGround::textFieldY + 1, '!');
	View::xyPutC(BackGround::textFieldX + 11, BackGround::textFieldY + 1, 'm');


	// 정답을 제출 했는지 아닌지 확인하는 변수
	bool isSubmitted = false;
	// 답이 올바른지 확인하는 변수
	bool isCorrect = true;
	// 몇번째 칸에 답을 작성하고 있는지 저장하는 변수
	int currentBlock = 0;
	// 최종 정답
	char resultAnswer = 'm';
	char selectArray[4] = { '0', '?', '!', 'm' };

	int key = 0;
	while (!isSubmitted) {
		key = Controller::getKey();
		switch (key) {
		case ENTERKEY:
			isSubmitted = true; // enter를 누르면 선택 종료
			if (selectArray[currentBlock] != resultAnswer)
				isCorrect = false;
			View::clearAllText();
			break;
		case LEFTKEY:
			// 왼쪽을 눌렀을 때 가장 왼쪽 칸이면 왼쪽으로 못감
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
			// 오른쪽을 눌렀을 때 가장 오른쪽 칸이면 오른쪽으로 못감
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

// 동쪽 문과 상호작용했을 때 실행될 함수 (나가는 최종 문)
// 키를 모았는지 확인해야 하므로 함수 오버라이딩 해서 사용
void Room8::eventEastEntranceFunc() {
	textbackground(WHITE);
	textcolor(BLACK);

	// 아직 모든 키를 얻지 못했다면, 그냥 함수 종료시킴
	if (Model::escapeKey != 4) {
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "모든 키를 얻어야 저택에서 탈출할 수 있습니다!");
		isTextPainted = true;
		return;
	}

	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "저택에서 탈출하시겠습니까?");
	// Yes와 No 중에서 선택한 후, 결과값을 받아온다.
	bool selected = selectYesNo();
	// enter를 눌렀을 때, 선택한 문자가 Yes인 경우
	if (selected) {
		isInRoom = false;
		View::clearAllText();
		// 인터페이스 창 지움
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
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY-3, "게임 종료. 저택을 탈출했습니다!");
	else
		View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY - 3, "게임 종료. 저택을 탈출하지 못했습니다.");
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY+-2, "획득 점수 : ");
	View::xyPutStr(BackGround::textFieldX+10, BackGround::textFieldY-2, point);
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY-1, "등급 : ");
	if (!didEscape)
		level = 'F';
	View::xyPutC(BackGround::textFieldX + 5, BackGround::textFieldY - 1, level);
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "게임을 종료하시겠습니까?");

	bool selected = selectYesNo();
	// 게임을 종료한다면 view의 canfPlayGame을 false로 설정
	if(selected)
		Model::canPlayGame = false;
	// 게임을 종료하지 않는다면, 게임을 다시 시작시킴
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
		
		// roomVector의 내용물을 전부 지우고, 다시 vector에 방들을 생성해서 집어넣음
		view->getRoomVector()->clear();

		// 생성된 방들 모두 벡터에 순서대로 집어넣기
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





// 현재 캐릭터가 위치한 장애물을 반환하는 함수
Box* Room8::getCurrentObstacle() {
	// 캐릭터 포인터 획득
	Character* character = model->getCharacter();

	// 캐릭터의 x/y 좌표
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

	textcolor(BLACK); // 캐릭터 색상
	textbackground(WHITE);
	View::xyPutStr(character->getXPos(), character->getYPos(), "!");
	// 현재 캐릭터가 계속해서 해당 방에 존재할 것이면 반복문 계속.
	while (isInRoom) {
		paintInterface();
		makeRoomSmaller(remainChance);

		key = Controller::getKey();

		paintObstacle();

		// 인터페이스가 출력되는 부분에 텍스트가 출력되어있다면, 해당 부분을 지운다.
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
				// 캐릭터가 장애물과 부딪혔다면, 현재 부딪힌 장애물을 얻어온다.
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
		View::xyPutStr(character->getOldXPos(), character->getOldYPos(), " "); // 잔상 처리
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
