#include "gameLogic.h"
#include "draw.h"
#include "windowsCtrl.h"
#include "soundPlay.h"
#include "ChessEngine.h"

#include <stdio.h>
#include <GL/glut.h>
#include <conio.h>
#include <process.h>

int board[BOARD_SIZE][BOARD_SIZE] = { BLANK_BOARD }; // 棋盘
int currentPlayer;                                   // 当前玩家
int gameMode;                                        // 游戏模式
int colorTaken;                                      // 玩家执子颜色
int difficult;                                       // AI难度
int chessTaken;                                      // 判断玩家是否执子
int personChess;                                     // 玩家棋子的颜色
int botChess;                                        // AI棋子的颜色
int chessNum;                                        // 下棋数目
Move history[BOARD_SIZE * BOARD_SIZE];               // 下棋历史记录

void placeChess(int x, int y, int player)
{
    extern int gameEnd;
    if (board[x][y] != BLANK_BOARD && board[x][y] != FAKE_CHESS)
    {
        printf("\a该位置已有棋子，不能下棋！\n");
		return;  // 如果该位置已有棋子，则不能下棋
    }
	history[chessNum].x = x;
	history[chessNum].y = y;  // 记录下棋位置
	chessNum++;  // 更新下棋数目
    board[x][y] = player;  // 更新棋盘状态
	goChessSound();
    printf("%s在(%d, %d)处落棋\n", player == BLACK_CHESS ? "黑棋" : "白棋", x, y);  // 日志打印
	if (checkWin(board, x, y, player))
	{
        gameEnd = true;
		if (gameMode == TWO_PLAYER_BATTLE_MODE) gameEndSound(GAME_WIN);
		else
		{
			if (player == personChess)gameEndSound(GAME_WIN);
			else gameEndSound(GAME_LOSE);  // 播放游戏结算音乐
		}
		printf("%d子连一线！%s获胜！\n", WIN_LINE, player == BLACK_CHESS ? "黑棋" : "白棋");
		printf("按r重新开始游戏，按q返回游戏设置界面\n");
	}
	else if (chessNum == BOARD_SIZE * BOARD_SIZE)
	{
		gameEnd = true;
		gameEndSound(GAME_WIN);
		printf("棋盘已满，平局！\n");
		printf("按r重新开始游戏，按q返回游戏设置界面\n");  // 游戏平局
	}
	if (currentPlayer == BLACK_CHESS)
	{
		currentPlayer = WHITE_CHESS;
	}
	else
	{
		currentPlayer = BLACK_CHESS;  // 执子玩家切换
	}
	if(gameMode != TWO_PLAYER_BATTLE_MODE)chessTaken = chessTaken ? false : true;  // 人机对弈模式下切换玩家是否执子
}

void takeBackChess()
{
	// 悔棋超限
	if (chessNum <= 1)
	{
		printf("无棋可悔！\n");
		return;
	}
	chessNum--;
	board[history[chessNum].x][history[chessNum].y] = BLANK_BOARD;
	chessNum--;
	board[history[chessNum].x][history[chessNum].y] = BLANK_BOARD; // 连续悔两步棋
	printf("%s悔棋成功！\n", currentPlayer == BLACK_CHESS ? "黑棋" : "白棋");
}

bool checkWin(const int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int player) {
    int count;

    // 水平方向
    count = 1;
    for (int i = 1; i < WIN_LINE; ++i) 
	{
        if (x + i < BOARD_SIZE && board[x + i][y] == player) ++count;  // 向右检查
        else break;
    }
    for (int i = 1; i < WIN_LINE; ++i) 
	{
        if (x - i >= 0 && board[x - i][y] == player) ++count;  // 向左检查
        else break;
    }
    if (count >= WIN_LINE) return true;  // 如果连续棋子数达到胜利条件

    // 垂直方向
    count = 1;
    for (int i = 1; i < WIN_LINE; ++i) 
	{
        if (y + i < BOARD_SIZE && board[x][y + i] == player) ++count;  // 向下检查
        else break;
    }
    for (int i = 1; i < WIN_LINE; ++i) 
	{
        if (y - i >= 0 && board[x][y - i] == player) ++count;  // 向上检查
        else break;
    }
    if (count >= WIN_LINE) return true;  // 如果连续棋子数达到胜利条件

    // 主对角线方向（从左上到右下）
    count = 1;
    for (int i = 1; i < WIN_LINE; ++i) 
	{
        if (x + i < BOARD_SIZE && y + i < BOARD_SIZE && board[x + i][y + i] == player) ++count;  // 右下方检查
        else break;
    }
    for (int i = 1; i < WIN_LINE; ++i) 
	{
        if (x - i >= 0 && y - i >= 0 && board[x - i][y - i] == player) ++count;  // 左上方检查
        else break;
    }
    if (count >= WIN_LINE) return true;  // 如果连续棋子数达到胜利条件

    // 副对角线方向（从右上到左下）
    count = 1;
    for (int i = 1; i < WIN_LINE; ++i) 
	{
        if (x + i < BOARD_SIZE && y - i >= 0 && board[x + i][y - i] == player) ++count;  // 左下方检查
        else break;
    }
    for (int i = 1; i < WIN_LINE; ++i) 
	{
        if (x - i >= 0 && y + i < BOARD_SIZE && board[x - i][y + i] == player) ++count;  // 右上方检查
        else break;
    }
    if (count >= WIN_LINE) return true;  // 如果连续棋子数达到胜利条件

    return false;  // 没有玩家获胜
}

