#pragma once
#include "Parent Room.h"

class Room7 : public ParentRoom {
private:
	Box walls[4];
	Box keyBox;
	bool didGetKey;

public:
	Room7(Model* model, View* view) : ParentRoom(model, view) {
		didGetKey = false;
	}
	virtual ~Room7() {
	}


	virtual void paintRoom() override;


private:
	// ����ڰ� Ư�� ��ǥ���� space Ű�� �������� Ȯ���ϴ� ��ȣ�ۿ� Ȯ�� �Լ�
	bool isImpacted();

	// ------------ Wall & KeyBox ------------ //
	// ���� �ʱ�ȭ�ϴ� �Լ�
	void initWalls();
	// ���� ����ϴ� �Լ�
	void paintWalls();

	// ������ڸ� �ʱ�ȭ�ϴ� �Լ�
	void initKeyBox();
	// ������ڸ� ����ϴ� �Լ�
	void paintKeyBox();

	// ------------ event Function ------------ // 
	// ����ڰ� ������ڿ� ��ȣ�ۿ����� �� ����� �Լ�
	void eventKeyBoxFunc();

	// ������ڿ� ��ȣ�ۿ� �� ȣ���� ������ �����ϴ� �Լ�
	bool eventGameFuc();


	// ���� ĳ���Ͱ� ��ġ�� ��ֹ��� ��ȯ�ϴ� �Լ�
	Box* getCurrentObstacle();

	virtual void paintCharacter() override;

	// Ű�� �̵��� ��ġ�� �޾Ƽ� ���� ��ġ�� �� �� �̵� �������� Ȯ���ϴ� �Լ�
	bool possibleToMove(int futureX, int futureY);

};