#pragma once
#include "Parent Room.h"

class Room4 : public ParentRoom{
private:
	int wall[20][20];
	Box keyBox;
	bool didGetKey;

public:
	Room4(Model* model, View* view) : ParentRoom(model, view) {
		didGetKey = false;
	}
	virtual ~Room4() {
	}


	virtual void paintRoom() override;


private:
	// ����ڰ� Ư�� ��ǥ���� space Ű�� �������� Ȯ���ϴ� ��ȣ�ۿ� Ȯ�� �Լ�
	bool isImpacted();

	// ------------ Wall & KeyBox ------------ //
	// �̷� ���� �ʱ�ȭ�ϴ� �Լ�
	void initWall();
	// �̷� ���� ����ϴ� �Լ�
	void paintWall();

	// ������ڸ� �ʱ�ȭ�ϴ� �Լ�
	void initKeyBox();
	// ������ڸ� ����ϴ� �Լ�
	void paintKeyBox();

	// ------------ event Function ------------ // 
	// ����ڰ� ������ڿ� ��ȣ�ۿ����� �� ����� �Լ�
	void eventKeyBoxFunc();


	// ���� ĳ���Ͱ� ��ġ�� ��ֹ��� ��ȯ�ϴ� �Լ�
	Box* getCurrentObstacle();

	virtual void paintCharacter() override;
};