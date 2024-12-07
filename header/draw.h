/*
* @file  draw.h
* 
* @brief ��Ϸ���ƺ����ļ�
* 
* @date 2024/11/19
*/

#ifndef __DRAW_H
#define __DRAW_H

#define OPTION_UP -1
#define OPTION_LEFT -1
#define OPTION_DOWN 1
#define OPTION_RIGHT 1

#define START_MENU_TITLE_POS_Y 1
#define START_MENU_OPTION_START_POS_Y 18
#define START_MENU_OPTION_HELP_POS_Y 21
#define START_MENU_OPTION_EXIT_POS_Y 24
#define START_MENU_OPTION_NUM 3
#define START_MENU_START_OPTION 0
#define START_MENU_HELP_OPTION 1
#define START_MENU_EXIT_OPTION 2

#define GAME_SETTING_TITLE_POS_Y 1
#define GAME_SETTING_OPTION_NUM 3
#define GAME_SETTING_INNER_OPTION_NUM 2
#define GAME_GAME_MODE_OPTION_POS_Y 7
#define GAME_COLOR_TAKEN_OPTION_POS_Y 10
#define GAME_DIFFICULT_OPTION_POS_Y 12
#define GAME_SETTING_PAGE_TIPS_POS_Y 25
#define GAME_SETTING_PAGE_TIPS_NUM 2

#define HELP_TITLE_POS_Y 0
#define HELP_PAGE_OPTION_POS_Y 25
#define HELP_PAGE_OPTION_NUM 2
#define HELP_PAGE_RETURN_OPTION 0
#define HELP_PAGE_PROGRAMMER_OPTION 1

#define TIP_LINE_LENGTH 50

//�йؿ�ʼ������Ƶĺ���
void drawStartMenuPage();                 // ������Ϸ��ʼҳ��
void setStartMenuOptionIndex(int dir);    // ���¿�ʼҳ�水ť������
int getStartMenuOptionIndex();            // ��ȡ��ʼҳ�水ť������

//�йذ���ҳ����Ƶĺ���
void drawHelpPage();                    // ���ư���ҳ��
void setHelpOptionIndex(int dir);       // ���°���ҳ�水ť������
int getHelpOptionIndex();               // ��ð���ҳ�水ť������

//�й���Ϸ����ҳ��ĺ���
void drawGameSettingPage();                    // ������Ϸ����ҳ��
void setGameSettingOptionIndex(int dir);       // ������Ϸ��ѡ�������
void setGameSettingOptionInnerIndex(int dir);  // ������Ϸ��ѡ�������
int getGameMode();                             // ��ȡ��Ϸ��ģʽ
int getColorTaken();                           // ��ȡ���ִ�ӵ���ɫ
int getDifficult();                            // ��ȡ��Ϸ�Ѷ�

//�й����̻��Ƶĺ���
void initTexture();       // ���ز���
void drawBoard();         // ��������
void drawChess();         // ��������
void drawGamePage();      // ҳ����Ƶ�������

#endif

