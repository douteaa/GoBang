/*
* @file  soundPlay.h
*
* @brief 音乐播放函数文件
*
* @date 2024/11/30
*/
#ifndef __SOUNDPLAY_H
#define __SOUNDPLAY_H

#define MUSIC_START 1
#define MUSIC_END 0

#define GAME_WIN 1
#define GAME_LOSE 0

#define GO_CHESS_SOUND_NUM 3
#define GAME_END_SOUND_NUM 2

void programmerBGM(int operation);   // 彩蛋界面背景音乐函数
void goChessSound();                 // 下棋音效
void gameEndSound(int gameResult);   // 游戏结算音乐

#endif