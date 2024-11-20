#define GLUT_DISABLE_ATEXIT_HACK
#include "windowsCtrl.h"
#include "draw.h"
#include <Windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <conio.h>


#define EXIT_PAGE -1
#define START_MENU_PAGE 0
#define HELP_PAGE 1
#define GAME_PAGE 2

int onGame = true;
int pageIndex = START_MENU_PAGE;

int main(int argc, char** argv)
{
	while (onGame)
	{
		switch (pageIndex)
		{
		case EXIT_PAGE:
			system("cls");
			exit(0);
		case START_MENU_PAGE:
			initWindows();
			drawStartMenuPage();
			while (!KEY_PRESS(VK_RETURN))
			{
				if (KEY_PRESS(VK_UP))
				{
					setStartMenuOptionIndex(-1);
					drawStartMenuPage();
				}
				else if (KEY_PRESS(VK_DOWN))
				{
					setStartMenuOptionIndex(1);
					drawStartMenuPage();
				}
				Sleep(100);
			}
			switch (getStartMenuOptionIndex())
			{
			case 0:
				pageIndex = GAME_PAGE;
				break;
			case 1:
				pageIndex = HELP_PAGE;
				break;
			case 2:
				pageIndex = EXIT_PAGE;
				break;
			}
			break;
		case HELP_PAGE:
			drawHelpPage();
			while (!KEY_PRESS(VK_RETURN))
			{
				if (KEY_PRESS(VK_LEFT))
				{
					setHelpOptionIndex(-1);
					drawHelpPage();
				}
				else if (KEY_PRESS(VK_RIGHT))
				{
					setHelpOptionIndex(1);
					drawHelpPage();
				}
				Sleep(100);
			}
			pageIndex = START_MENU_PAGE;
			break;
		}
	}
	return 0;
}