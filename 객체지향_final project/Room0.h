#pragma once
#include "Parent Room.h"

class Room0 : public ParentRoom{
private:
	Box obstacle[3];
	bool isInRoom; // �ش� �濡 ��� ĳ���Ͱ� �����Ұ��� ������ �Ǵ��ϴ� �Լ�.
	bool didGetKey;
	int currentTutorial;


public:
	Room0(Model *model, View* view) : ParentRoom(model, view){
		isInRoom = true;
		didGetKey = false;
		currentTutorial = 1;
	}
	virtual ~Room0() {
	}


	virtual void paintRoom() override;
	virtual void paintInterface() override;
	
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
	// ����° ��ֹ��� ��ȣ�ۿ����� �� ����� �Լ�
	void eventThreeFunc();

	// ����ڰ� �Ա��� ��ȣ�ۿ����� �� ����� �Լ�
	// Ʃ�丮���̹Ƿ� �ش� �Լ��� �������̵� �ؼ� ����Ѵ�.
	void eventNorthEntranceFunc();


	// ���� ĳ���Ͱ� ��ġ�� ��ֹ��� ��ȯ�ϴ� �Լ�
	Box* getCurrentObstacle();
	
	// ----- Ʃ�丮�� ��� �Լ� ----- //
	void paintTutorial();

	virtual void paintCharacter() override;

	
};