#ifndef __WINDOWSCTRL_H
#define __WINDOWSCTRL_H

#include <Windows.h>

#define BOARD_POS_X 100
#define BOARD_POS_Y 100
#define BOARD_WIDTH 512
#define BOARD_HEIGHT 512

#define KEY_PRESS(vk) (GetAsyncKeyState(vk)&1?1:0)

void initWindows();
void initBoard(int argc, char** argv);
void gotoxy(HANDLE hOut, int x, int y);
void centerPrint(HANDLE hOut, int y, const char* str);

#endif