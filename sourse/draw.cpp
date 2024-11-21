#include "draw.h"
#include "windowsCtrl.h"
#include <stdio.h>
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <GL/glut.h>

//有关开始界面的变量
#define START_MENU_TITLE_HEIGHT 11
int startMenuOptionIndex = 0;
const char startMenuTitle[START_MENU_TITLE_HEIGHT][76] = { "五五五五五五五五五五五　　　子子子子子子子子　　　　　　棋　　棋　　　棋  ",
                                                           "　　　　五　　　　　　　　　　　　　　　　子　　　　　　棋　棋棋棋棋棋棋棋",
                                                           "　　　　五　　　　　　　　　　　　　　　子　　　　　棋棋棋棋　棋　　　棋  ", 
                                                           "　　　　五　　　　　　　　　　　　　　子　　　　　　　　棋　　棋棋棋棋棋  ", 
                                                           "　五五五五五五五五　　　　　　　　　子　　　　　　　　　棋　　棋　　　棋  ", 
                                                           "　　　五　　　　五　　　　子子子子子子子子子子子　　　棋棋棋　棋棋棋棋棋  ", 
                                                           "　　　五　　　　五　　　　　　　　　子　　　　　　　　棋棋　　棋　　　棋  ", 
                                                           "　　　五　　　　五　　　　　　　　　子　　　　　　　棋　棋　棋棋棋棋棋棋棋", 
                                                           "　　　五　　　　五　　　　　　　　　子　　　　　　　　　棋                ", 
                                                           "　　　五　　　　五　　　　　　　　　子　　　　　　　　　棋　　棋　　　棋  ", 
                                                           "五五五五五五五五五五五　　　　　子子子　　　　　　　　　棋　棋　　　　　棋"};
const char startOption[2][15] = { "   开始游戏   ", 
								  "-> 开始游戏   "};
const char helpOption[2][15] = { "   查看帮助   ", 
								 "-> 查看帮助   "};
const char exitOption[2][15] = { "   退出游戏   ", 
								 "-> 退出游戏   "};

//有关帮助页面的变量
#define HELP_PAGE_TITLE_HEIGHT 6
int helpPageOptionIndex = 0;
const char helpTitle[HELP_PAGE_TITLE_HEIGHT][63] = { "五子棋帮助",
								"1.五子棋是一种双人对弈的纯策略型棋类游戏，是中国传统棋类之一。", 
								"2.五子棋是在15*15的棋盘上进行的，双方轮流下子，黑方先行。     ", 
								"3.黑白双方轮流下子，黑方先行。                                ", 
								"4.每次落子后，对手可以选择悔棋，悔棋后对手可以选择悔棋。      ", 
                                "5.当一方在横、竖、斜方向上连成五子时，游戏结束。              "};
const char helpPageOption[2][39] = { "-> 返回开始菜单          制作人员     ",
									 "   返回开始菜单       -> 制作人员     "};

//有关棋盘的变量
cv::Mat boardImage;

void drawStartMenuPage()
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < START_MENU_TITLE_HEIGHT; i++)
	{
		centerPrint(hOutput, START_MENU_TITLE_POS_Y + i, startMenuTitle[i]);
	}
	centerPrint(hOutput, START_MENU_OPTION_START_POS_Y, startOption[startMenuOptionIndex == 0]);
	centerPrint(hOutput, START_MENU_OPTION_HELP_POS_Y, helpOption[startMenuOptionIndex == 1]);
	centerPrint(hOutput, START_MENU_OPTION_EXIT_POS_Y, exitOption[startMenuOptionIndex == 2]);
}

void setStartMenuOptionIndex(int dir)
{
	startMenuOptionIndex = (startMenuOptionIndex + dir) >= 0 ? (startMenuOptionIndex + dir) % START_MENU_OPTION_NUM : START_MENU_OPTION_NUM - 1;
}

int getStartMenuOptionIndex()
{
	return startMenuOptionIndex;
}

void drawHelpPage()
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < HELP_PAGE_TITLE_HEIGHT; i++)
	{
		centerPrint(hOutput, HELP_TITLE_POS_Y + i * 2, helpTitle[i]);
	}
	centerPrint(hOutput, HELP_PAGE_OPTION_POS_Y, helpPageOption[helpPageOptionIndex]);
}

void setHelpOptionIndex(int dir)
{
	if (helpPageOptionIndex + dir >= 0 && helpPageOptionIndex + dir <= 1)
		helpPageOptionIndex = helpPageOptionIndex + dir;
	else
		printf("\a");
}

int getHelpOptionIndex()
{
	return helpPageOptionIndex;
}

void initBoardDraw()
{
	boardImage = cv::imread(".\\asset\\board.png", cv::IMREAD_UNCHANGED);
	cv::cvtColor(boardImage, boardImage, cv::COLOR_BGRA2RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, boardImage.cols, boardImage.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, boardImage.data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
}

void drawBoard()
{
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, -1.0, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(1.0, -1.0, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 1.0, 0.0);
	glEnd();
	glFlush();
	glutSwapBuffers();
}