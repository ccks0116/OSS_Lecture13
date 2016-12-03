// project.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "stdlib.h"
#include "windows.h"//Sleep(), Beep()를 사용하기위한 헤더파일
#include "time.h"
#include "conio.h" //_kbhit(),getch()
#include "MMSystem.h" // PlaySound() 함수 실행하기 위한 헤더파일
#pragma comment(lib,"Winmm.lib")

#define ESC 27
#define MAX 10
#define Third_Run "alram.wav"

typedef struct SaveTime {  //데이터 저장시 구조체단위로 파일입출력하기위한 구조체
	time_t date;
	int elpTime;
}saveTime;

int c = 0; //clock()로 받은 값을 저장
int m = 0, h = 0; // 경괴시간 분, 시
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

void elpTime();//시작부터 종료까지 사용량 출력
void pTime();  //현재시간 출력
void keyListener(); //키입력을 대기하고 처리하는 함수
void setAlarm(); //알람함수
void writeData(); //로그파일에 시간데이터 저장
void readData(saveTime *arr, int arrSize); //로그파일에서 데이터를 최근값으로 배열 크기만큼 읽어들임
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
		printf("\t0 메뉴, ESC 종료.\n");
		Sleep(1000);
	}

	writeData(); //시간값 저장
	return 0;
}

