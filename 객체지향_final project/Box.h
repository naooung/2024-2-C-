#pragma once
// 그림을 손쉽게 그리기 위한 Box 클래스
// 해당 클래스는 x,y 좌표, width, height의 데이터를 담고 있디.
class Box {
private:
	int x, y; // 박스의 좌측 상단 꼭짓점의 좌표
	int width, height;



public:
	Box(int _x, int _y, int _width, int _height)
		:x(_x), y(_y), width(_width), height(_height)
	{}
	Box() {
		Box(0, 0, 0, 0);
	}
	~Box() {}

	// ----- getter / setter ----- //
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	int getWidth() {
		return width;
	}
	int getHeight() {
		return height;
	}
	void setX(int x) {
		this->x = x;
	}
	void setY(int y) {
		this->y = y;
	}
	void setWidth(int width) {
		this->width = width;
	}
	void setHeight(int height) {
		this->height = height;
	}

	//Room4에서 사용
	void plusX(int n) {
		this->x += n;
	}
	void plusY(int n) {
		this->y += n;
	}
	
	bool operator==(const Box& other) const {
		return x == other.x && y == other.y &&
			width == other.width && height == other.height;
	}

	void operator=(const Box& other) {
		this->x = other.x;
		this->y = other.y;
		this->width = other.width;
		this->height = other.height;
	}

	// ---- 박스를 그리는 함수 ---- //
	void paintBox(char color);
};