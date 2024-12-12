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

	// ����ڰ� Ư�� ��ǥ���� space Ű�� �������� Ȯ���ϴ� ��ȣ�ۿ� Ȯ�� �Լ�
	bool isImpacted();

	// ���� ĳ���Ͱ� ��ġ�� ��ֹ��� ��ȯ�ϴ� �Լ�
	Box* getCurrentObstacle();


	virtual void paintCharacter() override;
};