void clearBoard()
{
	// 遍历清空棋盘
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            board[i][j] = BLANK_BOARD;
        }
    }
}

void initGame()
{
	printf("游戏初始化...\n");
	clearBoard();  // 清空棋盘
	currentPlayer = BLACK_CHESS;  // 黑棋先行
	chessNum = 0;  // 重置棋数
	if (gameMode == HUMAN_AI_BATTLE_MODE)
	{
		personChess = colorTaken + 1;
		botChess = BLACK_CHESS + WHITE_CHESS - personChess;  // 计算人机各自的执子颜色
		HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, computerAI, NULL, 0, NULL);  // 创建AI进程
		// 设置执子情况
		switch (personChess)
		{
			case BLACK_CHESS:
			{
				chessTaken = true;
				break;
			}
			case WHITE_CHESS:
			{
				chessTaken = false;
				break;
			}
		}
		// 初始化大师AI
		if (difficult == MASTER_AI)
		{
			ChessEngine::beforeStart();
			ChessEngine::reset(colorTaken);
		}
	}
	else chessTaken = true;  // 双人对弈时始终执子
    printf("游戏开始！\n");
}

void setGame(int newGameMode, int newColorTaken, int newDifficult)
{
	gameMode = newGameMode;
	colorTaken = newColorTaken;
	difficult = newDifficult;  // 设置游戏各项参数
}

unsigned int WINAPI computerAI(void* pParam)
{
	extern int gameEnd;  // 进程退出标志
	while (!gameEnd)
	{
		if (currentPlayer != botChess)
		{
			Sleep(100);
			continue;  // 未轮到自己时等待
		}
		printf("思考中...\n");
		switch (difficult)
		{
			// 菜鸟AI
			case 0:
			{
				int startChess[3] = {6, 7, 8};
				int score[BOARD_SIZE][BOARD_SIZE] = { 0 };
				int bestX = startChess[rand() % 3], bestY = startChess[rand() % 3];  // 起始位置
				calculateScore(board, score);  // 棋盘分数计算
				for (int i = 0; i < BOARD_SIZE; i++)
				{
					for (int j = 0; j < BOARD_SIZE; j++)
					{
						if (score[i][j] > score[bestX][bestY])
						{
							bestX = i;
							bestY = j;  // 更新最好下棋位置
						}
					}
				}
				Sleep(1000);
				placeChess(bestX, bestY, currentPlayer);  // 下棋
				break;
			}
			case 1:
			{
				if (chessNum > 0)
				{
					Move laastMove = getLastMove();
					ChessEngine::nextStep(laastMove.x, laastMove.y);  // 向大师AI推送玩家的下棋位置
				}
				ChessEngine::Position AIresult = ChessEngine::getLastPosition();  // 获得大师AI下棋的位置
				Sleep(1000);
				placeChess(AIresult.x, AIresult.y, botChess);  // 下棋
				break;
			}
		}
	}
	return 0;
}

Move getLastMove()
{
	// 返回最后一步棋的位置
	return history[chessNum - 1];
}

