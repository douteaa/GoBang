#ifndef __DRAW_H
#define __DRAW_H

#define OPTION_UP -1
#define OPTION_LEFT -1
#define OPTION_DOWN 1
#define OPTION_RIGHT 1

#define START_MENU_TITLE_POS_Y 0
#define START_MENU_OPTION_START_POS_Y 17
#define START_MENU_OPTION_HELP_POS_Y 20
#define START_MENU_OPTION_EXIT_POS_Y 23
#define START_MENU_OPTION_NUM 3
#define START_MENU_START_OPTION 0
#define START_MENU_HELP_OPTION 1
#define START_MENU_EXIT_OPTION 2

#define HELP_TITLE_POS_Y 0
#define HELP_PAGE_OPTION_POS_Y 25
#define HELP_PAGE_RETURN_OPTION 0
#define HELP_PAGE_PROGRAMMER_OPTION 1

//有关开始界面绘制的函数
void drawStartMenuPage();
void setStartMenuOptionIndex(int dir);
int getStartMenuOptionIndex();

//有关帮助页面绘制的函数
void drawHelpPage();
void setHelpOptionIndex(int dir);
int getHelpOptionIndex();

//有关棋盘绘制的函数
void initBoardDraw();
void drawBoard();

#endif

