#include <stdio.h>
#include "stdlib.h"
#include "windows.h"//Sleep(), Beep()�� ����ϱ����� �������
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

	printf("�˶��� ��������� ������ �Է��ϼ���!\n");
	printf("%d + %d = ?\n", random[0], random[1]);
	printf("���� �Է�= ");
	scanf("%d", &a);
	while (!((random[0] + random[1]) == a))
	{
		system("cls");
		printf("Ʋ�Ƚ��ϴ�. �ٽ� �Է��ϼ���\n");
		printf("%d + %d = ?\n", random[0], random[1]);
		printf("? �Է�= ");
		scanf("%d", &a);
	}
	printf("�����Դϴ�! �˶��� �����մϴ�.\n");
	PlaySound(NULL, 0, 0);
}