#define GLUT_DISABLE_ATEXIT_HACK
#include "windowsCtrl.h"
#include "bouncingName.h"
#include "draw.h"
#include "gameLogic.h"
#include "soundPlay.h"
#include "mainDefine.h"
#include <Windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>

int onGame = true;                 // 判断游戏是否继续
int pageIndex = START_MENU_PAGE;   // 当前页面的索引
int gameEnd;                       // 判断游戏是否结束
int exitFlag;                      // 菜单进程退出标志

int main(int argc, char** argv)
{
	while (onGame)
	{
		switch (pageIndex)
		{
			case EXIT_PAGE:
			{
				system("cls"); // 清屏
				exit(0);  // 退出
			}
			case START_MENU_PAGE:
			{
				system("cls");
				initWindows();
				drawStartMenuPage();
				// 按回车键确定选择
				while (!KEY_PRESS(VK_RETURN))
				{
					if (KEY_PRESS(VK_UP))
					{
						setStartMenuOptionIndex(OPTION_UP);
						drawStartMenuPage();
					}
					else if (KEY_PRESS(VK_DOWN))
					{
						setStartMenuOptionIndex(OPTION_DOWN);
						drawStartMenuPage();
					}
					Sleep(100);
				}
				// 根据索引切换页面
				switch (getStartMenuOptionIndex())
				{
				case START_MENU_START_OPTION:
					pageIndex = GAME_SETTING_PAGE;
					break;
				case START_MENU_HELP_OPTION:
					pageIndex = HELP_PAGE;
					break;
				case START_MENU_EXIT_OPTION:
					pageIndex = EXIT_PAGE;
					break;
				}
				break;
			}
			case HELP_PAGE:
			{
				system("cls");
				drawHelpPage();
				// 按回车键确定选择
				while (!KEY_PRESS(VK_RETURN))
				{
					if (KEY_PRESS(VK_LEFT))
					{
						setHelpOptionIndex(OPTION_LEFT);
						drawHelpPage();
					}
					else if (KEY_PRESS(VK_RIGHT))
					{
						setHelpOptionIndex(OPTION_RIGHT);
						drawHelpPage();
					}
					Sleep(100);
				}
				// 根据选项索引切换页面
				switch (getHelpOptionIndex())
				{
				case HELP_PAGE_RETURN_OPTION:
					pageIndex = START_MENU_PAGE;
					break;
				case HELP_PAGE_PROGRAMMER_OPTION:
					pageIndex = PROGRAMMER_PAGE;
					break;
				}
				break;
			}
			case PROGRAMMER_PAGE:
			{
				system("cls");
				initName();
				exitFlag = 0;
				HANDLE eggHandle = (HANDLE)_beginthreadex(NULL, 0, drawName, NULL, 0, NULL);
				programmerBGM(MUSIC_START);
				while (!KEY_PRESS(VK_ESCAPE));  // 运行直至按下Esc键
				programmerBGM(MUSIC_END);
				exitFlag = 1;
				pageIndex = HELP_PAGE;
				break;
			}
			case GAME_SETTING_PAGE:
			{
				int returnKey = false; // 判断是否返回游戏开始界面
				system("cls");
				drawGameSettingPage();
				// 按下回车键确定选择
				while (!KEY_PRESS(VK_RETURN))
				{
					if (KEY_PRESS(VK_LEFT))
					{
						setGameSettingOptionInnerIndex(OPTION_LEFT);
						drawGameSettingPage();
					}
					else if (KEY_PRESS(VK_RIGHT))
					{
						setGameSettingOptionInnerIndex(OPTION_RIGHT);
						drawGameSettingPage();
					}
					else if (KEY_PRESS(VK_UP))
					{
						setGameSettingOptionIndex(OPTION_UP);
						drawGameSettingPage();
					}
					else if (KEY_PRESS(VK_DOWN))
					{
						setGameSettingOptionIndex(OPTION_DOWN);
						drawGameSettingPage();
					}
					else if (KEY_PRESS(VK_ESCAPE))
					{
						returnKey = 1;
						break;
					}
					else 
						Sleep(100);
				}
				// 根据选择情况切换页面
				if (returnKey)
				{
					pageIndex = START_MENU_PAGE;
					break;
				}
				else
				{
					pageIndex = GAME_PAGE;
					setGame(getGameMode(), getColorTaken(), getDifficult());
				}
				break;
			}
			case GAME_PAGE:
			{
				system("cls");
				gameEnd = false;
				initGame();                                       // 初始化游戏
				initBoard(argc, argv);                            // 初始化棋盘
				initTexture();                                    // 加载材质
				glutReshapeFunc([](int width, int height) {
					glutReshapeWindow(BOARD_WIDTH, BOARD_HEIGHT); // 设置窗口大小
				});                                               // 设置窗口大小变化事件回调函数
				glutDisplayFunc(drawGamePage);                    // 设置窗口重绘回调函数
				glutMouseFunc(mouseClick);                        // 设置鼠标点击事件回调函数
				mouseMotionInit();                                // 初始化鼠标移动事件变量
				glutPassiveMotionFunc(mouseMotion);               // 设置鼠标事件回调函数
				glutKeyboardFunc(keyboardCtrl);                   // 设置键盘事件回调函数
				glutMainLoop();                                   // 进入GLUT事件主循环
				pageIndex = GAME_SETTING_PAGE;
				gameEnd = true;
				break;
			}
		}
	}
	return 0;
}