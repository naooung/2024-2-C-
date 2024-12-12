#pragma once
#include "Parent Room.h"

class Room7 : public ParentRoom {
private:
	Box walls[4];
	Box keyBox;
	bool didGetKey;

public:
	Room7(Model* model, View* view) : ParentRoom(model, view) {
		didGetKey = false;
	}
	virtual ~Room7() {
	}


	virtual void paintRoom() override;


private:
	// 사용자가 특정 좌표에서 space 키를 눌렀는지 확인하는 상호작용 확인 함수
	bool isImpacted();

	// ------------ Wall & KeyBox ------------ //
	// 벽을 초기화하는 함수
	void initWalls();
	// 벽을 출력하는 함수
	void paintWalls();

	// 열쇠상자를 초기화하는 함수
	void initKeyBox();
	// 열쇠상자를 출력하는 함수
	void paintKeyBox();

	// ------------ event Function ------------ // 
	// 사용자가 열쇠상자와 상호작용했을 때 실행될 함수
	void eventKeyBoxFunc();

	// 열쇠상자와 상호작용 후 호출할 게임을 실행하는 함수
	bool eventGameFuc();


	// 현재 캐릭터가 위치한 장애물을 반환하는 함수
	Box* getCurrentObstacle();

	virtual void paintCharacter() override;

	// 키가 이동할 위치를 받아서 벽의 위치와 비교 후 이동 가능한지 확인하는 함수
	bool possibleToMove(int futureX, int futureY);

};