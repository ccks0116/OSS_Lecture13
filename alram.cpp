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
	PlaySound(TEXT(Third_Run), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	while (1)
	{
		int atime;

		printf("�˸��� ���ðڽ��ϱ�?(0�� �Է��Ͻÿ�)\n");
		scanf_s("%d", &atime);
		if (atime == 0)
		{
			PlaySound(NULL, 0, 0);
			Sleep(1000);
			printf("�˶��� �����߽��ϴ�");
			return 0;
		}

	}

}