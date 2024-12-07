#define GLUT_DISABLE_ATEXIT_HACK
#include "windowsCtrl.h"
#include "gameLogic.h"
#include "ChessEngine.h"
#include <gl/freeglut.h>
#include <stdio.h>

int onChessX; 
int onChessY; // 透明棋子的位置

void initWindows()
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hOutput, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(hOutput, &CursorInfo); // 设置控制台光标隐藏
}

void initBoard(int argc, char** argv)
{
	extern int gameMode;
	extern int difficult;
	char title[50];
	snprintf(title, 50, "五子棋-%s-%s", gameMode == TWO_PLAYER_BATTLE_MODE ? "双人对弈" : "人机对战", difficult == NEWBIE_AI ? "菜鸟" : "大师");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // 设置双缓冲模式和绘制颜色模式
	glutInitWindowSize(BOARD_WIDTH, BOARD_HEIGHT);  // 设置窗口的大小
	glutInitWindowPosition(BOARD_POS_X, BOARD_POS_Y); // 设置窗口的位置
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION); // 设置窗口关闭后的行为
	glutCreateWindow(title);  // 创建窗口
}

void gotoxy(HANDLE hOut, int x, int y)
{
	COORD pos;
	pos.X = x; //横坐标
	pos.Y = y; //纵坐标
	SetConsoleCursorPosition(hOut, pos);  // 设置光标位置
}

void centerPrint(HANDLE hOut, int y, const char* str)
{
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(hOut, &bInfo);
	int dwSizeX = bInfo.dwSize.X;  // 获得控制台大小
	int len = strlen(str);
	int x = dwSizeX / 2 - len / 2;
	gotoxy(hOut, x, y);  // 设置光标位置
	printf("%s", str);  // 打印字符串 
}

void mouseClick(int button, int state, int mouseX, int mouseY)
{
	extern int gameMode;
	extern int chessTaken;
	extern int gameEnd;
	extern int board[BOARD_SIZE][BOARD_SIZE];
	extern int currentPlayer;
	extern int difficult;
	if (gameEnd || !chessTaken) return;  // 只有游戏没有结束以及执子时才能操作
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		int gridX = (mouseX - BOARD_MARGIN + BOARD_GRID_SIZE / 2) / BOARD_GRID_SIZE;
		int gridY = (mouseY - BOARD_MARGIN + BOARD_GRID_SIZE / 2) / BOARD_GRID_SIZE;
		if(gridX >= 0 && gridX < BOARD_SIZE && gridY >= 0 && gridY < BOARD_SIZE)
			placeChess(gridX, gridY, currentPlayer);  // 下棋
		
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		int gridX = (mouseX - BOARD_MARGIN + BOARD_GRID_SIZE / 2) / BOARD_GRID_SIZE;
		int gridY = (mouseY - BOARD_MARGIN + BOARD_GRID_SIZE / 2) / BOARD_GRID_SIZE;
		if (gridX >= 0 && gridX < BOARD_SIZE && gridY >= 0 && gridY < BOARD_SIZE)
		{
			// 悔棋
			takeBackChess();
			if (gameMode == HUMAN_AI_BATTLE_MODE && difficult == MASTER_AI)
			{
				ChessEngine::takeBack();
			}
		}
	}
}

void mouseMotionInit()
{
	// 初始化透明棋子的初始位置
	extern int board[BOARD_SIZE][BOARD_SIZE];
	onChessX = 0;
	onChessY = 0;
	board[onChessX][onChessY] = -1;
}

void mouseMotion(int mouseX, int mouseY)
{
	extern int board[BOARD_SIZE][BOARD_SIZE];
	int gridX = (mouseX - BOARD_MARGIN + BOARD_GRID_SIZE / 2) / BOARD_GRID_SIZE;
	int gridY = (mouseY - BOARD_MARGIN + BOARD_GRID_SIZE / 2) / BOARD_GRID_SIZE;
	if (gridX >= 0 && gridX < BOARD_SIZE && gridY >= 0 && gridY < BOARD_SIZE && board[gridX][gridY] == 0)
	{
		if(board[onChessX][onChessY] == -1) board[onChessX][onChessY] = 0;
		onChessX = gridX;
		onChessY = gridY;
		board[onChessX][onChessY] = -1; // 更新透明棋子的位置
	}
}

void keyboardCtrl(unsigned char key, int x, int y)
{
	extern int gameEnd;
	if (gameEnd)
	{
		switch (key)
		{
			case 'r':
			{
				extern int difficult;
				extern int colorTaken;
				extern int gameMode;
				if (gameMode == HUMAN_AI_BATTLE_MODE && difficult == MASTER_AI)
					ChessEngine::reset(colorTaken == 1 ? 1 : 0);
				clearBoard(); // 清空棋盘
				initGame(); // 初始化游戏
				gameEnd = 0;  // 退出电脑AI进程
				break;
			}
			case 'q':
			{
				glutLeaveMainLoop();  // 退出GLUT事件循环
				break;
			}
		}
	}
}