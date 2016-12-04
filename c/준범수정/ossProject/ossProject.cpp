#include "stdafx.h"
#include "stdlib.h"
#include "windows.h"//Sleep(), Beep()�� ����ϱ����� �������
#include "time.h"
#include "conio.h" //_kbhit(),getch()
#include "MMSystem.h" // PlaySound() �Լ� �����ϱ� ���� �������
#include <iostream>
#include <fstream>
#pragma comment(lib,"Winmm.lib")

#define ESC 27
#define MAX 10
#define Third_Run "alram.wav"

using namespace std;

int c = 0; //clock()�� ���� ���� ����
int m = 0, h = 0, s = 0; // �汫�ð� ��, ��
int state = NULL; // Ű�Է� ����
int endProgram = 1; //���α׷� ����
int alarm = 3600;// �ʷ� ȯ���� �˶��ð�
int exittime = 28800;//������ �ð� ����
int sx[6] = { 0, 8, 20, 28, 40, 48 }; // gotoxy�� �� ��ǥ (0 8 �� �ð�, 20 28�� �� 40 48�� �� ������ �ʱ����� ��� x)
int sx2[2] = { 16 }; // �ݷ�(:) ���

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
		{ 0 },  // 00 : 00 �Ҷ� : �� ǥ���Ҷ��� colon_[0], �ƹ��͵� ǥ�� ���Ҷ��� colon_[1]
		{ 1 },
		{ 0 }
	}
};

void elpTime();
void pTime();  //����ð� ���
void keyListener(); //Ű�Է��� ����ϰ� ó���ϴ� �Լ�
void setAlarm(); //�˶��Լ�
void writeData(); //�α����Ͽ� �ð������� ����
void statistics(); //7���ϰ� ��뷮�� ��ճ�
void checkElpTime(); //30�ϰ� ��뷮�� �����
void gotoxy(int x, int y);
void TimePrint(int pos, int num);
void ColonPrint(int num);
void checkExittime();
void exitPC();
void pomodoro();
// void MapPrint(); // ��� ����

int main()
{
	srand((unsigned)time(NULL));
	system("title ��ǻ�� ���ð� ����");
	system("mode con:cols=40 lines=10");// con:cols=50 : ���� �� lines=20 : ���� ��

	while (endProgram) {
		system("cls");
		keyListener();
		elpTime();
		exitPC();
		pTime();
		printf("\t0 �� ��, ESC �� ��.\n");
		Sleep(1000);
	}

	writeData(); //�ð��� ����
	return 0;
}

void elpTime() {      //���ۺ��� ������� ��뷮 ���
	int random[2] = { rand() % 100 + 1,rand() % 100 + 1 };
	int a = 0;

	c = (clock() / 1000) + 1; //clock()�� 1/1000�ʸ� ��ȯ�ϹǷ� 1�ʷ� ���� ���� (��������)
	m = (c / 60) % 60; //�� (��������)
	h = c / 3600; //�� (��������)
	s = c % 60;
	if ((c % alarm) == 0) { //���������� ������ �˶��ð��� �Ǹ� ������ ���

		PlaySound(TEXT(Third_Run), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // wav ���� ����Լ�

		printf("�˶��� ��������� ������ �Է��ϼ���!\n");
		printf("%d + %d = ?\n", random[0], random[1]);
		printf("���� �Է�= ");
		scanf("%d", &a);

		while (!((random[0] + random[1]) == a)) // ���� ���⶧���� �ݺ�
		{
			system("cls");
			printf("Ʋ�Ƚ��ϴ�. �ٽ� �Է��ϼ���\n");
			printf("%d + %d = ?\n", random[0], random[1]);
			printf("���� �Է�= ");
			scanf("%d", &a);
		}
		printf("�����Դϴ�! �˶��� �����մϴ�.\n");
		PlaySound(NULL, 0, 0);
	}

	TimePrint(0, h / 10);
	TimePrint(1, h % 10);
	ColonPrint(0); // �ݷ�(:)�Լ� ���� 00:00
	TimePrint(2, m / 10);
	TimePrint(3, m % 10);

}

void TimePrint(int pos, int num) // ����ð��� �����м��ڷ� ǥ���ϴ� �Լ�
{
	int x = 0, y = 0, count = 0;
	for (y = 0; y < 5; y++)
	{
		for (x = 0; x < 3; x++)
		{
			gotoxy(sx[pos] + (x) * 2, y); // gotoxy()�Լ��� ���� ����� �� ����
			if (number_[num][y][x] == 1) // 19��° ���ο� �����ص� �迭�� ���� 1�̸� �������̴� �׸� ǥ�� ��� 0�̸� �Ⱥ��̴� �׸� ���
				printf("��");
			count++;
			if (number_[num][y][x] == 0)
				printf("��"); // ����x �Ⱥ��̴� �׸�
		}
		printf("\n"); // 3ĭ���� �ٹٲ�
	}
	printf("\n");
}
void ColonPrint(int num) // 00 : 00 �϶� :ǥ���ϴ� �Լ�
{
	int x = 0, y = 0;
	for (y = 0; y < 5; y++)
	{
		for (x = 0; x < 1; x++)
		{
			gotoxy(sx2[num], y);
			if (colon_[x][y] == 1)
				printf("��");
			else if (colon_[x][y] == 0)
				printf("��");
		}
		printf("\n");
	}
}

void gotoxy(int x, int y) // xy��ǥ �̵� �Լ�
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}


