// project.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include <stdio.h>
#include "stdafx.h"
#include "stdlib.h"
#include "windows.h"//Sleep(), Beep()�� ����ϱ����� �������
#include "time.h"
#include "conio.h" //_kbhit(),getch()
#include "MMSystem.h"
#pragma comment(lib,"Winmm.lib")

#define Third_Run "C:\\Users\\J\\Documents\\Visual Studio 2015\\Projects\\ConsoleApplication2\\ConsoleApplication2\\alram.wav"

int main(void)
{
	srand(time(NULL));
	int random = rand();
	random = random % 9;

	PlaySound(TEXT(Third_Run), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	while (1)
	{
		int atime;

		printf("�˸��� ���ðڽ��ϱ�?(0~9�� ���Ǽ� ��)\n");
		scanf_s("%d", &atime);
		if (atime == random)
		{
			PlaySound(NULL, 0, 0);
			Sleep(1000);
			printf("�˶��� �����߽��ϴ�");
			return 0;
		}

	}

}