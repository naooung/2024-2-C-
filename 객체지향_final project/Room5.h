#pragma once
#include "Parent Room.h"

class Room5 : public ParentRoom {
private:
	// 사용자가 갈 길을 담은 배열
	Box path[8];
	// 밟으면 길을 다시 보여주는 장애물
	Box obstacle[2];


public:
	Room5(Model* model, View* view) : ParentRoom(model, view) {
	}
	virtual ~Room5() {
	}


	virtual void paintRoom() override;
	
	


private:
	// 사용자가 특정 좌표에서 space 키를 눌렀는지 확인하는 상호작용 확인 함수
	bool isImpacted();

	// --------- obstacle ----------- // 
	// 사용자가 갈 길을 출력하는 함수
	void paintObstacles(char color);
	// 장애물들 초기화 함수
	void initObstacles();

	// --------- path ----------- // 
	// 사용자가 갈 길을 출력하는 함수
	void paintPath(char color);
	// 길 초기화 함수
	void initPath();
	

	// ------------ event Function ------------ // 
	// 장애물과 상호작용했을 때 실행될 함수
	void eventObstacleFunc();
	
	// 길에서 벗어났을 때, 이전 방으로 이동하는 함수
	void eventGoBackPrevRoom();


	// 현재 캐릭터가 위치한 장애물을 반환하는 함수
	Box* getCurrentObstacle();


	virtual void paintCharacter() override;
};