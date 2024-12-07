/*
* @file  windowsCtrl.h
*
* @brief ��Ϸ���ڿ����ļ�
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

#define KEY_PRESS(vk) (GetAsyncKeyState(vk)&1?1:0)                // ������ĳ�����Ƿ��µĺ궨��

void initWindows();                                               // ��ʼ������������
void initBoard(int argc, char** argv);                            // ��ʼ����Ϸ����
void gotoxy(HANDLE hOut, int x, int y);                           // ʹ�������ȷ�е�λ��
void centerPrint(HANDLE hOut, int y, const char* str);            // ���д�ӡ�ַ���
void mouseClick(int button, int state, int mouseX, int mouseY);   // ������ص�����
void mouseMotion(int mouseX, int mouseY);                         // ����ƶ��ص�����
void mouseMotionInit();                                           // ����ƶ���س�ʼ��
void keyboardCtrl(unsigned char key, int x, int y);               // ��������ص�����

#endif