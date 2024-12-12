#pragma once
#include "Parent Room.h"


class Room1 : public ParentRoom {
private:
	bool playedTutorial;
public:
	Room1(Model* model, View *view) : ParentRoom(model, view) {
		playedTutorial = false;
	}
	virtual ~Room1() {
	}

	
	virtual void paintRoom() override;


private:
	void paintPattern();

	// ����ڰ� Ư�� ��ǥ���� space Ű�� �������� Ȯ���ϴ� ��ȣ�ۿ� Ȯ�� �Լ�
	bool isImpacted();
	

	// ------------ event Function ------------ // 
	// ���� ���� ��ȣ�ۿ����� �� ����� �Լ�
	// 5�� ���� ���� �� ������ ���־�� �ϹǷ�, �������̵� �ؼ� ���
	void eventNorthEntranceFunc();

	


	// ���� ĳ���Ͱ� ��ġ�� ��ֹ��� ��ȯ�ϴ� �Լ�
	Box* getCurrentObstacle();

	void paintTutorial();

	virtual void paintCharacter() override;
};