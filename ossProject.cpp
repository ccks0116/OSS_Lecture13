#include "stdafx.h"
#include "stdlib.h"
#include "windows.h"//Sleep(), Beep()를 사용하기위한 헤더파일
#include "time.h"
#include "conio.h" //_kbhit(),getch()
#include "MMSystem.h" // PlaySound() 함수 실행하기 위한 헤더파일
#include <iostream>
#include <fstream>
#pragma comment(lib,"Winmm.lib")

#define ESC 27
#define MAX 10
#define Third_Run "alram.wav"

using namespace std;

int c = 0; //clock()로 받은 값을 저장
int m = 0, h = 0, s = 0; // 경괴시간 분, 시
int state = NULL; // 키입력 상태
int endProgram = 1; //프로그램 종료
int alarm = 3600;// 초로 환산한 알람시간
int sx[6] = { 0, 8, 20, 28, 40, 48 }; // gotoxy로 쓸 좌표 (0 8 은 시간, 20 28은 분 40 48은 초 이지만 초까지는 출력 x)
int sx2[2] = { 16 }; // 콜론(:) 출력

int number_[MAX][5][3] = {
	{
		{ 1, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 0, 1 }, // 0
		{ 1, 0, 1 },
		{ 1, 1, 1 }
	},
	{
		{ 1, 1, 0 },
		{ 0, 1, 0 },
		{ 0, 1, 0 }, // 1
		{ 0, 1, 0 },
		{ 1, 1, 1 }
	},
	{
		{ 1, 1, 1 },
		{ 0, 0, 1 },
		{ 1, 1, 1 }, // 2
		{ 1, 0, 0 },
		{ 1, 1, 1 }
	},
	{
		{ 1, 1, 1 },
		{ 0, 0, 1 },
		{ 1, 1, 1 }, // 3
		{ 0, 0, 1 },
		{ 1, 1, 1 }
	},
	{
		{ 1, 0, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 1 }, // 4
		{ 0, 0, 1 },
		{ 0, 0, 1 }
	},
	{
		{ 1, 1, 1 },
		{ 1, 0, 0 },
		{ 1, 1, 1 }, // 5
		{ 0, 0, 1 },
		{ 1, 1, 1 }
	},
	{
		{ 1, 0, 0 },
		{ 1, 0, 0 },
		{ 1, 1, 1 }, // 6
		{ 1, 0, 1 },
		{ 1, 1, 1 }
	},
	{
		{ 1, 1, 1 },
		{ 1, 0, 1 },
		{ 0, 0, 1 }, // 7
		{ 0, 0, 1 },
		{ 0, 0, 1 }
	},
	{
		{ 1, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 1 }, // 8
		{ 1, 0, 1 },
		{ 1, 1, 1 }
	},
	{
		{ 1, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 1 }, // 9
		{ 0, 0, 1 },
		{ 0, 0, 1 }
	}
};
int colon_[1][5] = {
	{
		{ 0 },
		{ 1 },
		{ 0 },  // 00 : 00 할때 : 를 표시할때는 colon_[0], 아무것도 표시 안할때는 colon_[1]
		{ 1 },
		{ 0 }
	}
};

void elpTime();
void pTime();  //현재시간 출력
void keyListener(); //키입력을 대기하고 처리하는 함수
void setAlarm(); //알람함수
void writeData(); //로그파일에 시간데이터 저장
void statistics(); //7일일간 사용량을 평균냄
void checkElpTime(); //30일간 사용량을 출력함
void gotoxy(int x, int y);
void TimePrint(int pos, int num);
void ColonPrint(int num);
// void MapPrint(); // 사용 안함

int main()
{
	srand((unsigned)time(NULL));
	system("mode con:cols=40 lines=10");// con:cols=50 : 가로 길 lines=20 : 세로 길

	while (endProgram) {
		system("cls");
		keyListener();
		elpTime();
		pTime();
		printf("\t0 메 뉴, ESC 종 료.\n");
		Sleep(1000);
	}

	writeData(); //시간값 저장
	return 0;
}

