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

// 각 방들의 부모 클래스
class ParentRoom {
protected:
	Model *model;
	View *view;
	vector<Box> entranceVector; // 각 방에 있는 입구들을 담은 배열
	bool isInRoom; // 해당 방에 계속 캐릭터가 존재할건지 유무를 판단하는 변수
	// 사용자가 있었던 이전 방 번호를 담고 있는 변수
	int prevRoom;

	bool isTextPainted;

public:
	ParentRoom(Model* model, View* view):model(model), view(view) {
		isInRoom = true;
		prevRoom = 0;
		isTextPainted = false;
	}
	// 가상 소멸자 사용해야 메모리 누수 방지가 가능함
	virtual ~ParentRoom() {
	}

	// 방을 색칠하는 함수. Model이 방들의 배열을 갖고 있으면 이 함수로 각 방을 출력할 것이다.
	// 따라서, 자식 클래스들에게 반드시 override 표현을 해주어야 한다. 그래야 ParentRoom으로 해당 객체들을 받을 때 각자의 메소드가 실행된다.
	virtual void paintRoom()=0;
	virtual void paintInterface();

	// 기본적으로 방 이동만 수행하는 함수들. 따라서, 해당 방이 잠긴 문을 열어야되는 경우, 오버라이딩을 해서 사용해야함
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
	// 입구를 entranceVector에 추가하는 함수. 방향을 인자로 주면, 해당 방향이 vector에 있는지 검사하고 추가한다.
	virtual void addEntrance(int direction);

	// paintRoom 내부에서 for문으로 사용할 "각 방의 입구들을 그리는 함수". 방별로 entranceVector에 저장되어있는 값으로 입구를 그린다.
	virtual void paintEntrance();


	// -------------- void paintBackGround() ------------------ //
	// 배경을 그리는 함수. clrscr() 함수가 내부에서 실행되었기에, 화면을 그릴 때 가장 처음에 실행되어야 함
	// 기본 배경 페인트 함수
	virtual void paintBackGround();

	// -------------- void paintCharacter() ------------------ //
	// 캐릭터를 그리는 함수.
	virtual void paintCharacter();


	// ----------- Yes/No 선택 함수 ------------- // 
	// 반환값이 true이면 Yes, false이면 No를 선택한 것이다.
	bool selectYesNo();
};

