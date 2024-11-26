#define GLUT_DISABLE_ATEXIT_HACK
#include "windowsCtrl.h"
#include "bouncingName.h"
#include "draw.h"
#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>

#define EXIT_PAGE -1
#define START_MENU_PAGE 0
#define HELP_PAGE 1
#define PROGRAMMER_PAGE 2
#define GAME_PAGE 3

int onGame = true;
int pageIndex = START_MENU_PAGE;

int main(int argc, char** argv)
{
	while (onGame)
	{
		switch (pageIndex)
		{
			case EXIT_PAGE:
			{
				system("cls");
				exit(0);
			}
			case START_MENU_PAGE:
			{
				system("cls");
				initWindows();
				drawStartMenuPage();
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
				switch (getStartMenuOptionIndex())
				{
				case START_MENU_START_OPTION:
					pageIndex = GAME_PAGE;
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
				HANDLE eggHandle = (HANDLE)_beginthreadex(NULL, 0, drawName, NULL, 0, NULL);
				PlaySoundW(L".\\asset\\themeOfHUST.wav", NULL, SND_FILENAME | SND_ASYNC);
				while (!KEY_PRESS(VK_ESCAPE));
				PlaySoundW(NULL, NULL, SND_FILENAME);
				TerminateThread(eggHandle, 0);
				pageIndex = HELP_PAGE;
				break;
			}
			case GAME_PAGE:
			{
				initBoard(argc, argv);
				initBoardDraw();
				glutDisplayFunc(drawBoard);
				glutMouseFunc(mouseClick);
				glutMainLoop();
				/*system("cls");
				system("game.exe");
				system("pause");
				pageIndex = EXIT_PAGE;*/
				break;
			}
		}
	}
	return 0;
}