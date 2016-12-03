// project.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "stdlib.h"
#include "windows.h"//Sleep(), Beep()�� ����ϱ����� �������
#include "time.h"
#include "conio.h" //_kbhit(),getch()
#include "MMSystem.h" // PlaySound() �Լ� �����ϱ� ���� �������
#pragma comment(lib,"Winmm.lib")

#define ESC 27
#define MAX 10
#define Third_Run "alram.wav"

typedef struct SaveTime {  //������ ����� ����ü������ ����������ϱ����� ����ü
	time_t date;
	int elpTime;
}saveTime;

int c = 0; //clock()�� ���� ���� ����
int m = 0, h = 0; // �汫�ð� ��, ��
int state = NULL; // Ű�Է� ����
int endProgram = 1; //���α׷� ����
int alarm = 3600;// �ʷ� ȯ���� �˶��ð�
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

void elpTime();//���ۺ��� ������� ��뷮 ���
void pTime();  //����ð� ���
void keyListener(); //Ű�Է��� ����ϰ� ó���ϴ� �Լ�
void setAlarm(); //�˶��Լ�
void writeData(); //�α����Ͽ� �ð������� ����
void readData(saveTime *arr, int arrSize); //�α����Ͽ��� �����͸� �ֱٰ����� �迭 ũ�⸸ŭ �о����
void statistics(); //7���ϰ� ��뷮�� ��ճ�
void checkElpTime(); //30�ϰ� ��뷮�� �����
void gotoxy(int x, int y);
void TimePrint(int pos, int num);
void ColonPrint(int num);
// void MapPrint(); // ��� ����

int main()
{
	srand((unsigned)time(NULL));
	system("mode con:cols=40 lines=10");// con:cols=50 : ���� �� lines=20 : ���� ��

	while (endProgram) {
		system("cls");
		keyListener();
		elpTime();
		pTime();
		printf("\t0 �޴�, ESC ����.\n");
		Sleep(1000);
	}

	writeData(); //�ð��� ����
	return 0;
}

void elpTime() {		//���ۺ��� ������� ��뷮 ���
	int random[2] = { rand() % 100 + 1,rand() % 100 + 1 };
	int a = 0;

	c = (clock() / 1000) + 1; //clock()�� 1/1000�ʸ� ��ȯ�ϹǷ� 1�ʷ� ���� ���� (��������)
	m = (c / 60) % 60; //�� (��������)
	h = c / 3600; //�� (��������)
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
			printf("? �Է�= ");
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


void pTime() {	//����ð� ���
	struct tm *t; //localtime(time_t timer)���� ��ȯ�ϴ� �ּҰ��� ���� ����ü
	time_t timer; //time(NULL)�� ���� time_t�� ����
	timer = time(NULL);
	t = localtime(&timer); //time_t timer ���� �����ð����� �ٲ��ش�
	printf("����ð� %.2d:%.2d\n", t->tm_hour, t->tm_min);
}

void keyListener() {	//Ű�Է��� ����ϰ� ó���ϴ� �Լ�
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
			printf("\n\n\t\t     M E N U\n\n\n\t1. �˶��ð� ����\n\n\t2. ��뷮 ���\n\n\t3. ��ǻ�� ��뷮 Ȯ��\n\n\tESC. ����\n");
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
			}
			system("mode con:cols=40 lines=10");
			break;
		}
	}

}

void setAlarm() {		//�˶��Լ�
	int alarmH = 0, alarmM = 01; // �˶��ð� ��, ��
	system("cls");
	printf("�˶� ���� �޴��Դϴ�.(�⺻ 1�ð����� �˶�)\n");
	printf("----------------------\n");
	while (1) {
		while (1) {  //�˶� �� ����
			printf("�ð��� ������ �ֽʽÿ�( 0 ~ 24 )\n");
			scanf("%d", &alarmH);
			if (alarmH > 24) {
				printf("24�ø� ���� �� �����ϴ�.\n");
				continue;
			}
			break;
		}
		while (1) { // �˶� �� ����
			printf("���� ������ �ֽʽÿ�( 0 ~ 59 )\n");
			scanf("%d", &alarmM);
			if (alarmH > 59) {
				printf("59�и� ���� �� �����ϴ�.\n");
				continue;
			}
			break;
		}
		alarm = (alarmH * 3600) + (alarmM * 60); //��, ���� �ʴ����� ��ȯ �Ͽ� �������� alarm�� ����
		if (alarm == 0) {  //0�� 0���� ���� ����
			printf("�ð��� �ٽü��� �ϼ���.\n");
			continue;
		}
		break;
	}

}

