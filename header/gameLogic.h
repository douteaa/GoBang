/*
* @file  gameLogic.h
*
* @brief 游戏逻辑函数文件
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
}Move;  //一步棋的结构体

bool checkWin(const int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int player);                    // 检测棋盘是否有赢家
void placeChess(int x, int y, int player);                                                           // 下棋
void takeBackChess();                                                                                // 悔棋                                                                           
void clearBoard();                                                                                   // 清空棋盘
void initGame();                                                                                     // 初始化游戏
void setGame(int newGameMode, int newColorTaken, int newDifficult);                                  // 设置游戏
void calculateScore(const int board[BOARD_SIZE][BOARD_SIZE], int score[BOARD_SIZE][BOARD_SIZE]);     // 菜鸟AI棋盘分数计算
unsigned int WINAPI computerAI(void* pParam);                                                        // AI进程主函数
Move getLastMove();                                                                                  // 获得最后一步棋

#endif
