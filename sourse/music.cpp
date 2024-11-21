#include "music.h"

unsigned int WINAPI themeOfHUST(void* pParam)
{
	Beep(DO, TICK / 2);
	Sleep(INTERVAL / 2);
	Beep(MI, TICK / 2);
	Sleep(INTERVAL / 2);
	Beep(SO, TICK / 4 * 3);
	Sleep(INTERVAL / 4 * 3);
	Beep(LA, TICK / 4);
	Sleep(INTERVAL / 4);
	Beep(SO, TICK);
	Sleep(INTERVAL);
	Beep(MI, TICK / 2);
	Sleep(INTERVAL / 2);
	Beep(SO, TICK / 2);
	Sleep(INTERVAL / 2);
	Beep(HDO, TICK / 4 * 3);
	Sleep(INTERVAL / 4 * 3);
	Beep(HRE, TICK / 4);
	Sleep(INTERVAL / 4);
	Beep(HMI, TICK);
	Sleep(INTERVAL);
	Beep(HRE, TICK / 2);
	Sleep(INTERVAL / 2);
	Beep(HDO, TICK / 2);
	Sleep(INTERVAL / 2);
	Beep(LA, TICK);
	Sleep(INTERVAL);
	Beep(SO, TICK);
	Sleep(INTERVAL);
	Beep(HMI, TICK);
	Sleep(INTERVAL);
	Beep(HRE, TICK);
	Sleep(INTERVAL);
	Beep(HDO, TICK);
	Sleep(INTERVAL);
	Beep(HDO, TICK / 4 * 3);
	Sleep(INTERVAL / 4 * 3);
	Beep(HDO, TICK / 4);
	Sleep(INTERVAL / 4);
	Beep(HDO, TICK);
	Sleep(INTERVAL);
	return 0;
}