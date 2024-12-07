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
} programmer[PROGRAMMER_NUM]; // 存储制作人员的结构体

void initName()
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(hOutput, &bInfo);
	int dwSizeX = bInfo.dwSize.X;
	int dwSizeY = bInfo.dwSize.Y;  // 获取当前控制台大小
	srand(time(NULL));
	for (int i = 0; i < PROGRAMMER_NUM; i++)
	{
		int vx, vy;
		do {
			vx = rand() % MAX_SPEED_INTERVAL - MAX_SPEED_INTERVAL / 2;
			vy = rand() % MAX_SPEED_INTERVAL - MAX_SPEED_INTERVAL / 2;
		} while (vx == 0 || vy == 0);  // 确保 vx 和 vy 都不为零

		programmer[i] = { "田露涛", rand() % (dwSizeX - 4), rand() % dwSizeY, vx, vy, FOREGROUND_RED | FOREGROUND_INTENSITY };
	}
	programmer[0].name = "田露涛";
	programmer[1].name = "林益杰";
	programmer[2].name = "蔡林睿";
	programmer[1].color = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	programmer[2].color = FOREGROUND_BLUE | FOREGROUND_INTENSITY;  // 控制制作人员的颜色
}

unsigned int WINAPI drawName(void* pParam)
{
	extern int exitFlag;  // 进程退出标志
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(hOutput, &bInfo);
	int dwSizeX = bInfo.dwSize.X;
	int dwSizeY = bInfo.dwSize.Y;  // 获取当前控制台大小
	while (true)
	{
		// 清除之前的位置
		for (int i = 0; i < PROGRAMMER_NUM; i++)
		{
			gotoxy(hOutput, programmer[i].x, programmer[i].y);
			for (int j = 0; j < strlen(programmer[i].name); j++)
			{
				printf(" ");
			}
		}

		// 更新位置和速度
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

		// 检测碰撞
		for (int i = 0; i < PROGRAMMER_NUM; i++)
		{
			for (int j = i + 1; j < PROGRAMMER_NUM; j++)
			{
				if (abs(programmer[i].x - programmer[j].x) <= 4 && abs(programmer[i].y - programmer[j].y) <= 2)
				{
					// 交换速度方向
					int tempVx = programmer[i].vx;
					int tempVy = programmer[i].vy;
					programmer[i].vx = programmer[j].vx;
					programmer[i].vy = programmer[j].vy;
					programmer[j].vx = tempVx;
					programmer[j].vy = tempVy;
				}
			}
		}

		// 绘制新的位置
		for (int i = 0; i < PROGRAMMER_NUM; i++)
		{
			SetConsoleTextAttribute(hOutput, programmer[i].color);
			gotoxy(hOutput, programmer[i].x, programmer[i].y);
			printf("%s", programmer[i].name);
		}

		// 恢复默认颜色
		SetConsoleTextAttribute(hOutput, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		Sleep(100);  // 控制动画快慢

		if (exitFlag)
		{
			ExitThread(0);  // 退出进程释放资源
		}
	}
	return 0;
}


