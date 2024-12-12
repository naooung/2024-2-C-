#pragma once
#include "Parent Room.h"


class Room6 : public ParentRoom {
public:
	Room6(Model* model, View* view) : ParentRoom(model, view) {
	}
	virtual ~Room6() {
	}


	virtual void paintRoom() override;


private:
	void paintPattern();
	

	// 사용자가 특정 좌표에서 space 키를 눌렀는지 확인하는 상호작용 확인 함수
	bool isImpacted();


	// ------------ event Function ------------ // 
	// 남쪽 문과 상호작용했을 때 실행될 함수
	// 5번 방의 이전 방 설정을 해줘야 하므로 오버라이딩 해서 사용
	void eventSouthEntranceFunc();
	


	// 현재 캐릭터가 위치한 장애물을 반환하는 함수
	Box* getCurrentObstacle();


	virtual void paintCharacter() override;
};