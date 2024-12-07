#include "gameLogic.h"
#include "draw.h"
#include "windowsCtrl.h"
#include "soundPlay.h"
#include "ChessEngine.h"

#include <stdio.h>
#include <GL/glut.h>
#include <conio.h>
#include <process.h>

int board[BOARD_SIZE][BOARD_SIZE] = { BLANK_BOARD }; // ����
int currentPlayer;                                   // ��ǰ���
int gameMode;                                        // ��Ϸģʽ
int colorTaken;                                      // ���ִ����ɫ
int difficult;                                       // AI�Ѷ�
int chessTaken;                                      // �ж�����Ƿ�ִ��
int personChess;                                     // ������ӵ���ɫ
int botChess;                                        // AI���ӵ���ɫ
int chessNum;                                        // ������Ŀ
Move history[BOARD_SIZE * BOARD_SIZE];               // ������ʷ��¼

void placeChess(int x, int y, int player)
{
    extern int gameEnd;
    if (board[x][y] != BLANK_BOARD && board[x][y] != FAKE_CHESS)
    {
        printf("\a��λ���������ӣ��������壡\n");
		return;  // �����λ���������ӣ���������
    }
	history[chessNum].x = x;
	history[chessNum].y = y;  // ��¼����λ��
	chessNum++;  // ����������Ŀ
    board[x][y] = player;  // ��������״̬
	goChessSound();
    printf("%s��(%d, %d)������\n", player == BLACK_CHESS ? "����" : "����", x, y);  // ��־��ӡ
	if (checkWin(board, x, y, player))
	{
        gameEnd = true;
		if (gameMode == TWO_PLAYER_BATTLE_MODE) gameEndSound(GAME_WIN);
		else
		{
			if (player == personChess)gameEndSound(GAME_WIN);
			else gameEndSound(GAME_LOSE);  // ������Ϸ��������
		}
		printf("%d����һ�ߣ�%s��ʤ��\n", WIN_LINE, player == BLACK_CHESS ? "����" : "����");
		printf("��r���¿�ʼ��Ϸ����q������Ϸ���ý���\n");
	}
	else if (chessNum == BOARD_SIZE * BOARD_SIZE)
	{
		gameEnd = true;
		gameEndSound(GAME_WIN);
		printf("����������ƽ�֣�\n");
		printf("��r���¿�ʼ��Ϸ����q������Ϸ���ý���\n");  // ��Ϸƽ��
	}
	if (currentPlayer == BLACK_CHESS)
	{
		currentPlayer = WHITE_CHESS;
	}
	else
	{
		currentPlayer = BLACK_CHESS;  // ִ������л�
	}
	if(gameMode != TWO_PLAYER_BATTLE_MODE)chessTaken = chessTaken ? false : true;  // �˻�����ģʽ���л�����Ƿ�ִ��
}

void takeBackChess()
{
	// ���峬��
	if (chessNum <= 1)
	{
		printf("����ɻڣ�\n");
		return;
	}
	chessNum--;
	board[history[chessNum].x][history[chessNum].y] = BLANK_BOARD;
	chessNum--;
	board[history[chessNum].x][history[chessNum].y] = BLANK_BOARD; // ������������
	printf("%s����ɹ���\n", currentPlayer == BLACK_CHESS ? "����" : "����");
}

bool checkWin(const int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int player) {
    int count;

    // ˮƽ����
    count = 1;
    for (int i = 1; i < WIN_LINE; ++i) 
	{
        if (x + i < BOARD_SIZE && board[x + i][y] == player) ++count;  // ���Ҽ��
        else break;
    }
    for (int i = 1; i < WIN_LINE; ++i) 
	{
        if (x - i >= 0 && board[x - i][y] == player) ++count;  // ������
        else break;
    }
    if (count >= WIN_LINE) return true;  // ��������������ﵽʤ������

    // ��ֱ����
    count = 1;
    for (int i = 1; i < WIN_LINE; ++i) 
	{
        if (y + i < BOARD_SIZE && board[x][y + i] == player) ++count;  // ���¼��
        else break;
    }
    for (int i = 1; i < WIN_LINE; ++i) 
	{
        if (y - i >= 0 && board[x][y - i] == player) ++count;  // ���ϼ��
        else break;
    }
    if (count >= WIN_LINE) return true;  // ��������������ﵽʤ������

    // ���Խ��߷��򣨴����ϵ����£�
    count = 1;
    for (int i = 1; i < WIN_LINE; ++i) 
	{
        if (x + i < BOARD_SIZE && y + i < BOARD_SIZE && board[x + i][y + i] == player) ++count;  // ���·����
        else break;
    }
    for (int i = 1; i < WIN_LINE; ++i) 
	{
        if (x - i >= 0 && y - i >= 0 && board[x - i][y - i] == player) ++count;  // ���Ϸ����
        else break;
    }
    if (count >= WIN_LINE) return true;  // ��������������ﵽʤ������

    // ���Խ��߷��򣨴����ϵ����£�
    count = 1;
    for (int i = 1; i < WIN_LINE; ++i) 
	{
        if (x + i < BOARD_SIZE && y - i >= 0 && board[x + i][y - i] == player) ++count;  // ���·����
        else break;
    }
    for (int i = 1; i < WIN_LINE; ++i) 
	{
        if (x - i >= 0 && y + i < BOARD_SIZE && board[x - i][y + i] == player) ++count;  // ���Ϸ����
        else break;
    }
    if (count >= WIN_LINE) return true;  // ��������������ﵽʤ������

    return false;  // û����һ�ʤ
}

