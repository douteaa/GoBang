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

int onGame = true;                 // �ж���Ϸ�Ƿ����
int pageIndex = START_MENU_PAGE;   // ��ǰҳ�������
int gameEnd;                       // �ж���Ϸ�Ƿ����
int exitFlag;                      // �˵������˳���־

int main(int argc, char** argv)
{
	while (onGame)
	{
		switch (pageIndex)
		{
			case EXIT_PAGE:
			{
				system("cls"); // ����
				exit(0);  // �˳�
			}
			case START_MENU_PAGE:
			{
				system("cls");
				initWindows();
				drawStartMenuPage();
				// ���س���ȷ��ѡ��
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
				// ���������л�ҳ��
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
				// ���س���ȷ��ѡ��
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
				// ����ѡ�������л�ҳ��
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
				while (!KEY_PRESS(VK_ESCAPE));  // ����ֱ������Esc��
				programmerBGM(MUSIC_END);
				exitFlag = 1;
				pageIndex = HELP_PAGE;
				break;
			}
			case GAME_SETTING_PAGE:
			{
				int returnKey = false; // �ж��Ƿ񷵻���Ϸ��ʼ����
				system("cls");
				drawGameSettingPage();
				// ���»س���ȷ��ѡ��
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
				// ����ѡ������л�ҳ��
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
				initGame();                                       // ��ʼ����Ϸ
				initBoard(argc, argv);                            // ��ʼ������
				initTexture();                                    // ���ز���
				glutReshapeFunc([](int width, int height) {
					glutReshapeWindow(BOARD_WIDTH, BOARD_HEIGHT); // ���ô��ڴ�С
				});                                               // ���ô��ڴ�С�仯�¼��ص�����
				glutDisplayFunc(drawGamePage);                    // ���ô����ػ�ص�����
				glutMouseFunc(mouseClick);                        // ����������¼��ص�����
				mouseMotionInit();                                // ��ʼ������ƶ��¼�����
				glutPassiveMotionFunc(mouseMotion);               // ��������¼��ص�����
				glutKeyboardFunc(keyboardCtrl);                   // ���ü����¼��ص�����
				glutMainLoop();                                   // ����GLUT�¼���ѭ��
				pageIndex = GAME_SETTING_PAGE;
				gameEnd = true;
				break;
			}
		}
	}
	return 0;
}