void pTime() {   //����ð� ���
	struct tm *t; //localtime(time_t timer)���� ��ȯ�ϴ� �ּҰ��� ���� ����ü
	time_t timer; //time(NULL)�� ���� time_t�� ����
	timer = time(NULL);
	t = localtime(&timer); //time_t timer ���� �����ð����� �ٲ��ش�
	printf("����ð� %.2d:%.2d\n", t->tm_hour, t->tm_min);
}

void keyListener() {   //Ű�Է��� ����ϰ� ó���ϴ� �Լ�
	if (_kbhit() != 0) //Ű���� ���۰��� ������ �ݺ����� ��������
	{
		state = getch();
		switch (state) {
		case ESC:
			printf("�����մϴ�.\n");
			endProgram = 0;
			break;
		case '0':
			system("mode con:cols=50 lines=20"); //�޴�â�� �°� â������ ����
			printf("\n\n \t\t    M  E  N  U\n\n\t1. �˶��ð� ����\n\n\t2. �ֱ� 7�ϰ� ��뷮 ���\n\n\t3. �ֱ� 15�ϰ� ��ǻ�� ��뷮 Ȯ��\n\n\t4. �������� ���� �ð�Ȯ��\n\n\t5. �Ǹ𵵸� �ð�����\n\n\tESC. ����\n");
			state = getch();
			switch (state) {
			case ESC:
				break;
			case '1':
				setAlarm(); //�˶� �Լ� ȣ��
				break;
			case '2':
				statistics(); //��� �Լ� ȣ��
				break;
			case '3':
				checkElpTime(); //��뷮 ��� �Լ� ȣ��
				break;
			case '4':
				checkExittime();//�������� �����ð� �Լ� ȣ��
				break;
			case '5':
				pomodoro();
				break;
			}
			system("mode con:cols=40 lines=10");
			break;
		}
	}

}

void setAlarm() {      //�˶��Լ�
	int alramH = 1, alramM = 00; // �˶��ð� ��, ��
	system("cls");
	system("mode con:cols=35 lines=10");
	printf(" \n     �˶� ���� �޴��Դϴ�.\n    (���� %d�� %d�и��� �˶�)\n\n", alarm / 3600, alarm / 60 % 60);
	while (1) {
		while (1) {  //�˶� �� ����
			printf("     ���ϴ� hour( 0 ~ 24) : ");
			scanf("%d", &alramH);
			if (alramH > 24 || alramH < 0) {
				system("cls");
				printf("       �߸��� �Է��Դϴ�.\n");
				continue;
			}
			break;
		}
		while (1) { // �˶� �� ����
			printf("   ���ϴ� minute( 0 ~ 59 ) : ");
			scanf("%d", &alramM);
			if (alramM > 59 || alramM < 0) {
				system("cls");
				printf("       �߸��� �Է��Դϴ�.\n");
				continue;
			}
			break;
		}
		alarm = (alramH * 3600) + (alramM * 60); //��, ���� �ʴ����� ��ȯ �Ͽ� �������� alarm�� ����
		if (alarm == 0) {  //0�� 0���� ���� ����
			system("cls");
			printf("       �߸��� �Է��Դϴ�.\n");
			continue;
		}
		break;
	}

}