void writeData() { //�α����Ͽ��� �����͸� �ֱٰ����� �迭 ũ�⸸ŭ �о����
	FILE * fp;

	if ((fp = fopen("Log.txt", "a")) == NULL) { //������ "append"��(���ϳ��� �߰��Ͽ� ��)���� ���� ������ �߻��ϸ� ����
		printf("������ �� �� �����ϴ�.\n");
		return;
	}
	saveTime save; //����ü ������ �����ϱ����� 
	save.date = time(NULL); //saveTime �Ӽ� time_t date
	save.elpTime = clock(); // int elaTime
	fwrite(&save, sizeof(saveTime), 1, fp); //����ü�� ũ�⸸ŭ �ѵ���� �α����Ͽ� �����Ѵ�.
	fclose(fp);
}

void readData(saveTime arr[], int arrSize) {	//�α����Ͽ��� �����͸� �ֱٰ����� �迭 ũ�⸸ŭ �о����
	FILE * fp;
	saveTime read; //�о���� �����͸� ������ ����ü
	int i = 1, j = 0; //ī��Ʈ ����
	int time1 = 0, time2 = 0; //�ð� �񱳸� ���� ����
	struct tm * t;
	system("cls");

	if ((fp = fopen("Log.txt", "r")) == NULL) {		//������ "read"��(�б� ����)���� ���� �����߻��� ����
		printf("������ �� �� �����ϴ�.\nó�� ���� ���״ٸ� ���α׷� ������ �α������� �����˴ϴ�\n");
		getch();
		return;
	}

	fseek(fp, -sizeof(saveTime), SEEK_END); //�α������� ���� �޺κк��� ����üsaveTime ������ŭ �ڷ� �ǳʶ�
	fread(&read, sizeof(saveTime), 1, fp);	//saveTimeũ�� ��ŭ �о����
	arr[j] = read;							//�о���� ������ �ϴ� ù��°�迭�� ä���.

	while (ftell(fp) != sizeof(saveTime)) {
		fseek(fp, -(i + 1) * sizeof(saveTime), SEEK_END); //������ ������ saveTime�� ũ�⸸ŭ i+1�� �ڷ� �̵���Ų��. (�ֱ� ����ȼ����� �о���̱� ����)
		fread(&read, sizeof(saveTime), 1, fp);
		t = localtime(&arr[j].date);	time1 = t->tm_min; //��¥�񱳸����� ���������� ���� ////////////////////////������ �ٲ���� ���߿� ��¥(mday)�� �ٲ�ߵ�///////////
		t = localtime(&read.date);		time2 = t->tm_min;
		if (j == arrSize) {					//�迭�� �Ѿ�� ����
			break;
		}
		else if (time1 == time2) {  //��¥�� ������ ���ð��� ����
			arr[j].elpTime += read.elpTime;
		}
		else {
			j = j + 1;
			arr[j] = read;//��¥�� �ٸ��� �����迭�� ����
		}
		i++;
	}

}

void checkElpTime() {	//30�ϰ� ��뷮�� �����
	system("mode con:cols=50 lines=50"); //âũ�� ����
	struct tm * t;
	saveTime arr[30] = { {} }; //30�ϰ��� �����͸� ���� ����ü�迭
	readData(arr, sizeof(arr) / sizeof(saveTime)); //readDate()�� �̿��Ͽ� �迭�� ��(sizeof(arr) / sizeof(saveTime))��ŭ �α����Ͽ��� �о� ���δ�.
	for (int i = 0; i < sizeof(arr) / sizeof(saveTime); i++) {
		if (arr[i].date == 0)
			break;
		t = localtime(&arr[i].date); //�о���� �ð��� �����ð����� ����
		printf("%2d�� ���ð� %10d��\n", t->tm_min, arr[i].elpTime / 1000); //////////////////////////������ �ٲ���� ���߿� ��¥�� �ٲ�ߵ�///////////
	}
	printf("�ƹ�Ű �Է½� ����\n");
	getch();
}

void statistics() { //���ð��� ��賻�� �Լ� ����ȭ�� �ʿ��ϴ�
	saveTime arr[7] = { {} };
	int sum = 0;
	readData(arr, sizeof(arr) / sizeof(saveTime));
	for (int i = 0; i < sizeof(arr) / sizeof(saveTime); i++) {
		sum += arr[i].elpTime;
	}
	printf("7�ϰ� ��� ��뷮 = %d\n", sum / 7);
	printf("�ƹ�Ű �Է½� ����\n");
	getch();
}