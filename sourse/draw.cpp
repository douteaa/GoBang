#include "draw.h"
#include "windowsCtrl.h"
#include <stdio.h>
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <GL/glut.h>

//�йؿ�ʼ����ı���
#define START_MENU_TITLE_HEIGHT 11
int startMenuOptionIndex = 0;
const char startMenuTitle[START_MENU_TITLE_HEIGHT][76] = { "���������������������塡�������������������ӡ������������塡���塡������  ",
                                                           "���������塡�������������������������������ӡ������������塡��������������",
                                                           "���������塡�����������������������������ӡ����������������塡�塡������  ", 
                                                           "���������塡���������������������������ӡ����������������塡������������  ", 
                                                           "�����������������塡�����������������ӡ������������������塡���塡������  ", 
                                                           "�������塡�������塡���������������������������ӡ����������塡����������  ", 
                                                           "�������塡�������塡�����������������ӡ������������������塡���塡������  ", 
                                                           "�������塡�������塡�����������������ӡ��������������塡�塡��������������", 
                                                           "�������塡�������塡�����������������ӡ�������������������                ", 
                                                           "�������塡�������塡�����������������ӡ������������������塡���塡������  ", 
                                                           "���������������������塡�������������ӡ������������������塡�塡����������"};
const char startOption[2][15] = { "   ��ʼ��Ϸ   ", 
								  "-> ��ʼ��Ϸ   "};
const char helpOption[2][15] = { "   �鿴����   ", 
								 "-> �鿴����   "};
const char exitOption[2][15] = { "   �˳���Ϸ   ", 
								 "-> �˳���Ϸ   "};

//�йذ���ҳ��ı���
#define HELP_PAGE_TITLE_HEIGHT 6
int helpPageOptionIndex = 0;
const char helpTitle[HELP_PAGE_TITLE_HEIGHT][63] = { "���������",
								"1.��������һ��˫�˶��ĵĴ�������������Ϸ�����й���ͳ����֮һ��", 
								"2.����������15*15�������Ͻ��еģ�˫���������ӣ��ڷ����С�     ", 
								"3.�ڰ�˫���������ӣ��ڷ����С�                                ", 
								"4.ÿ�����Ӻ󣬶��ֿ���ѡ����壬�������ֿ���ѡ����塣      ", 
                                "5.��һ���ںᡢ����б��������������ʱ����Ϸ������              "};
const char helpPageOption[2][39] = { "-> ���ؿ�ʼ�˵�          ������Ա     ",
									 "   ���ؿ�ʼ�˵�       -> ������Ա     "};

//�й����̵ı���
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