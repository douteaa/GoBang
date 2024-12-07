#include "draw.h"
#include "windowsCtrl.h"
#include "gameLogic.h"
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
													 "2.����������15*15�������Ͻ��еģ�˫���������ӣ��������У�     ", 
													 "3.ÿ�����Ӻ󣬿��԰�������Ҽ�ѡ����壻                      ", 
													 "4.��һ���ںᡢ����б��������������ʱ����Ϸ������              ", 
													 "5.��Ϸ�����󣬰�r�����¿�ʼ����q��������Ϸ���ý��档          "};
const char helpPageOption[HELP_PAGE_OPTION_NUM][39] = { "-> ���ؿ�ʼ�˵�          ������Ա     ",
														"   ���ؿ�ʼ�˵�       -> ������Ա     "};

//�й���Ϸ����ҳ��ı���
int gameSettingOptionIndex = 0;
int gameModeOptionIndex = 0;
int colorTakenOptionIndex = 0;
int difficultOptionIndex = 0;
const char gameModeOption[2][2][40] = { {"   ��Ϸģʽ�� -> ˫�˲���      �˻���ս",
										 "  ��Ϸģʽ��    ˫�˲���   -> �˻���ս"},
										{"�� ��Ϸģʽ�� -> ˫�˲���      �˻���ս",
										 "�� ��Ϸģʽ��    ˫�˲���   -> �˻���ս"} };
const char colorTakenOption[2][2][40] = { {"  ִ����ɫ�� -> ����          ����    ",
										   "  ִ����ɫ��    ����       -> ����    "},
										  {"�� ִ����ɫ�� -> ����          ����    ",
										   "�� ִ����ɫ��    ����       -> ����    "} };
const char difficultOption[2][2][40] = { {"  ��Ϸ�Ѷȣ� -> ����          ��ʦ    ",
										  "  ��Ϸ�Ѷȣ�    ����       -> ��ʦ    "},
										 {"�� ��Ϸ�Ѷȣ� -> ����          ��ʦ    ",
										  "�� ��Ϸ�Ѷȣ�    ����       -> ��ʦ    "} };
const char blanketOption[40] = { "                                       " };
const char tips[3][32] = { "-----���س�����ʼ��Ϸ�ɣ� -----",
						   "-----��Esc�����ؿ�ʼ���棡-----" };

//�й����̵ı���
cv::Mat boardImage;           // ����ͼƬ
cv::Mat blackChessImage;      // ����ͼƬ
cv::Mat whiteChessImage;      // ����ͼƬ
cv::Mat blackChessLastImage;  // ��Ǻ���ͼƬ
cv::Mat whiteChessLastImage;  // ��ǰ���ͼƬ
GLuint boardTexture;          // ���̲���
GLuint blackChessTexture;     // �������
GLuint whiteChessTexture;     // �������
GLuint blackChessLastTexture; // ��Ǻ������
GLuint whiteChessLastTexture; // ��ǰ������

void drawStartMenuPage()
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	// ��ӡ��ʼ�������
	for (int i = 0; i < START_MENU_TITLE_HEIGHT; i++)
	{
		centerPrint(hOutput, START_MENU_TITLE_POS_Y + i, startMenuTitle[i]);
	}
	// ��ӡ��ʼ����ѡ��
	centerPrint(hOutput, START_MENU_OPTION_START_POS_Y, startOption[startMenuOptionIndex == 0]);
	centerPrint(hOutput, START_MENU_OPTION_HELP_POS_Y, helpOption[startMenuOptionIndex == 1]);
	centerPrint(hOutput, START_MENU_OPTION_EXIT_POS_Y, exitOption[startMenuOptionIndex == 2]);
}

void setStartMenuOptionIndex(int dir)
{
	// ���ÿ�ʼҳ��ѡ�������
	startMenuOptionIndex = (startMenuOptionIndex + dir) >= 0 ? (startMenuOptionIndex + dir) % START_MENU_OPTION_NUM : START_MENU_OPTION_NUM - 1;
}

int getStartMenuOptionIndex()
{
	// ���ؿ�ʼ����ѡ�������
	return startMenuOptionIndex;
}