void calculateScore(const int board[BOARD_SIZE][BOARD_SIZE], int score[BOARD_SIZE][BOARD_SIZE])
{
	//统计玩家或AI连子
	int personNum = 0;    //玩家
	int botNum = 0;   //AI
	int emptyNum = 0; //各方向空白位数

	for (int row = 0; row < BOARD_SIZE; row++) 
	{
		for (int col = 0; col < BOARD_SIZE; col++) 
		{
			//判断空白点
			if (row >= 0 && col >= 0 && board[row][col] == 0) 
			{
				//遍历四个方向，然后分别计算正反四个方向
				int directs[4][2] = { {1,0}, {1,1}, {0,1}, {-1,1} };

				for (int k = 0; k < 4; k++) 
				{
					int x = directs[k][0];
					int y = directs[k][1];

					//重置
					personNum = 0;
					botNum = 0;
					emptyNum = 0;

					//对玩家评分(正向)
					for (int i = 1; i <= 4; i++) 
					{
						if (row + i * y >= 0 && row + i * y < BOARD_SIZE && col + i * x >= 0 && col + i * x < BOARD_SIZE && board[row + i * y][col + i * x] == personChess) {
							//玩家的子
							personNum++;

						}
						else if (row + i * y >= 0 && row + i * y < BOARD_SIZE && col + i * x >= 0 && col + i * x < BOARD_SIZE && board[row + i * y][col + i * x] == 0) 
						{
							//空白位
							emptyNum++;
							break;    //遇到空白位置停止该方向搜索

						}
						else 
						{
							break;    //出边界或遇到白棋停止搜索
						}


					}

					//对玩家评分(反向)
					for (int i = 1; i <= 4; i++) 
					{
						if (row - i * y >= 0 && row - i * y < BOARD_SIZE && col - i * x >= 0 && col - i * x < BOARD_SIZE && board[row - i * y][col - i * x] == personChess)
						{
							personNum++;
						}
						else if (row - i * y >= 0 && row - i * y < BOARD_SIZE && col - i * x >= 0 && col - i * x < BOARD_SIZE && board[row - i * y][col - i * x] == 0) 
						{
							emptyNum++;
							break;
						}
						else 
						{
							break;
						}
					}

					if (personNum == 1) 
					{
						score[row][col] += 10;
					}
					else if (personNum == 2) 
					{
						if (emptyNum == 1) 
						{
							//死3
							score[row][col] += 30;
						}
						else if (emptyNum == 2) 
						{
							//活3
							score[row][col] += 40;
						}
					}
					else if (personNum == 3) 
					{
						if (emptyNum == 1) {
							//死4
							score[row][col] += 60;
						}
						else if (emptyNum == 2) 
						{
							//活4
							score[row][col] += 200;
						}
					}
					else if (personNum == 4) {
						score[row][col] += 20000;
					}
					emptyNum = 0; //清空

					//对电脑评分（正向）
					for (int i = 1; i <= 4; i++) 
					{
						if (row + i * y > 0 && row + i * y < BOARD_SIZE && col + i * x > 0 && col + i * x < BOARD_SIZE && board[row + i * y][col + i * x == botChess])
						{
							botNum++;
						}
						else if (row + i * y > 0 && row + i * y < BOARD_SIZE && col + i * x > 0 && col + i * x < BOARD_SIZE && board[row + i * y][col + i * x] == 0) 
						{
							emptyNum++;
							break;
						}
						else 
						{
							break;
						}
					}
					//对电脑评分(反向)
					for (int i = 1; i <= 4; i++) 
					{
						if (row - i * y > 0 && row - i * y < BOARD_SIZE && col - i * x > 0 && col - i * x < BOARD_SIZE && board[row - i * y][col - i * x] == botChess) 
						{
							botNum++;
						}
						else if (row - i * y > 0 && row - i * y < BOARD_SIZE && col - i * x > 0 && col - i * x < BOARD_SIZE && board[row - i * y][col - i * x] == 0) 
						{
							emptyNum++;
							break;
						}
						else 
						{
							break;    //出边界
						}
					}

					if (botNum == 0) 
					{
						//连1
						score[row][col] += 5;
					}
					else if (botNum == 1) 
					{
						//活2
						score[row][col] += 10;
					}
					else if (botNum == 2) 
					{
						if (emptyNum == 1) 
						{
							//死3
							score[row][col] += 25;
						}
						else if (emptyNum == 2) 
						{
							//活3
							score[row][col] += 50;
						}
					}
					else if (botNum == 3) 
					{
						if (emptyNum == 1) 
						{
							//死4
							score[row][col] += 55;
						}
						else if (botNum == 2) 
						{
							//活4
							score[row][col] += 300;
						}
					}
					else if (botNum >= 4) 
					{
						//活5
						score[row][col] += 20000;
					}
				}
			}
		}
	}
}