void elpTime() {      //시작부터 종료까지 사용량 출력
	int random[2] = { rand() % 100 + 1,rand() % 100 + 1 };
	int a = 0;

	c = (clock() / 1000) + 1; //clock()는 1/1000초를 반환하므로 1초로 단위 변경 (전역변수)
	m = (c / 60) % 60; //분 (전역변수)
	h = c / 3600; //시 (전역변수)
	s = c % 60;
	if ((c % alarm) == 0) { //전역변수로 설정한 알람시간이 되면 비프음 출력

		PlaySound(TEXT(Third_Run), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // wav 파일 재생함수

		printf("알람을 끄고싶으면 정답을 입력하세요!\n");
		printf("%d + %d = ?\n", random[0], random[1]);
		printf("정답 입력= ");
		scanf("%d", &a);

		while (!((random[0] + random[1]) == a)) // 정답 맞출때까지 반복
		{
			system("cls");
			printf("틀렸습니다. 다시 입력하세요\n");
			printf("%d + %d = ?\n", random[0], random[1]);
			printf("정답 입력= ");
			scanf("%d", &a);
		}
		printf("정답입니다! 알람을 종료합니다.\n");
		PlaySound(NULL, 0, 0);
	}
	TimePrint(0, h / 10);
	TimePrint(1, h % 10);
	ColonPrint(0); // 콜론(:)함수 실행 00:00
	TimePrint(2, m / 10);
	TimePrint(3, m % 10);

}

void TimePrint(int pos, int num) // 현재시간을 디지털숫자로 표시하는 함수
{
	int x = 0, y = 0, count = 0;
	for (y = 0; y < 5; y++)
	{
		for (x = 0; x < 3; x++)
		{
			gotoxy(sx[pos] + (x) * 2, y); // gotoxy()함수로 숫자 출력할 곳 조절
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
			gotoxy(sx2[num], y);
			if (colon_[x][y] == 1)
				printf("■");
			else if (colon_[x][y] == 0)
				printf("　");
		}
		printf("\n");
	}
}

void gotoxy(int x, int y) // xy좌표 이동 함수
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}


void pTime() {   //현재시간 출력
	struct tm *t; //localtime(time_t timer)에서 반환하는 주소값을 받을 구조체
	time_t timer; //time(NULL)을 담을 time_t형 변수
	timer = time(NULL);
	t = localtime(&timer); //time_t timer 값을 현지시간으로 바꿔준다
	printf("현재시간 %.2d:%.2d\n", t->tm_hour, t->tm_min);
}

void keyListener() {   //키입력을 대기하고 처리하는 함수
	if (_kbhit() != 0) //키보드 버퍼값이 있으면 반복문을 빠져나옴
	{
		state = getch();
		switch (state) {
		case ESC:
			printf("종료합니다.\n");
			endProgram = 0;
			break;
		case '0':
			system("mode con:cols=50 lines=20"); //메뉴창에 맞게 창사이즈 변경
			printf("\n\n \t\t    M  E  N  U\n\n\t1. 알람시간 설정\n\n\t2. 사용량 통계\n\n\t3. 컴퓨터 사용량 확인\n\n\tESC. 이전\n");
			state = getch();
			switch (state) {
			case ESC:
				break;
			case '1':
				setAlarm(); //알람 함수 호출
				break;
			case '2':
				statistics(); //통계 함수 호출
				break;
			case '3':
				checkElpTime(); //사용량 출력 함수 호출
				break;
			}
			system("mode con:cols=40 lines=10");
			break;
		}
	}

}

void setAlarm() {      //알람함수
	int alramH = 1, alramM = 00; // 알람시간 시, 분
	system("cls");
	system("mode con:cols=35 lines=10");
	printf(" \n     알람 설정 메뉴입니다.\n    (현재 %d시 %d분마다 알람)\n\n",alarm/3600,alarm/60%60);
	while (1) {
		while (1) {  //알람 시 설정
			printf("     원하는 hour( 0 ~ 24) : ");
			scanf("%d",&alramH);
			if (alramH > 24 || alramH < 0) {
				system("cls");
				printf("       잘못된 입력입니다.\n");
				continue;
			}
			break;
		}
		while (1) { // 알람 분 설정
			printf("   원하는 minute( 0 ~ 59 ) : ");
			scanf("%d", &alramM);
			if (alramM > 59 || alramM < 0) {
				system("cls");
				printf("       잘못된 입력입니다.\n");
				continue;
			}
			break;
		}
		alarm = (alramH * 3600) + (alramM * 60); //시, 분을 초단위로 변환 하여 전역변수 alarm에 저장
		if (alarm == 0) {  //0시 0분일 때를 방지
			system("cls");
			printf("       잘못된 입력입니다.\n");
			continue;
		}
		break;
	}

}



