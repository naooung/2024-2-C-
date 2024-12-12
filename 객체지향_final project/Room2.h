#pragma once
#include "Parent Room.h"


class Room2 : public ParentRoom {
private:
	Box obstacle[2];
	bool didGetKey;


public:
	Room2(Model* model, View* view) : ParentRoom(model, view) {
		didGetKey = false;
	}
	virtual ~Room2() {
	}


	virtual void paintRoom() override;


private:
	// 사용자가 특정 좌표에서 space 키를 눌렀는지 확인하는 상호작용 확인 함수
	bool isImpacted();

	// --------- obstacle ----------- // 
	// 장애물들을 출력하는 함수
	void paintObstacles();

	// 장애물들 초기화 함수
	void initObstacles();

	// ------------ event Function ------------ // 
	// 첫번째 장애물과 상호작용했을 때 실행될 함수
	void eventOneFunc();
	// 두번째 장애물과 상호작용했을 때 실행될 함수
	void eventTwoFunc();

	// 문제를 풀고 정답을 입력받는 함수. 정답을 맞추면 true, 못맞추면 false 반환
	bool playQuiz();


	// 현재 캐릭터가 위치한 장애물을 반환하는 함수
	Box* getCurrentObstacle();


	virtual void paintCharacter() override;
};