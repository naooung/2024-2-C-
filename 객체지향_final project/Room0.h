#pragma once
#include "Parent Room.h"

class Room0 : public ParentRoom{
private:
	Box obstacle[3];
	bool isInRoom; // 해당 방에 계속 캐릭터가 존재할건지 유무를 판단하는 함수.
	bool didGetKey;
	int currentTutorial;


public:
	Room0(Model *model, View* view) : ParentRoom(model, view){
		isInRoom = true;
		didGetKey = false;
		currentTutorial = 1;
	}
	virtual ~Room0() {
	}


	virtual void paintRoom() override;
	virtual void paintInterface() override;
	
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
	// 세번째 장애물과 상호작용했을 때 실행될 함수
	void eventThreeFunc();

	// 사용자가 입구와 상호작용했을 때 실행될 함수
	// 튜토리얼이므로 해당 함수를 오버라이딩 해서 사용한다.
	void eventNorthEntranceFunc();


	// 현재 캐릭터가 위치한 장애물을 반환하는 함수
	Box* getCurrentObstacle();
	
	// ----- 튜토리얼 출력 함수 ----- //
	void paintTutorial();

	virtual void paintCharacter() override;

	
};