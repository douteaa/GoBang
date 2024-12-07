#include "bouncingName.h"
#include "windowsCtrl.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <stdlib.h>

struct
{
	const char* name;
	int x;
	int y;
	int vx;
	int vy;
	WORD color;
} programmer[PROGRAMMER_NUM]; // �洢������Ա�Ľṹ��

void initName()
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(hOutput, &bInfo);
	int dwSizeX = bInfo.dwSize.X;
	int dwSizeY = bInfo.dwSize.Y;  // ��ȡ��ǰ����̨��С
	srand(time(NULL));
	for (int i = 0; i < PROGRAMMER_NUM; i++)
	{
		int vx, vy;
		do {
			vx = rand() % MAX_SPEED_INTERVAL - MAX_SPEED_INTERVAL / 2;
			vy = rand() % MAX_SPEED_INTERVAL - MAX_SPEED_INTERVAL / 2;
		} while (vx == 0 || vy == 0);  // ȷ�� vx �� vy ����Ϊ��

		programmer[i] = { "��¶��", rand() % (dwSizeX - 4), rand() % dwSizeY, vx, vy, FOREGROUND_RED | FOREGROUND_INTENSITY };
	}
	programmer[0].name = "��¶��";
	programmer[1].name = "�����";
	programmer[2].name = "�����";
	programmer[1].color = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	programmer[2].color = FOREGROUND_BLUE | FOREGROUND_INTENSITY;  // ����������Ա����ɫ
}

unsigned int WINAPI drawName(void* pParam)
{
	extern int exitFlag;  // �����˳���־
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(hOutput, &bInfo);
	int dwSizeX = bInfo.dwSize.X;
	int dwSizeY = bInfo.dwSize.Y;  // ��ȡ��ǰ����̨��С
	while (true)
	{
		// ���֮ǰ��λ��
		for (int i = 0; i < PROGRAMMER_NUM; i++)
		{
			gotoxy(hOutput, programmer[i].x, programmer[i].y);
			for (int j = 0; j < strlen(programmer[i].name); j++)
			{
				printf(" ");
			}
		}

		// ����λ�ú��ٶ�
		for (int i = 0; i < PROGRAMMER_NUM; i++)
		{
			programmer[i].x += programmer[i].vx;
			programmer[i].y += programmer[i].vy;
			if (programmer[i].x < 0 || programmer[i].x + strlen(programmer[i].name) >= dwSizeX)
			{
				programmer[i].vx = - programmer[i].vx;
				programmer[i].x += programmer[i].vx;
			}
			if (programmer[i].y < 0 || programmer[i].y >= dwSizeY)
			{
				programmer[i].vy = - programmer[i].vy;
				programmer[i].y += programmer[i].vy;
			}
		}

		// �����ײ
		for (int i = 0; i < PROGRAMMER_NUM; i++)
		{
			for (int j = i + 1; j < PROGRAMMER_NUM; j++)
			{
				if (abs(programmer[i].x - programmer[j].x) <= 4 && abs(programmer[i].y - programmer[j].y) <= 2)
				{
					// �����ٶȷ���
					int tempVx = programmer[i].vx;
					int tempVy = programmer[i].vy;
					programmer[i].vx = programmer[j].vx;
					programmer[i].vy = programmer[j].vy;
					programmer[j].vx = tempVx;
					programmer[j].vy = tempVy;
				}
			}
		}

		// �����µ�λ��
		for (int i = 0; i < PROGRAMMER_NUM; i++)
		{
			SetConsoleTextAttribute(hOutput, programmer[i].color);
			gotoxy(hOutput, programmer[i].x, programmer[i].y);
			printf("%s", programmer[i].name);
		}

		// �ָ�Ĭ����ɫ
		SetConsoleTextAttribute(hOutput, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		Sleep(100);  // ���ƶ�������

		if (exitFlag)
		{
			ExitThread(0);  // �˳������ͷ���Դ
		}
	}
	return 0;
}


