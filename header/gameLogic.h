/*
* @file  gameLogic.h
*
* @brief ��Ϸ�߼������ļ�
*
* @date 2024/11/26
*/
#ifndef __GAME_LOGIC_H
#define __GAME_LOGIC_H

#define FAKE_CHESS -1
#define BLANK_BOARD 0
#define BLACK_CHESS 1
#define WHITE_CHESS 2

#define BOARD_SIZE 15
#define CHESS_SIZE 16
#define WIN_LINE 5

#define TWO_PLAYER_BATTLE_MODE 0
#define HUMAN_AI_BATTLE_MODE 1

#define NEWBIE_AI 0
#define MASTER_AI 1

#include <Windows.h>

typedef struct MoveStruct
{
	int x;
	int y;
}Move;  //һ����Ľṹ��

bool checkWin(const int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int player);                    // ��������Ƿ���Ӯ��
void placeChess(int x, int y, int player);                                                           // ����
void takeBackChess();                                                                                // ����                                                                           
void clearBoard();                                                                                   // �������
void initGame();                                                                                     // ��ʼ����Ϸ
void setGame(int newGameMode, int newColorTaken, int newDifficult);                                  // ������Ϸ
void calculateScore(const int board[BOARD_SIZE][BOARD_SIZE], int score[BOARD_SIZE][BOARD_SIZE]);     // ����AI���̷�������
unsigned int WINAPI computerAI(void* pParam);                                                        // AI����������
Move getLastMove();                                                                                  // ������һ����

#endif
