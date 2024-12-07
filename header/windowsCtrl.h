/*
* @file  windowsCtrl.h
*
* @brief 游戏窗口控制文件
*
* @date 2024/11/21
*/
#ifndef __WINDOWSCTRL_H
#define __WINDOWSCTRL_H

#include <Windows.h>

#define BOARD_POS_X 100
#define BOARD_POS_Y 100
#define BOARD_WIDTH 512
#define BOARD_HEIGHT 512
#define BOARD_MARGIN 31
#define BOARD_GRID_SIZE 32

#define KEY_PRESS(vk) (GetAsyncKeyState(vk)&1?1:0)                // 检测键盘某个键是否按下的宏定义

void initWindows();                                               // 初始化启动器窗口
void initBoard(int argc, char** argv);                            // 初始化游戏界面
void gotoxy(HANDLE hOut, int x, int y);                           // 使光标移向确切的位置
void centerPrint(HANDLE hOut, int y, const char* str);            // 居中打印字符串
void mouseClick(int button, int state, int mouseX, int mouseY);   // 鼠标点击回调函数
void mouseMotion(int mouseX, int mouseY);                         // 鼠标移动回调函数
void mouseMotionInit();                                           // 鼠标移动相关初始化
void keyboardCtrl(unsigned char key, int x, int y);               // 键盘输入回调函数

#endif