void drawHelpPage()
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	// ��ӡ�����������
	for (int i = 0; i < HELP_PAGE_TITLE_HEIGHT; i++)
	{
		centerPrint(hOutput, HELP_TITLE_POS_Y + i * 2, helpTitle[i]);
	}
	// ��ӡ����ҳ��ѡ��
	centerPrint(hOutput, HELP_PAGE_OPTION_POS_Y, helpPageOption[helpPageOptionIndex]);
}

void setHelpOptionIndex(int dir)
{	
	// ���ð���ҳ��ѡ������
	if (helpPageOptionIndex + dir >= 0 && helpPageOptionIndex + dir <= 1)
		helpPageOptionIndex = helpPageOptionIndex + dir;
	else
		printf("\a"); // ���޾���
}

int getHelpOptionIndex()
{
	// ���ذ���ҳ��ѡ������
	return helpPageOptionIndex;
}

void drawGameSettingPage()
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	// ��ӡ��Ϸ����ҳ�����
	centerPrint(hOutput, START_MENU_TITLE_POS_Y, "��Ϸ����");
	// ��ӡ��Ϸ����ҳ���һ��ѡ��
	centerPrint(hOutput, GAME_GAME_MODE_OPTION_POS_Y, gameModeOption[gameSettingOptionIndex == 0][gameModeOptionIndex]);
	// �˻�����ģʽ�Ż���ʾ����ѡ��
	if (gameModeOptionIndex == 1)
	{
		centerPrint(hOutput, GAME_COLOR_TAKEN_OPTION_POS_Y, colorTakenOption[gameSettingOptionIndex == 1][colorTakenOptionIndex]);
		centerPrint(hOutput, GAME_DIFFICULT_OPTION_POS_Y, difficultOption[gameSettingOptionIndex == 2][difficultOptionIndex]);
	}
	else
	{
		centerPrint(hOutput, GAME_COLOR_TAKEN_OPTION_POS_Y, blanketOption);
		centerPrint(hOutput, GAME_DIFFICULT_OPTION_POS_Y, blanketOption);
	}
	// ��ӡ��Ϸ����ҳ����ʾ
	for (int i = 0; i < GAME_SETTING_PAGE_TIPS_NUM; i++)
	{
		centerPrint(hOutput, GAME_SETTING_PAGE_TIPS_POS_Y + i * 2, tips[i]);
	}
}

void setGameSettingOptionIndex(int dir)
{
	// ����һ��ѡ������
	if (gameModeOptionIndex == 0 || (gameSettingOptionIndex + dir < 0 && gameSettingOptionIndex + dir >= GAME_SETTING_OPTION_NUM)) printf("\a");  // ���޾���
	else
	{
		gameSettingOptionIndex = (gameSettingOptionIndex + dir) >= 0 ? ((gameSettingOptionIndex + dir) % GAME_SETTING_OPTION_NUM) : GAME_SETTING_OPTION_NUM - 1;
	}
}

void setGameSettingOptionInnerIndex(int dir)
{
	// ���ö���ѡ������
	switch (gameSettingOptionIndex)
	{
		case 0: 
		{
			if (gameModeOptionIndex + dir < 0 || gameModeOptionIndex + dir >= GAME_SETTING_INNER_OPTION_NUM) printf("\a");
			else gameModeOptionIndex = gameModeOptionIndex + dir;
			break;
		}
		case 1:
		{
			if (colorTakenOptionIndex + dir < 0 || colorTakenOptionIndex + dir >= GAME_SETTING_INNER_OPTION_NUM) printf("\a");
			else colorTakenOptionIndex = colorTakenOptionIndex + dir;
			break;
		}
		case 2:
		{
			if (difficultOptionIndex + dir < 0 || difficultOptionIndex + dir >= GAME_SETTING_INNER_OPTION_NUM) printf("\a");
			else difficultOptionIndex = difficultOptionIndex + dir;
			break;
		}
	}
}

int getGameMode()
{
	// ������Ϸģʽ
	return gameModeOptionIndex;
}

int getColorTaken()
{
	// ����ִ����ɫ
	return colorTakenOptionIndex;
}

int getDifficult()
{
	// ������Ϸ�Ѷ�
	return difficultOptionIndex;
}

