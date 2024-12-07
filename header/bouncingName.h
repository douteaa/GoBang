/*
* @file  bouncingName.h
*
* @brief 彩蛋函数文件
*
* @date 2024/11/21
*/
#ifndef __BOUNCING_NAME
#define __BOUNCING_NAME

#include <windows.h>

#define PROGRAMMER_NUM 3
#define MAX_SPEED_INTERVAL 3

unsigned int WINAPI drawName(void* pParam);  // 名字绘制进程函数
void initName();                             // 初始化名字彩蛋

#endif