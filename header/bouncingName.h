/*
* @file  bouncingName.h
*
* @brief �ʵ������ļ�
*
* @date 2024/11/21
*/
#ifndef __BOUNCING_NAME
#define __BOUNCING_NAME

#include <windows.h>

#define PROGRAMMER_NUM 3
#define MAX_SPEED_INTERVAL 3

unsigned int WINAPI drawName(void* pParam);  // ���ֻ��ƽ��̺���
void initName();                             // ��ʼ�����ֲʵ�

#endif