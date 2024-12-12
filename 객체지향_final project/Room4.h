#pragma once
#include "Parent Room.h"

class Room4 : public ParentRoom{
private:
	int wall[20][20];
	Box keyBox;
	bool didGetKey;

public:
	Room4(Model* model, View* view) : ParentRoom(model, view) {
		didGetKey = false;
	}
	virtual ~Room4() {
	}


	virtual void paintRoom() override;


private:
	// 사용자가 특정 좌표에서 space 키를 눌렀는지 확인하는 상호작용 확인 함수
	bool isImpacted();

	// ------------ Wall & KeyBox ------------ //
	// 미로 벽을 초기화하는 함수
	void initWall();
	// 미로 벽을 출력하는 함수
	void paintWall();

	// 열쇠상자를 초기화하는 함수
	void initKeyBox();
	// 열쇠상자를 출력하는 함수
	void paintKeyBox();

	// ------------ event Function ------------ // 
	// 사용자가 열쇠상자와 상호작용했을 때 실행될 함수
	void eventKeyBoxFunc();


	// 현재 캐릭터가 위치한 장애물을 반환하는 함수
	Box* getCurrentObstacle();

	virtual void paintCharacter() override;
};