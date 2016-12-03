// project.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include <stdio.h>
#include "stdafx.h"
#include "stdlib.h"
#include "windows.h"//Sleep(), Beep()를 사용하기위한 헤더파일
#include "time.h"
#include "conio.h" //_kbhit(),getch()
#include "MMSystem.h"
#pragma comment(lib,"Winmm.lib")

#define Third_Run "C:\\Users\\J\\Documents\\Visual Studio 2015\\Projects\\ConsoleApplication2\\ConsoleApplication2\\alram.wav"

int main(void)
{
	PlaySound(TEXT(Third_Run), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	while (1)
	{
		int atime;

		printf("알림을 끄시겠습니까?(0을 입력하시오)\n");
		scanf_s("%d", &atime);
		if (atime == 0)
		{
			PlaySound(NULL, 0, 0);
			Sleep(1000);
			printf("알람을 종료했습니다");
			return 0;
		}

	}

}