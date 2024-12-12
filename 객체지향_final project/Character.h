#pragma once

class Character {
private:
	int xpos, ypos;
	int oldxpos, oldypos;

public:
	Character() {
		xpos = 19;		
		ypos = 9;
		oldxpos = xpos;	
		oldypos = ypos;
	}

	~Character() {

	}

	void setStartLocation(char c) {
		if (c == 'U') {			//��
			xpos = 29;
			ypos = 5;
		}
		else if (c == 'D') {	//��
			xpos = 30;
			ypos = 24;
		}
		else if (c == 'L') {	//��
			xpos = 9;
			ypos = 14;
		}
		else if (c == 'R') {	//��
			xpos = 49;
			ypos = 14;
		}
		oldxpos = xpos;	oldypos = ypos;
	}

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();


	// ---- getter/setter ---- //
	// ���� �̵��� �� ���Ӱ� ��ǥ�� �������� �� ����ϴ� �Լ�
	void setNewCoordinate(int x, int y) {
		xpos = x;
		ypos = y;
		oldxpos = x;
		oldypos = y;
	}

	int getXPos() {
		return xpos;
	}
	int getYPos() {
		return ypos;
	}
	int getOldXPos() {
		return oldxpos;
	}
	int getOldYPos() {
		return oldypos;
	}
};