#ifndef __DRAW_H
#define __DRAW_H

#define START_MENU_TITLE_POS_Y 0
#define START_MENU_OPTION_START_POS_Y 17
#define START_MENU_OPTION_HELP_POS_Y 20
#define START_MENU_OPTION_EXIT_POS_Y 23
#define START_MENU_OPTION_NUM 3

#define HELP_TITLE_POS_Y 0
#define HELP_PAGE_OPTION_POS_Y 25
#define GELP_PAGE_OPTION_NUM 2

//�йؿ�ʼ������Ƶĺ���
void drawStartMenuPage();
void setStartMenuOptionIndex(int dir);
int getStartMenuOptionIndex();

//�йذ���ҳ����Ƶĺ���
void drawHelpPage();
void setHelpOptionIndex(int dir);
int getHelpOptionIndex();

#endif

