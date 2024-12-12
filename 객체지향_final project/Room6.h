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
	

	// ����ڰ� Ư�� ��ǥ���� space Ű�� �������� Ȯ���ϴ� ��ȣ�ۿ� Ȯ�� �Լ�
	bool isImpacted();


	// ------------ event Function ------------ // 
	// ���� ���� ��ȣ�ۿ����� �� ����� �Լ�
	// 5�� ���� ���� �� ������ ����� �ϹǷ� �������̵� �ؼ� ���
	void eventSouthEntranceFunc();
	


	// ���� ĳ���Ͱ� ��ġ�� ��ֹ��� ��ȯ�ϴ� �Լ�
	Box* getCurrentObstacle();


	virtual void paintCharacter() override;
};