#pragma once
#include "View.h"
#include "Model.h"

#define UPKEY 0xe048
#define DOWNKEY 0xe050
#define LEFTKEY 0xe04b
#define RIGHTKEY 0xe04d
#define SPACEKEY 0x20
#define ENTERKEY 0x0d

#define ZEROKEY 0x30
#define ONEKEY 0x31
#define TWOKEY 0x32
#define THREEKEY 0x33
#define FOURKEY 0x34
#define FIVEKEY 0x35
#define SIXKEY 0x36
#define SEVENKEY 0x37
#define EIGHTKEY 0x38
#define NINEKEY 0x39


using namespace std;
class Controller {
private:
	View *view;
	Model *model;


public:
	Controller() {
		model = new Model();
		view = new View(model);
	}
	~Controller() {
		delete model;
		delete view;
	}

	void startGame();
	static int getKey();
};