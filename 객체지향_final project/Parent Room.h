#pragma once
#include <vector>
#include "Box.h"

#define NORTH 0
#define SOUTH 1
#define WEST 2
#define EAST 3

using namespace std;

class Model;
class View;

// �� ����� �θ� Ŭ����
class ParentRoom {
protected:
	Model *model;
	View *view;
	vector<Box> entranceVector; // �� �濡 �ִ� �Ա����� ���� �迭
	bool isInRoom; // �ش� �濡 ��� ĳ���Ͱ� �����Ұ��� ������ �Ǵ��ϴ� ����
	// ����ڰ� �־��� ���� �� ��ȣ�� ��� �ִ� ����
	int prevRoom;

	bool isTextPainted;

public:
	ParentRoom(Model* model, View* view):model(model), view(view) {
		isInRoom = true;
		prevRoom = 0;
		isTextPainted = false;
	}
	// ���� �Ҹ��� ����ؾ� �޸� ���� ������ ������
	virtual ~ParentRoom() {
	}

	// ���� ��ĥ�ϴ� �Լ�. Model�� ����� �迭�� ���� ������ �� �Լ��� �� ���� ����� ���̴�.
	// ����, �ڽ� Ŭ�����鿡�� �ݵ�� override ǥ���� ���־�� �Ѵ�. �׷��� ParentRoom���� �ش� ��ü���� ���� �� ������ �޼ҵ尡 ����ȴ�.
	virtual void paintRoom()=0;
	virtual void paintInterface();

	// �⺻������ �� �̵��� �����ϴ� �Լ���. ����, �ش� ���� ��� ���� ����ߵǴ� ���, �������̵��� �ؼ� ����ؾ���
	virtual void eventNorthEntranceFunc(int roomNum);
	virtual void eventSouthEntranceFunc(int roomNum);
	virtual void eventWestEntranceFunc(int roomNum);
	virtual void eventEastEntranceFunc(int roomNum);


	void setIsInRoom(bool value);
	int getPrevRoom() {
		return prevRoom;
	}
	void setPrevRoom(int num) {
		prevRoom = num;
	}
protected:
	// �Ա��� entranceVector�� �߰��ϴ� �Լ�. ������ ���ڷ� �ָ�, �ش� ������ vector�� �ִ��� �˻��ϰ� �߰��Ѵ�.
	virtual void addEntrance(int direction);

	// paintRoom ���ο��� for������ ����� "�� ���� �Ա����� �׸��� �Լ�". �溰�� entranceVector�� ����Ǿ��ִ� ������ �Ա��� �׸���.
	virtual void paintEntrance();


	// -------------- void paintBackGround() ------------------ //
	// ����� �׸��� �Լ�. clrscr() �Լ��� ���ο��� ����Ǿ��⿡, ȭ���� �׸� �� ���� ó���� ����Ǿ�� ��
	// �⺻ ��� ����Ʈ �Լ�
	virtual void paintBackGround();

	// -------------- void paintCharacter() ------------------ //
	// ĳ���͸� �׸��� �Լ�.
	virtual void paintCharacter();


	// ----------- Yes/No ���� �Լ� ------------- // 
	// ��ȯ���� true�̸� Yes, false�̸� No�� ������ ���̴�.
	bool selectYesNo();
};