void clearBoard()
{
	// �����������
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
	printf("��Ϸ��ʼ��...\n");
	clearBoard();  // �������
	currentPlayer = BLACK_CHESS;  // ��������
	chessNum = 0;  // ��������
	if (gameMode == HUMAN_AI_BATTLE_MODE)
	{
		personChess = colorTaken + 1;
		botChess = BLACK_CHESS + WHITE_CHESS - personChess;  // �����˻����Ե�ִ����ɫ
		HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, computerAI, NULL, 0, NULL);  // ����AI����
		// ����ִ�����
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
		// ��ʼ����ʦAI
		if (difficult == MASTER_AI)
		{
			ChessEngine::beforeStart();
			ChessEngine::reset(colorTaken);
		}
	}
	else chessTaken = true;  // ˫�˶���ʱʼ��ִ��
    printf("��Ϸ��ʼ��\n");
}

void setGame(int newGameMode, int newColorTaken, int newDifficult)
{
	gameMode = newGameMode;
	colorTaken = newColorTaken;
	difficult = newDifficult;  // ������Ϸ�������
}

unsigned int WINAPI computerAI(void* pParam)
{
	extern int gameEnd;  // �����˳���־
	while (!gameEnd)
	{
		if (currentPlayer != botChess)
		{
			Sleep(100);
			continue;  // δ�ֵ��Լ�ʱ�ȴ�
		}
		printf("˼����...\n");
		switch (difficult)
		{
			// ����AI
			case 0:
			{
				int startChess[3] = {6, 7, 8};
				int score[BOARD_SIZE][BOARD_SIZE] = { 0 };
				int bestX = startChess[rand() % 3], bestY = startChess[rand() % 3];  // ��ʼλ��
				calculateScore(board, score);  // ���̷�������
				for (int i = 0; i < BOARD_SIZE; i++)
				{
					for (int j = 0; j < BOARD_SIZE; j++)
					{
						if (score[i][j] > score[bestX][bestY])
						{
							bestX = i;
							bestY = j;  // �����������λ��
						}
					}
				}
				Sleep(1000);
				placeChess(bestX, bestY, currentPlayer);  // ����
				break;
			}
			case 1:
			{
				if (chessNum > 0)
				{
					Move laastMove = getLastMove();
					ChessEngine::nextStep(laastMove.x, laastMove.y);  // ���ʦAI������ҵ�����λ��
				}
				ChessEngine::Position AIresult = ChessEngine::getLastPosition();  // ��ô�ʦAI�����λ��
				Sleep(1000);
				placeChess(AIresult.x, AIresult.y, botChess);  // ����
				break;
			}
		}
	}
	return 0;
}

Move getLastMove()
{
	// �������һ�����λ��
	return history[chessNum - 1];
}

void calculateScore(const int board[BOARD_SIZE][BOARD_SIZE], int score[BOARD_SIZE][BOARD_SIZE])
{
	//ͳ����һ�AI����
	int personNum = 0;    //���
	int botNum = 0;   //AI
	int emptyNum = 0; //������հ�λ��

	for (int row = 0; row < BOARD_SIZE; row++) 
	{
		for (int col = 0; col < BOARD_SIZE; col++) 
		{
			//�жϿհ׵�
			if (row >= 0 && col >= 0 && board[row][col] == 0) 
			{
				//�����ĸ�����Ȼ��ֱ���������ĸ�����
				int directs[4][2] = { {1,0}, {1,1}, {0,1}, {-1,1} };

				for (int k = 0; k < 4; k++) 
				{
					int x = directs[k][0];
					int y = directs[k][1];

					//����
					personNum = 0;
					botNum = 0;
					emptyNum = 0;

					//���������(����)
					for (int i = 1; i <= 4; i++) 
					{
						if (row + i * y >= 0 && row + i * y < BOARD_SIZE && col + i * x >= 0 && col + i * x < BOARD_SIZE && board[row + i * y][col + i * x] == personChess) {
							//��ҵ���
							personNum++;

						}
						else if (row + i * y >= 0 && row + i * y < BOARD_SIZE && col + i * x >= 0 && col + i * x < BOARD_SIZE && board[row + i * y][col + i * x] == 0) 
						{
							//�հ�λ
							emptyNum++;
							break;    //�����հ�λ��ֹͣ�÷�������

						}
						else 
						{
							break;    //���߽����������ֹͣ����
						}


					}

					//���������(����)
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
							//��3
							score[row][col] += 30;
						}
						else if (emptyNum == 2) 
						{
							//��3
							score[row][col] += 40;
						}
					}
					else if (personNum == 3) 
					{
						if (emptyNum == 1) {
							//��4
							score[row][col] += 60;
						}
						else if (emptyNum == 2) 
						{
							//��4
							score[row][col] += 200;
						}
					}
					else if (personNum == 4) {
						score[row][col] += 20000;
					}
					emptyNum = 0; //���

					//�Ե������֣�����
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
					//�Ե�������(����)
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
							break;    //���߽�
						}
					}

					if (botNum == 0) 
					{
						//��1
						score[row][col] += 5;
					}
					else if (botNum == 1) 
					{
						//��2
						score[row][col] += 10;
					}
					else if (botNum == 2) 
					{
						if (emptyNum == 1) 
						{
							//��3
							score[row][col] += 25;
						}
						else if (emptyNum == 2) 
						{
							//��3
							score[row][col] += 50;
						}
					}
					else if (botNum == 3) 
					{
						if (emptyNum == 1) 
						{
							//��4
							score[row][col] += 55;
						}
						else if (botNum == 2) 
						{
							//��4
							score[row][col] += 300;
						}
					}
					else if (botNum >= 4) 
					{
						//��5
						score[row][col] += 20000;
					}
				}
			}
		}
	}
}