void elpTime() {		//시작부터 종료까지 사용량 출력
	int random[2] = { rand() % 100 + 1,rand() % 100 + 1 };
	int a = 0;

	c = (clock() / 1000) + 1; //clock()는 1/1000초를 반환하므로 1초로 단위 변경 (전역변수)
	m = (c / 60) % 60; //분 (전역변수)
	h = c / 3600; //시 (전역변수)
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
			printf("? 입력= ");
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


void pTime() {	//현재시간 출력
	struct tm *t; //localtime(time_t timer)에서 반환하는 주소값을 받을 구조체
	time_t timer; //time(NULL)을 담을 time_t형 변수
	timer = time(NULL);
	t = localtime(&timer); //time_t timer 값을 현지시간으로 바꿔준다
	printf("현재시간 %.2d:%.2d\n", t->tm_hour, t->tm_min);
}

void keyListener() {	//키입력을 대기하고 처리하는 함수
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
			printf("\n\n\t\t     M E N U\n\n\n\t1. 알람시간 설정\n\n\t2. 사용량 통계\n\n\t3. 컴퓨터 사용량 확인\n\n\tESC. 이전\n");
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

void setAlarm() {		//알람함수
	int alarmH = 0, alarmM = 01; // 알람시간 시, 분
	system("cls");
	printf("알람 설정 메뉴입니다.(기본 1시간마다 알람)\n");
	printf("----------------------\n");
	while (1) {
		while (1) {  //알람 시 설정
			printf("시간을 설정해 주십시오( 0 ~ 24 )\n");
			scanf("%d", &alarmH);
			if (alarmH > 24) {
				printf("24시를 넘을 수 없습니다.\n");
				continue;
			}
			break;
		}
		while (1) { // 알람 분 설정
			printf("분을 설정해 주십시오( 0 ~ 59 )\n");
			scanf("%d", &alarmM);
			if (alarmH > 59) {
				printf("59분를 넘을 수 없습니다.\n");
				continue;
			}
			break;
		}
		alarm = (alarmH * 3600) + (alarmM * 60); //시, 분을 초단위로 변환 하여 전역변수 alarm에 저장
		if (alarm == 0) {  //0시 0분일 때를 방지
			printf("시간을 다시설정 하세요.\n");
			continue;
		}
		break;
	}

}

void writeData() { //로그파일에서 데이터를 최근값으로 배열 크기만큼 읽어들임
	FILE * fp;

	if ((fp = fopen("Log.txt", "a")) == NULL) { //파일을 "append"형(파일끝에 추가하여 씀)으로 열고 오류가 발생하면 리턴
		printf("파일을 열 수 없습니다.\n");
		return;
	}
	saveTime save; //구조체 단위로 저장하기위함 
	save.date = time(NULL); //saveTime 속성 time_t date
	save.elpTime = clock(); // int elaTime
	fwrite(&save, sizeof(saveTime), 1, fp); //구조체의 크기만큼 한덩어리씩 로그파일에 저장한다.
	fclose(fp);
}

void readData(saveTime arr[], int arrSize) {	//로그파일에서 데이터를 최근값으로 배열 크기만큼 읽어들임
	FILE * fp;
	saveTime read; //읽어들인 데이터를 저장할 구조체
	int i = 1, j = 0; //카운트 변수
	int time1 = 0, time2 = 0; //시간 비교를 위한 변수
	struct tm * t;
	system("cls");

	if ((fp = fopen("Log.txt", "r")) == NULL) {		//파일을 "read"형(읽기 전용)으로 열고 오류발생시 리턴
		printf("파일을 열 수 없습니다.\n처음 실행 시켰다면 프로그램 종료후 로그파일이 생성됩니다\n");
		getch();
		return;
	}

	fseek(fp, -sizeof(saveTime), SEEK_END); //로그파일의 제일 뒷부분부터 구조체saveTime 단위만큼 뒤로 건너뜀
	fread(&read, sizeof(saveTime), 1, fp);	//saveTime크기 만큼 읽어들임
	arr[j] = read;							//읽어들인 값으로 일단 첫번째배열을 채운다.

	while (ftell(fp) != sizeof(saveTime)) {
		fseek(fp, -(i + 1) * sizeof(saveTime), SEEK_END); //파일의 끝에서 saveTime의 크기만큼 i+1번 뒤로 이동시킨다. (최근 저장된순으로 읽어들이기 위함)
		fread(&read, sizeof(saveTime), 1, fp);
		t = localtime(&arr[j].date);	time1 = t->tm_min; //날짜비교를위세 각각변수에 저장 ////////////////////////분으로 바꿔놨음 나중에 날짜(mday)로 바꿔야됨///////////
		t = localtime(&read.date);		time2 = t->tm_min;
		if (j == arrSize) {					//배열을 넘어가면 종료
			break;
		}
		else if (time1 == time2) {  //날짜가 같으면 사용시간을 더함
			arr[j].elpTime += read.elpTime;
		}
		else {
			j = j + 1;
			arr[j] = read;//날짜가 다르면 다음배열에 저장
		}
		i++;
	}

}

void checkElpTime() {	//30일간 사용량을 출력함
	system("mode con:cols=50 lines=50"); //창크기 조정
	struct tm * t;
	saveTime arr[30] = { {} }; //30일간의 데이터를 담을 구조체배열
	readData(arr, sizeof(arr) / sizeof(saveTime)); //readDate()를 이용하여 배열의 수(sizeof(arr) / sizeof(saveTime))만큼 로그파일에서 읽어 들인다.
	for (int i = 0; i < sizeof(arr) / sizeof(saveTime); i++) {
		if (arr[i].date == 0)
			break;
		t = localtime(&arr[i].date); //읽어들인 시간을 현지시간으로 변경
		printf("%2d일 사용시간 %10d초\n", t->tm_min, arr[i].elpTime / 1000); //////////////////////////분으로 바꿔놨음 나중에 날짜로 바꿔야됨///////////
	}
	printf("아무키 입력시 종료\n");
	getch();
}

void statistics() { //사용시간을 통계내는 함수 간략화가 필요하다
	saveTime arr[7] = { {} };
	int sum = 0;
	readData(arr, sizeof(arr) / sizeof(saveTime));
	for (int i = 0; i < sizeof(arr) / sizeof(saveTime); i++) {
		sum += arr[i].elpTime;
	}
	printf("7일간 평균 사용량 = %d\n", sum / 7);
	printf("아무키 입력시 종료\n");
	getch();
}