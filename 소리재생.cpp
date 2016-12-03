#include <stdio.h>
#include "stdlib.h"
#include "windows.h"//Sleep(), Beep()를 사용하기위한 헤더파일
#include "time.h"
#include "conio.h" //_kbhit(),getch()
#include "MMSystem.h"
#pragma comment(lib,"Winmm.lib")

#define Third_Run "C:\\alarm.wav"

int main()
{
	srand((unsigned)time(NULL));
	int random[2] = { rand()%10+1,rand() % 10 + 1};
	int a = 0;

	PlaySound(TEXT(Third_Run), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	printf("알람을 끄고싶으면 정답을 입력하세요!\n");
	printf("%d + %d = ?\n", random[0], random[1]);
	printf("정답 입력= ");
	scanf("%d", &a);
	while (!((random[0] + random[1]) == a))
	{
		system("cls");
		printf("틀렸습니다. 다시 입력하세요\n");
		printf("%d + %d = ?\n", random[0], random[1]);
		printf("? 입력= ");
		scanf("%d", &a);
	}
	printf("정답입니다! 알람을 종료합니다.\n");
	PlaySound(NULL, 0, 0);
}