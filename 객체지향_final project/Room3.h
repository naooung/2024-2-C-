#pragma once
#include "Parent Room.h"


class Room3 : public ParentRoom {
public:
	Room3(Model* model, View* view) : ParentRoom(model, view) {
	}
	virtual ~Room3() {
	}


	virtual void paintRoom() override;


private:
	
	void paintPattern();

	// 사용자가 특정 좌표에서 space 키를 눌렀는지 확인하는 상호작용 확인 함수
	bool isImpacted();

	// 현재 캐릭터가 위치한 장애물을 반환하는 함수
	Box* getCurrentObstacle();


	virtual void paintCharacter() override;
};