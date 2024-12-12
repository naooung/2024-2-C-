#include "View.h"
#include "Controller.h"
#include <conio.h>
#include "Consola.h"
#include "BackGround.h"


void View::startPage() {
    paintTitle(WHITE);
    if (selectYesNo()) {
        paintTitle(BLACK);
        playGame();
    }
    else {
        paintTitle(BLACK);
    }
}
void View::paintTitle(char color) {
    int pattern[20][50] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//5
      {0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},//10
      {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//11
      {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//15
      {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}//20
    };

    Box b(0, 0, 2, 1);

    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 50; ++j) {
            if (pattern[i][j] == 1) { // �Ϲ� ��
                b.paintBox(color);
            }
            b.plusX(2);
        }
        b.setX(BackGround::x);
        b.plusY(1);
    }
}

bool View::selectYesNo() {
    // �⺻ ������ Yes�� �����ϵ��� �д�.
    textcolor(BLACK);
    textbackground(WHITE);
    View::xyPutStr(30, 21, "Yes");
    textcolor(WHITE);
    textbackground(BLACK);
    View::xyPutStr(35, 21, "No");

    // Yes�� No�� 1���� �ߴ��� �ƴ��� Ȯ���ϴ� ����
    bool isSelected = false;
    // ���� �����Ѱ� ���� ��� �ִ� ���� (Yes�� 1, No�� 0)
    bool selected = true;

    int key = 0;
    while (!isSelected) {
        key = Controller::getKey();
        switch (key) {
        case ENTERKEY:
            isSelected = true; // enter�� ������ ���� ����
            // ���� ���� ���� Yes�� No�� �����ش�.
            textbackground(BLACK);
            View::xyPutStr(30, 21, "   ");
            View::xyPutStr(35, 21, "   ");
            break;
        case LEFTKEY:
            // ������ Yes�� �Ǿ������� ���� Ű�� ������ ������ �������� �ʴ´�.
            if (!selected) { // No�� ���õǾ�������
                selected = true; // Yes�� �������ְ�, 
                textcolor(BLACK);
                textbackground(WHITE);
                View::xyPutStr(30, 21, "Yes");
                textcolor(WHITE);
                textbackground(BLACK);
                View::xyPutStr(35, 21, "No");
            }
            break;
        case RIGHTKEY:
            // ������ No�� �Ǿ������� ������ Ű�� ������ ������ �������� �ʴ´�.
            if (selected) { // Yes�� ���õǾ�������
                selected = false; // No�� �������ְ�, 
                textcolor(WHITE);
                textbackground(BLACK);
                View::xyPutStr(30, 21, "Yes");
                textcolor(BLACK);
                textbackground(WHITE);
                View::xyPutStr(35, 21, "No");
            }
            break;
        }

    }
    return selected;
}


void View::playGame() {
    ParentRoom* currentRoom = nullptr;
    bool canPlayGame = Model::canPlayGame;
    int currentRoomNum = Model::currentRoomNum;
    while (canPlayGame) {
        canPlayGame = Model::canPlayGame;
        currentRoomNum = Model::currentRoomNum;
        currentRoom = roomVector->at(currentRoomNum);
        currentRoom->paintRoom();
    }
}



// --------------- static �޼ҵ� --------------- //
void View::fillBox(int x1, int y1, int x2, int y2, char color) {
    textbackground(color);
    for (int y = y1; y < y2; ++y)
        for (int x = x1; x < x2; ++x)
            xyPutC(x, y, ' ');
}

void View::xyPutC(int x, int y, char ch) {
    gotoxy(x, y);
    cout << ch;
}

void View::xyPutStr(int x, int y, const char str[]) {
    gotoxy(x, y);
    cout << str;
}
void View::xyPutStr(int x, int y, string str) {
    gotoxy(x, y);
    cout << str;
}




void View::clearAllText() {
    textbackground(BLACK);
    View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY - 5, "                                                                 ");
    View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY - 4, "                                                                 ");
    View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY - 3, "                                                                 ");
    View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY - 2, "                                                                 ");
    View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY - 1, "                                                                 ");
    View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "                                                                 ");
    View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY + 1, "                                                                 ");
    View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY + 2, "                                                                 ");
    View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY + 3, "                                                                 ");
    View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY + 4, "                                                                 ");
    View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY + 5, "                                                                 ");
}


// ---- getter / setter ----- //
vector<ParentRoom*>* View::getRoomVector() {
    return roomVector;
}