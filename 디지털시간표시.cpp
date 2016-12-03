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

int sx[6] = { 0,8,20,28,40,48 }; // gotoxy로 쓸 좌표 (0 8 은 시간, 20 28은 분 40 48은 초 이지만 초까지는 출력 x)
int sx2[2] = { 20,40 }; // 콜론(:) 출력 자리이지만 초단위 사용 안하기때문에 수정됨
int change = 0; // 콜론(:) 깜빡임 변수
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
		{ 0 },  // 00 : 00 할때 : 를 표시할때는 colon_[0], 아무것도 표시 안할때는 colon_[1]
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
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 1, 0 }, // 디지털숫자로 표시되는 시계 테두리 출력
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

		MapPrint(); // 맵테두리 출력

		TimePrint(0, (t->tm_hour / 10)); // 시(10단위)
		TimePrint(1, (t->tm_hour % 10)); // 시(0단위)
		TimePrint(2, (t->tm_min / 10)); // 분(10단위)
		TimePrint(3, (t->tm_min % 10)); // 분(0단위)


		ColonPrint(0); // 콜론(:)함수 실행 00:00

		Sleep(1000);
		change++; // change 값을 변화시킴으로써 콜론(:) 깜빡임 조절
		system("cls");
	}
}

void TimePrint(int pos, int num) // 현재시간을 디지털숫자로 표시하는 함수
{
	int x=0, y=0, count=0;
	for (y = 0; y < 5; y++)
	{
		for (x = 0; x < 3; x++)
		{
			gotoxy(sx[pos] + (x+2)* 2, y+2); // gotoxy()함수로 숫자 출력할 곳 조절
			if (number_[num][y][x] == 1) // 19번째 라인에 설정해둔 배열의 값이 1이면 눈에보이는 네모 표시 출력 0이면 안보이는 네모 출력
				printf("■");
			count++;
			if (number_[num][y][x] == 0)
				printf("　"); // 공백x 안보이는 네모
		}
		printf("\n"); // 3칸마다 줄바꿈
	}
	printf("\n");
}
void ColonPrint(int num) // 00 : 00 일때 :표시하는 함수
{
	int x = 0, y = 0;
	for (y = 0; y < 5; y++)
	{
		for (x = 0; x < 1; x++)
		{
			if (change > 1) { change = 0; } // 145번째 라인에 있는 sleep(1000) 초마다 change 값 변화 1이면 표시 0이면 표시x
			gotoxy(sx2[num], y+2);
			if (colon_[change][y][x] == 1)
				printf("■");
			if (colon_[change][y][x] == 0)
				printf("　");
		}
		printf("\n");
	}
}
void MapPrint() // 맵테두리 출력 함수
{
	int x = 0, y = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1); // 글씨색 바꾸는 함수 7이 기본값
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

void gotoxy(int x, int y) // xy좌표 이동 함수
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