void initTexture()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);  //����2D�����Լ�͸��ɫ���


	// ��������ͼƬ������
	boardImage = cv::imread(".\\asset\\board.png", cv::IMREAD_UNCHANGED);  // ��ȡ����ͼƬ
	cv::cvtColor(boardImage, boardImage, cv::COLOR_BGRA2RGBA);  // ����ͼƬ��ɫ����ΪOpenGl����ʶ��ĸ�ʽ
	glGenTextures(1, &boardTexture);  // �󶨲���ID
	glBindTexture(GL_TEXTURE_2D, boardTexture);  // ���ò��� 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // ���ò��ʲ���ģʽ
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, boardImage.cols, boardImage.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, boardImage.data);  // ����2D����

	// ���غ���ͼƬ������
	blackChessImage = cv::imread(".\\asset\\blackChess.png", cv::IMREAD_UNCHANGED);
	cv::cvtColor(blackChessImage, blackChessImage, cv::COLOR_BGRA2RGBA);
	glGenTextures(1, &blackChessTexture);
	glBindTexture(GL_TEXTURE_2D, blackChessTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, blackChessImage.cols, blackChessImage.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, blackChessImage.data);

	// ���ذ���ͼƬ������
	whiteChessImage = cv::imread(".\\asset\\whiteChess.png", cv::IMREAD_UNCHANGED);
	cv::cvtColor(whiteChessImage, whiteChessImage, cv::COLOR_BGRA2RGBA);
	glGenTextures(1, &whiteChessTexture);
	glBindTexture(GL_TEXTURE_2D, whiteChessTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, whiteChessImage.cols, whiteChessImage.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, whiteChessImage.data);

	// ���ر�Ǻ���ͼƬ������
	blackChessLastImage = cv::imread(".\\asset\\blackChessLast.png", cv::IMREAD_UNCHANGED);
	cv::cvtColor(blackChessLastImage, blackChessLastImage, cv::COLOR_BGRA2RGBA);
	glGenTextures(1, &blackChessLastTexture);
	glBindTexture(GL_TEXTURE_2D, blackChessLastTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, blackChessLastImage.cols, blackChessLastImage.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, blackChessLastImage.data);

	// ���ر�ǰ���ͼƬ������
	whiteChessLastImage = cv::imread(".\\asset\\whiteChessLast.png", cv::IMREAD_UNCHANGED);
	cv::cvtColor(blackChessLastImage, blackChessLastImage, cv::COLOR_BGRA2RGBA);
	glGenTextures(1, &whiteChessLastTexture);
	glBindTexture(GL_TEXTURE_2D, whiteChessLastTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, whiteChessLastImage.cols, whiteChessLastImage.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, whiteChessLastImage.data);
}

void drawBoard()
{
	glBindTexture(GL_TEXTURE_2D, boardTexture);  // �������̲���
	glBegin(GL_QUADS);  // ���λ���ģʽ
	glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, -1.0, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(1.0, -1.0, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 1.0, 0.0);  // ָ�����������Լ���������
	glEnd();
	glFlush();  // ǿ�����л�ͼָ�����
}