void writeData() { //�α����Ͽ��� �����͸� �ֱٰ����� �迭 ũ�⸸ŭ �о����

	ifstream fin;
	int a[1000][6];
	int n = 0;

	fin.open("Log.txt");

	struct tm *t;
	time_t timer;

	timer = time(NULL);
	t = localtime(&timer);

	if (fin.fail()) { //������ "append"��(���ϳ��� �߰��Ͽ� ��)���� ���� ������ �߻��ϸ� ����
		printf("������ �� �� �����ϴ�.\n");
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

void checkElpTime() {   //30�ϰ� ��뷮�� �����
	system("mode con:cols=50 lines=20");
	ifstream fin;
	int a[1000][6];
	int n, i, j;

	system("cls");

	fin.open("Log.txt");

	if (fin.fail()) { //������ "append"��(���ϳ��� �߰��Ͽ� ��)���� ���� ������ �߻��ϸ� ����
		printf("Log������ �����ϴ�.\n���α׷��� �������� �� ��������ּ���.");
		getch();
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
			printf("\t%d�� %2d�� %2d�� : %2d�ð� %2d�� %2d��\n", a[i][0], a[i][1], a[i][2], a[i][3], a[i][4], a[i][5]);
		}

	}
	else {

		for (i = n - 15; i<n; i++) {
			printf("\t%d�� %2d�� %2d�� : %2d�ð� %2d�� %2d��\n", a[i][0], a[i][1], a[i][2], a[i][3], a[i][4], a[i][5]);
		}

	}
	printf("\n\t\t0 �ǵ��ư���");
	getch();
}

void statistics() { //���ð��� ��賻�� �Լ� ����ȭ�� �ʿ��ϴ�

	system("mode con:cols=40 lines=10");
	ifstream fin;
	int a[1000][6];
	int n, i, j, sum = 0;

	system("cls");

	fin.open("Log.txt");

	if (fin.fail()) { //������ "append"��(���ϳ��� �߰��Ͽ� ��)���� ���� ������ �߻��ϸ� ����
		printf("Log������ �����ϴ�.\n���α׷��� �������� �� ��������ּ���.");
		getch();
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

	printf("\n\n\t  7�� ��� ��� : %d��\n\n\n", sum / 7);
	printf("\t     0 �ǵ��ư���");
	getch();

}

void exitPC()
{
	if (c == exittime) {
		system("shutdown -s -t 60");
	}
}

void checkExittime() {
	int exittimeremaining = 0;
	int s;
	while (state != ESC) {
		s = clock()/1000;
		exittimeremaining = exittime - s;
		system("mode con:cols=35 lines=10");
		printf("\n\n     %d�ð� %d�� %d�� ���ҽ��ϴ�.\n\n\t   ESC �ǵ��ư���", exittimeremaining / 3600, (exittimeremaining / 60) % 60, exittimeremaining % 60);
		Sleep(1000);
		if (_kbhit() != 0){
			state = getch();
		}
	}
}

void pomodoro() {
	int cycle = 0;
	int state = 0, s = 1800;
	while (state != ESC) {
		system("cls");
		printf("   ����������������������������������������������\n");
		printf("               �Ǹ𵵷� �ð� �������\n");
		printf("   ����������������������������������������������\n");
		printf("   ����������������������������������������������\n");
		printf("              ���� �Ǹ𵵷� ����Ŭ : %dȸ\n", cycle);
		printf("   ����������������������������������������������\n");
		if (s < 300) {
			printf("   ��������������������������������������������\n");
			printf("              ���� �޽Ľð� %2d:%2d\n", s / 60, s % 60);
			printf("   ��������������������������������������������\n");
		}
		else if (s == 0){
			cycle++;
			s = 1800;
		}
		else{
			printf("        ����������������������������������\n");
			printf("                �����ð� [%2d:%2d]\n", (s / 60) - 5, s % 60);
			printf("        ����������������������������������\n");
		}
		printf("\n         ESC ����\n");
		s--;
		Sleep(1000);
		if (_kbhit() != 0){
			state = getch();
		}
	}
}
