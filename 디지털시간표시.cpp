#include <stdio.h>
#include "stdlib.h"
#include "windows.h"
#include "time.h"
#include "conio.h" //_kbhit(),getch()를 사용하기위한 헤더파일
#define MAX 10
#define map_x 22
#define map_y 9

void gotoxy(int x, int y);
void TimePrint(int pos, int num);
void ColonPrint(int num);
void MapPrint();

int sx[6] = { 0,8,20,28,40,48 };
int sx2[2] = { 20,40 };
int change = 0;
// -------------------------------------------
int number_[MAX][5][3] = {
	{
		{ 1,1,1 },
		{ 1,0,1 },
		{ 1,0,1 }, // 0
		{ 1,0,1 },
		{ 1,1,1 }
	},
	{
		{ 1,1,0 },
		{ 0,1,0 },
		{ 0,1,0 }, // 1
		{ 0,1,0 },
		{ 1,1,1 }
	},
	{
		{ 1,1,1 },
		{ 0,0,1 },
		{ 1,1,1 }, // 2
		{ 1,0,0 },
		{ 1,1,1 }
	},
	{
		{ 1,1,1 },
		{ 0,0,1 },
		{ 1,1,1 }, // 3
		{ 0,0,1 },
		{ 1,1,1 }
	},
	{
		{ 1,0,1 },
		{ 1,0,1 },
		{ 1,1,1 }, // 4
		{ 0,0,1 },
		{ 0,0,1 }
	},
	{
		{ 1,1,1 },
		{ 1,0,0 },
		{ 1,1,1 }, // 5
		{ 0,0,1 },
		{ 1,1,1 }
	},
	{
		{ 1,0,0 },
		{ 1,0,0 },
		{ 1,1,1 }, // 6
		{ 1,0,1 },
		{ 1,1,1 }
	},
	{
		{ 1,1,1 },
		{ 1,0,1 },
		{ 0,0,1 }, // 7
		{ 0,0,1 },
		{ 0,0,1 }
	},
	{
		{ 1,1,1 },
		{ 1,0,1 },
		{ 1,1,1 }, // 8
		{ 1,0,1 },
		{ 1,1,1 }
	},
	{
		{ 1,1,1 },
		{ 1,0,1 },
		{ 1,1,1 }, // 9
		{ 0,0,1 },
		{ 0,0,1 }
	},
};

int colon_[2][5][1] = {
	{
		{ 0 },
		{ 1 },
		{ 0 },
		{ 1 },
		{ 0 }
	},
	{
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 }
	}
};
int map_[map_y][map_x] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 1, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 1, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 1, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 1, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 1, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 1, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 1, 0 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1, 1, 1 }
};
//---------------------------------------------------------------

int main()
{
	int x = 0, y = 0;
	int count = 0;
	int i = 0;
	

	while (1)
	{
		struct tm *t;
		time_t timer;
		timer = time(NULL);
		t = localtime(&timer);

		MapPrint();

		TimePrint(0, (t->tm_hour / 10)); // 시(10)
		TimePrint(1, (t->tm_hour % 10)); // 시(0)
		TimePrint(2, (t->tm_min / 10)); // 분(10)
		TimePrint(3, (t->tm_min % 10)); // 분(0)

		ColonPrint(0);

		Sleep(1000);
		change++;
		system("cls");
	}
}

void TimePrint(int pos, int num)
{
	int x=0, y=0, count=0;
	for (y = 0; y < 5; y++)
	{
		for (x = 0; x < 3; x++)
		{
			gotoxy(sx[pos] + (x+2)* 2, y+2);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
			if (number_[num][y][x] == 1)
				printf("■");
			count++;
			if (number_[num][y][x] == 0)
				printf("　");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		printf("\n"); // 3칸마다 줄바꿈
	}
	printf("\n");
}
void ColonPrint(int num)
{
	int x = 0, y = 0;
	for (y = 0; y < 5; y++)
	{
		for (x = 0; x < 1; x++)
		{
			if (change > 1) { change = 0; }
			gotoxy(sx2[num], y+2);
			if (colon_[change][y][x] == 1)
				printf("■");
			if (colon_[change][y][x] == 0)
				printf("　");
		}
		printf("\n");
	}
}
void MapPrint()
{
	int x = 0, y = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	for (y = 0; y < map_y; y++)
	{
		for (x = 0; x < map_x; x++)
		{
			if (map_[y][x] == 1)
				printf("■");
			if (map_[y][x] == 0)
				printf("  ");
		}
		printf("\n");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
