#pragma once
#include <vector>
#include <string>
#include "Room0.h"
#include "Room1.h"
#include "Room2.h"
#include "Room3.h"
#include "Room4.h"
#include "Room5.h"
#include "Room6.h"
#include "Room7.h"
#include "Room8.h"
#include <iostream>
using namespace std;

class View {
private:
	Model *model;
	vector<ParentRoom*> *roomVector; 
	// 추상 클래스로 각 방들을 받기 위한 벡터
	// 탈출하기 위한 열쇠

public:
	View(Model *model) {
		this->model = model;	
		roomVector = new vector<ParentRoom*>();

		// 각 방들 모두 생성
		ParentRoom* room0 = new Room0(model, this);
		ParentRoom* room1 = new Room1(model, this);
		ParentRoom* room2 = new Room2(model, this);
		ParentRoom* room3 = new Room3(model, this);
		ParentRoom* room4 = new Room4(model, this);
		ParentRoom* room5 = new Room5(model, this);
		ParentRoom* room6 = new Room6(model, this);
		ParentRoom* room7 = new Room7(model, this);
		ParentRoom* room8 = new Room8(model, this);


		// 생성된 방들 모두 벡터에 순서대로 집어넣기
		roomVector->push_back(room0);
		roomVector->push_back(room1);
		roomVector->push_back(room2);
		roomVector->push_back(room3);
		roomVector->push_back(room4);
		roomVector->push_back(room5);
		roomVector->push_back(room6);
		roomVector->push_back(room7);
		roomVector->push_back(room8);
	}
	~View() {
		delete roomVector;
	}

	// ------- 시작 페이지 --------- //
	void startPage();
	void paintTitle(char color);
	bool selectYesNo();

	// 게임 플레이 함수
	void playGame();


	// ------------ 그림을 그릴 수 있는 기본 static 함수들 ---------------- //
	static void fillBox(int x1, int y1, int x2, int y2, char color);
	static void xyPutC(int x, int y, char ch);
	static void xyPutStr(int x, int y, const char str[]);
	static void xyPutStr(int x, int y, string str);


	static void clearAllText();


	// ----- getter / setter ----- //
	vector<ParentRoom*>* getRoomVector();
};