void writeData() { //로그파일에서 데이터를 최근값으로 배열 크기만큼 읽어들임

	ifstream fin;
	int a[1000][6];
	int n = 0;

	fin.open("Log.txt");

	struct tm *t;
	time_t timer;

	timer = time(NULL);
	t = localtime(&timer);

	if (fin.fail()) { //파일을 "append"형(파일끝에 추가하여 씀)으로 열고 오류가 발생하면 리턴
		printf("파일을 열 수 없습니다.\n");
	}
	else {

		for (n = 0; !fin.eof(); n++) {

			for (int j = 0; j<6; j++) {
				fin >> a[n][j];
			}

		}
		n--;

	}

	fin.close();

	ofstream fout;
	fout.open("Log.txt");

	if (a[n - 1][0] == t->tm_year + 1900 && a[n - 1][1] == t->tm_mon + 1 && a[n - 1][2] == t->tm_mday) {
		a[n - 1][3] += h;
		a[n - 1][4] += m;
		a[n - 1][5] += s;
	}
	else {
		a[n][0] = t->tm_year + 1900;
		a[n][1] = t->tm_mon + 1;
		a[n][2] = t->tm_mday;
		a[n][3] = h;
		a[n][4] = m;
		a[n][5] = s;
		n++;
	}

	for (int i = 0; i<n; i++) {
		for (int j = 0; j<6; j++) {
			fout << a[i][j] << " ";
		}
		fout << endl;
	}

}

void checkElpTime() {   //30일간 사용량을 출력함
	system("mode con:cols=50 lines=20");
	ifstream fin;
	int a[1000][6];
	int n, i, j;

	system("cls");

	fin.open("Log.txt");

	if (fin.fail()) { //파일을 "append"형(파일끝에 추가하여 씀)으로 열고 오류가 발생하면 리턴
		printf("파일을 열 수 없습니다.\n");
		return;
	}

	for (n = 0; !fin.eof(); n++) {

		for (j = 0; j<6; j++) {
			fin >> a[n][j];
		}

	}
	printf("\n");
	n--;

	if (n <= 15) {

		for (i = 0; i<n; i++) {
			printf("\t%d년 %2d월 %2d일 : %2d시간 %2d분 %2d초\n", a[i][0], a[i][1], a[i][2], a[i][3], a[i][4], a[i][5]);
		}

	}
	else {

		for (i = n - 15; i<n; i++) {
			printf("\t%d년 %2d월 %2d일 : %2d시간 %2d분 %2d초\n", a[i][0], a[i][1], a[i][2], a[i][3], a[i][4], a[i][5]);
		}

	}
	printf("\n\t\t0 되돌아가기");
	getch();
}

void statistics() { //사용시간을 통계내는 함수 간략화가 필요하다

	system("mode con:cols=40 lines=10");
	ifstream fin;
	int a[1000][6];
	int n, i, j, sum = 0;

	system("cls");

	fin.open("Log.txt");

	if (fin.fail()) { //파일을 "append"형(파일끝에 추가하여 씀)으로 열고 오류가 발생하면 리턴
		printf("\n\n\t파일을 열 수 없습니다.");
		return;
	}

	for (n = 0; !fin.eof(); n++) {

		for (j = 0; j<6; j++) {
			fin >> a[n][j];
		}

	}

	n--;

	if (n <= 7) {
		for (i = 0; i<n; i++) {
			sum = sum + (a[i][3] * 60) + a[i][4];
		}
	}
	else {
		for (i = n - 7; i<n; i++) {
			sum = sum + (a[i][3] * 60) + a[i][4];
		}
	}

	printf("\n\n\t  7일 사용 평균 : %d분\n\n\n", sum / 7);
	printf("\t     0 되돌아가기");
	getch();

}