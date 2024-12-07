#define GLUT_DISABLE_ATEXIT_HACK
#include "windowsCtrl.h"
#include "gameLogic.h"
#include "ChessEngine.h"
#include <gl/freeglut.h>
#include <stdio.h>

int onChessX; 
int onChessY; // ͸�����ӵ�λ��

void initWindows()
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hOutput, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(hOutput, &CursorInfo); // ���ÿ���̨�������
}

void initBoard(int argc, char** argv)
{
	extern int gameMode;
	extern int difficult;
	char title[50];
	snprintf(title, 50, "������-%s-%s", gameMode == TWO_PLAYER_BATTLE_MODE ? "˫�˶���" : "�˻���ս", difficult == NEWBIE_AI ? "����" : "��ʦ");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // ����˫����ģʽ�ͻ�����ɫģʽ
	glutInitWindowSize(BOARD_WIDTH, BOARD_HEIGHT);  // ���ô��ڵĴ�С
	glutInitWindowPosition(BOARD_POS_X, BOARD_POS_Y); // ���ô��ڵ�λ��
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION); // ���ô��ڹرպ����Ϊ
	glutCreateWindow(title);  // ��������
}

void gotoxy(HANDLE hOut, int x, int y)
{
	COORD pos;
	pos.X = x; //������
	pos.Y = y; //������
	SetConsoleCursorPosition(hOut, pos);  // ���ù��λ��
}

void centerPrint(HANDLE hOut, int y, const char* str)
{
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(hOut, &bInfo);
	int dwSizeX = bInfo.dwSize.X;  // ��ÿ���̨��С
	int len = strlen(str);
	int x = dwSizeX / 2 - len / 2;
	gotoxy(hOut, x, y);  // ���ù��λ��
	printf("%s", str);  // ��ӡ�ַ��� 
}

void mouseClick(int button, int state, int mouseX, int mouseY)
{
	extern int gameMode;
	extern int chessTaken;
	extern int gameEnd;
	extern int board[BOARD_SIZE][BOARD_SIZE];
	extern int currentPlayer;
	extern int difficult;
	if (gameEnd || !chessTaken) return;  // ֻ����Ϸû�н����Լ�ִ��ʱ���ܲ���
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		int gridX = (mouseX - BOARD_MARGIN + BOARD_GRID_SIZE / 2) / BOARD_GRID_SIZE;
		int gridY = (mouseY - BOARD_MARGIN + BOARD_GRID_SIZE / 2) / BOARD_GRID_SIZE;
		if(gridX >= 0 && gridX < BOARD_SIZE && gridY >= 0 && gridY < BOARD_SIZE)
			placeChess(gridX, gridY, currentPlayer);  // ����
		
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		int gridX = (mouseX - BOARD_MARGIN + BOARD_GRID_SIZE / 2) / BOARD_GRID_SIZE;
		int gridY = (mouseY - BOARD_MARGIN + BOARD_GRID_SIZE / 2) / BOARD_GRID_SIZE;
		if (gridX >= 0 && gridX < BOARD_SIZE && gridY >= 0 && gridY < BOARD_SIZE)
		{
			// ����
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
	// ��ʼ��͸�����ӵĳ�ʼλ��
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
		board[onChessX][onChessY] = -1; // ����͸�����ӵ�λ��
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
				clearBoard(); // �������
				initGame(); // ��ʼ����Ϸ
				gameEnd = 0;  // �˳�����AI����
				break;
			}
			case 'q':
			{
				glutLeaveMainLoop();  // �˳�GLUT�¼�ѭ��
				break;
			}
		}
	}
}