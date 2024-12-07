#include "soundPlay.h"
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <mmsystem.h>

void programmerBGM(int operation)
{
	if (operation == MUSIC_END)
	{
		PlaySoundW(NULL, NULL, SND_FILENAME);
	}
	else if (operation == MUSIC_START)
	{
		PlaySoundW(L".\\asset\\themeOfHUST.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
}

void goChessSound()
{
	int soundIndex = rand() % GO_CHESS_SOUND_NUM;  // 随机播放下棋音乐
	switch (soundIndex)
	{
		case 0:
			PlaySoundW(L".\\asset\\goChess1.wav", NULL, SND_FILENAME | SND_ASYNC);
			break;
		case 1:
			PlaySoundW(L".\\asset\\goChess2.wav", NULL, SND_FILENAME | SND_ASYNC);
			break;
		case 2:
			PlaySoundW(L".\\asset\\goChess3.wav", NULL, SND_FILENAME | SND_ASYNC);
			break;
	}
}

void gameEndSound(int gameResult)
{
	if (gameResult == GAME_WIN)
	{
		int soundIndex = rand() % GAME_END_SOUND_NUM;  // 随机播放结算音乐
		switch (soundIndex)
		{
			case 0:
			{
				PlaySoundW(L".\\asset\\gameWin.wav", NULL, SND_FILENAME | SND_ASYNC);
				break;
			}
			case 1:
			{
				PlaySoundW(L".\\asset\\gameWin1.wav", NULL, SND_FILENAME | SND_ASYNC);
				break;
			}
		}
		
	}
	else if (gameResult == GAME_LOSE)
	{
		int soundIndex = rand() % GAME_END_SOUND_NUM;  // 随机播放结算音乐
		switch (soundIndex)
		{
			case 0:
			{
				PlaySoundW(L".\\asset\\gameLose.wav", NULL, SND_FILENAME | SND_ASYNC);
				break;
			}
			case 1:
			{
				PlaySoundW(L".\\asset\\gameLose1.wav", NULL, SND_FILENAME | SND_ASYNC);
				break;
			}
		}
	}
}