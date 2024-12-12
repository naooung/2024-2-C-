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
	// ����ڰ� Ư�� ��ǥ���� space Ű�� �������� Ȯ���ϴ� ��ȣ�ۿ� Ȯ�� �Լ�
	bool isImpacted();

	// --------- obstacle ----------- // 
	// ��ֹ����� ����ϴ� �Լ�
	void paintObstacles();

	// ��ֹ��� �ʱ�ȭ �Լ�
	void initObstacles();

	// ------------ event Function ------------ // 
	// ù��° ��ֹ��� ��ȣ�ۿ����� �� ����� �Լ�
	void eventOneFunc();
	// �ι�° ��ֹ��� ��ȣ�ۿ����� �� ����� �Լ�
	void eventTwoFunc();

	// ������ Ǯ�� ������ �Է¹޴� �Լ�. ������ ���߸� true, �����߸� false ��ȯ
	bool playQuiz();


	// ���� ĳ���Ͱ� ��ġ�� ��ֹ��� ��ȯ�ϴ� �Լ�
	Box* getCurrentObstacle();


	virtual void paintCharacter() override;
};