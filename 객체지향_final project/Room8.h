#pragma once
#include "Parent Room.h"
#include "BackGround.h"
class View;
class Room8 : public ParentRoom {
private:
	bool didGetKey;
	Box obstacle;
	Box* walls[3];

	int remainChance;

public:
	Room8(Model* model, View* view) : ParentRoom(model, view) {
		didGetKey = false;
		walls[0] = new Box(BackGround::x, BackGround::y, BackGround::width + 1, 7);
		walls[1] = new Box(BackGround::x, BackGround::y + 7, BackGround::width + 1, 7);
		walls[2] = new Box(BackGround::x, BackGround::y + 12, BackGround::width + 1, 9);
		remainChance = 3;
	}
	virtual ~Room8() {
	}


	virtual void paintRoom() override;


private:
	// ����ڰ� Ư�� ��ǥ���� space Ű�� �������� Ȯ���ϴ� ��ȣ�ۿ� Ȯ�� �Լ�
	bool isImpacted();

	// --------- obstacle ----------- // 
	// ��ֹ����� ����ϴ� �Լ�
	void paintObstacle();

	// ��ֹ��� �ʱ�ȭ �Լ�
	void initObstacle();


	// ------------ event Function ------------ // 
	// ���� ���� ��ȣ�ۿ����� �� ����� �Լ� (������ ���� ��)
	// Ű�� ��Ҵ��� Ȯ���ؾ� �ϹǷ� �Լ� �������̵� �ؼ� ���
	void eventEastEntranceFunc();

	void eventObstacleFunc();

	bool playQuiz();

	// ����ڰ� ������ �ѹ� Ʋ�� ������ ���� �� �۰� ������ִ� �Լ�
	void makeRoomSmaller(int i);

	

	void paintEndPage(bool didEscape);


	// ���� ĳ���Ͱ� ��ġ�� ��ֹ��� ��ȯ�ϴ� �Լ�
	Box* getCurrentObstacle();


	virtual void paintCharacter() override;

	bool possibleToMove(int futureXPos, int futureYPos);
};