#define GLUT_DISABLE_ATEXIT_HACK
#include "windowsCtrl.h"
#include <gl/glut.h>
#include <stdio.h>

void initWindows()
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hOutput, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(hOutput, &CursorInfo);
}

void initBoard(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(BOARD_WIDTH, BOARD_HEIGHT);
	glutInitWindowPosition(BOARD_POS_X, BOARD_POS_Y);
	glutCreateWindow("五子棋");
	glutReshapeFunc([](int width, int height) {
		glutReshapeWindow(BOARD_WIDTH, BOARD_HEIGHT);
		});
}

void gotoxy(HANDLE hOut, int x, int y)
{
	COORD pos;
	pos.X = x; //横坐标
	pos.Y = y; //纵坐标
	SetConsoleCursorPosition(hOut, pos);
}

void centerPrint(HANDLE hOut, int y, const char* str)
{
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(hOut, &bInfo);
	int dwSizeX = bInfo.dwSize.X;
	int len = strlen(str);
	int x = dwSizeX / 2 - len / 2;
	gotoxy(hOut, x, y);
	printf("%s", str);
}
