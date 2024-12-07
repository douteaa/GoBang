/*
* @file  draw.h
* 
* @brief 游戏绘制函数文件
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

//有关开始界面绘制的函数
void drawStartMenuPage();                 // 绘制游戏开始页面
void setStartMenuOptionIndex(int dir);    // 更新开始页面按钮的索引
int getStartMenuOptionIndex();            // 获取开始页面按钮的索引

//有关帮助页面绘制的函数
void drawHelpPage();                    // 绘制帮助页面
void setHelpOptionIndex(int dir);       // 更新帮助页面按钮的索引
int getHelpOptionIndex();               // 获得帮助页面按钮的索引

//有关游戏设置页面的函数
void drawGameSettingPage();                    // 绘制游戏设置页面
void setGameSettingOptionIndex(int dir);       // 更新游戏主选项的索引
void setGameSettingOptionInnerIndex(int dir);  // 更新游戏子选项的索引
int getGameMode();                             // 获取游戏的模式
int getColorTaken();                           // 获取玩家执子的颜色
int getDifficult();                            // 获取游戏难度

//有关棋盘绘制的函数
void initTexture();       // 加载材质
void drawBoard();         // 绘制棋盘
void drawChess();         // 绘制棋子
void drawGamePage();      // 页面绘制的主函数

#endif

