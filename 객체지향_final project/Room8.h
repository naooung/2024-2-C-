#pragma once
#include "Parent Room.h"
#include "BackGround.h"
class View;
class Room8 : public ParentRoom {
private:
	bool didGetKey;
	Box obstacle;
	Box* walls[3];

	int remainChance;

public:
	Room8(Model* model, View* view) : ParentRoom(model, view) {
		didGetKey = false;
		walls[0] = new Box(BackGround::x, BackGround::y, BackGround::width + 1, 7);
		walls[1] = new Box(BackGround::x, BackGround::y + 7, BackGround::width + 1, 7);
		walls[2] = new Box(BackGround::x, BackGround::y + 12, BackGround::width + 1, 9);
		remainChance = 3;
	}
	virtual ~Room8() {
	}


	virtual void paintRoom() override;


private:
	// 사용자가 특정 좌표에서 space 키를 눌렀는지 확인하는 상호작용 확인 함수
	bool isImpacted();

	// --------- obstacle ----------- // 
	// 장애물들을 출력하는 함수
	void paintObstacle();

	// 장애물들 초기화 함수
	void initObstacle();


	// ------------ event Function ------------ // 
	// 동쪽 문과 상호작용했을 때 실행될 함수 (나가는 최종 문)
	// 키를 모았는지 확인해야 하므로 함수 오버라이딩 해서 사용
	void eventEastEntranceFunc();

	void eventObstacleFunc();

	bool playQuiz();

	// 사용자가 문제를 한번 틀릴 때마다 방을 더 작게 만들어주는 함수
	void makeRoomSmaller(int i);

	

	void paintEndPage(bool didEscape);


	// 현재 캐릭터가 위치한 장애물을 반환하는 함수
	Box* getCurrentObstacle();


	virtual void paintCharacter() override;

	bool possibleToMove(int futureXPos, int futureYPos);
};