void drawChess()
{
	extern int chessTaken;
	extern int gameMode;
	extern int board[BOARD_SIZE][BOARD_SIZE];
	extern int currentPlayer;
	extern int gameEnd;
	extern int chessNum;
	glBindTexture(GL_TEXTURE_2D, blackChessTexture);  //���ú������
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == 1)
			{
				double centerX = BOARD_MARGIN + i * BOARD_GRID_SIZE;
				double centerY = BOARD_MARGIN + j * BOARD_GRID_SIZE;  // �����λ����Ļ�ϵ�����
				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex3f(-1.0 + (centerX - CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY - CHESS_SIZE) / 512.0 * 2, 0.0);
				glTexCoord2f(0.0, 1.0); glVertex3f(-1.0 + (centerX - CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY + CHESS_SIZE) / 512.0 * 2, 0.0);
				glTexCoord2f(1.0, 1.0); glVertex3f(-1.0 + (centerX + CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY + CHESS_SIZE) / 512.0 * 2, 0.0);
				glTexCoord2f(1.0, 0.0); glVertex3f(-1.0 + (centerX + CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY - CHESS_SIZE) / 512.0 * 2, 0.0);
				glEnd();
			}
		}
	}
	glFlush();

	glBindTexture(GL_TEXTURE_2D, whiteChessTexture);  // ���ð������
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == 2)
			{
				double centerX = BOARD_MARGIN + i * BOARD_GRID_SIZE;
				double centerY = BOARD_MARGIN + j * BOARD_GRID_SIZE;
				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex3f(-1.0 + (centerX - CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY - CHESS_SIZE) / 512.0 * 2, 0.0);
				glTexCoord2f(0.0, 1.0); glVertex3f(-1.0 + (centerX - CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY + CHESS_SIZE) / 512.0 * 2, 0.0);
				glTexCoord2f(1.0, 1.0); glVertex3f(-1.0 + (centerX + CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY + CHESS_SIZE) / 512.0 * 2, 0.0);
				glTexCoord2f(1.0, 0.0); glVertex3f(-1.0 + (centerX + CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY - CHESS_SIZE) / 512.0 * 2, 0.0);
				glEnd();
			}
		}
	}
	glFlush();

	if (chessNum > 0)
	{
		Move lastMove = getLastMove();  // ������һ���������
		if(board[lastMove.x][lastMove.y] == BLACK_CHESS)
			glBindTexture(GL_TEXTURE_2D, blackChessLastTexture);
		else
			glBindTexture(GL_TEXTURE_2D, whiteChessLastTexture);  // ������Ӧ���ӵı�ǲ���
		double centerX = BOARD_MARGIN + lastMove.x * BOARD_GRID_SIZE;
		double centerY = BOARD_MARGIN + lastMove.y * BOARD_GRID_SIZE;
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(-1.0 + (centerX - CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY - CHESS_SIZE) / 512.0 * 2, 0.0);
		glTexCoord2f(0.0, 1.0); glVertex3f(-1.0 + (centerX - CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY + CHESS_SIZE) / 512.0 * 2, 0.0);
		glTexCoord2f(1.0, 1.0); glVertex3f(-1.0 + (centerX + CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY + CHESS_SIZE) / 512.0 * 2, 0.0);
		glTexCoord2f(1.0, 0.0); glVertex3f(-1.0 + (centerX + CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY - CHESS_SIZE) / 512.0 * 2, 0.0);
		glEnd();
	}
	glFlush();

	if (gameMode != 0 && !chessTaken || gameEnd) return;  // ֻ����Ϸû�������˻�����ʱ�ֵ��������Ż���͸������
	switch (currentPlayer)
	{
		case BLACK_CHESS:
		{
			glBindTexture(GL_TEXTURE_2D, blackChessTexture);
			break;
		}
		case WHITE_CHESS:
		{
			glBindTexture(GL_TEXTURE_2D, whiteChessTexture);  // ������Ӧ��ɫ�����Ӳ���
			break;
		}
	}
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == -1)
			{
				GLfloat trueColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
				GLfloat falseColor[] = { 1.0f, 1.0f, 1.0f, 0.5f };  // ���ð�͸��ɫ
				glColor4fv(falseColor);
				double centerX = BOARD_MARGIN + i * BOARD_GRID_SIZE;
				double centerY = BOARD_MARGIN + j * BOARD_GRID_SIZE;
				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex3f(-1.0 + (centerX - CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY - CHESS_SIZE) / 512.0 * 2, 0.0);
				glTexCoord2f(0.0, 1.0); glVertex3f(-1.0 + (centerX - CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY + CHESS_SIZE) / 512.0 * 2, 0.0);
				glTexCoord2f(1.0, 1.0); glVertex3f(-1.0 + (centerX + CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY + CHESS_SIZE) / 512.0 * 2, 0.0);
				glTexCoord2f(1.0, 0.0); glVertex3f(-1.0 + (centerX + CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY - CHESS_SIZE) / 512.0 * 2, 0.0);
				glEnd();
				glFlush();
				glColor4fv(trueColor);  // �ָ�ԭ�е���ɫ
				return;
			}	
		}
}

void drawGamePage()
{
	drawBoard();        // ��������
	drawChess();        // ��������
	glutSwapBuffers();  // ����������ʹ����������ʾ����Ļ��
}