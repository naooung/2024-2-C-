#pragma once
#include "Parent Room.h"

class Room5 : public ParentRoom {
private:
	// ����ڰ� �� ���� ���� �迭
	Box path[8];
	// ������ ���� �ٽ� �����ִ� ��ֹ�
	Box obstacle[2];


public:
	Room5(Model* model, View* view) : ParentRoom(model, view) {
	}
	virtual ~Room5() {
	}


	virtual void paintRoom() override;
	
	


private:
	// ����ڰ� Ư�� ��ǥ���� space Ű�� �������� Ȯ���ϴ� ��ȣ�ۿ� Ȯ�� �Լ�
	bool isImpacted();

	// --------- obstacle ----------- // 
	// ����ڰ� �� ���� ����ϴ� �Լ�
	void paintObstacles(char color);
	// ��ֹ��� �ʱ�ȭ �Լ�
	void initObstacles();

	// --------- path ----------- // 
	// ����ڰ� �� ���� ����ϴ� �Լ�
	void paintPath(char color);
	// �� �ʱ�ȭ �Լ�
	void initPath();
	

	// ------------ event Function ------------ // 
	// ��ֹ��� ��ȣ�ۿ����� �� ����� �Լ�
	void eventObstacleFunc();
	
	// �濡�� ����� ��, ���� ������ �̵��ϴ� �Լ�
	void eventGoBackPrevRoom();


	// ���� ĳ���Ͱ� ��ġ�� ��ֹ��� ��ȯ�ϴ� �Լ�
	Box* getCurrentObstacle();


	virtual void paintCharacter() override;
};