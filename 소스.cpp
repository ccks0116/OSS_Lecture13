// project.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "stdlib.h"
#include "windows.h"
#include "time.h"
#include "conio.h" //_kbhit(),getch()�� ����ϱ����� �������

void elpTime();
void pTime();
void keyListener();
void setAlarm();
void writeData();
void readData();

typedef struct SaveTime {  //����ü������ �����������
	int date;
	int elaTime;
}saveTime;

int c = 0; //clock()�� ���� ���� ����
int m = 0, h = 0; // �汫�ð� ��, ��
int state = NULL; // Ű�Է� ����
int endProgram = 1; //���α׷� ����

int alarm = 3600;// �ʷ� ȯ���� �˶��ð�



#define ESC 27

int main()
{
	system("mode con:cols=20 lines=5");// con:cols=50 : ���� �� lines=20 : ���� ��

	while (endProgram) {
		system("cls");
		keyListener();
		elpTime();
		pTime();
		printf("0 ����, ESC ����.\n");
		Sleep(50);

	}

	writeData(); //�ð��� ����
	return 0;
}

void elpTime() {		//elapse time ����ð�
	c = clock() / 100; //clock()�� 1/1000�ʸ� ��ȯ�ϹǷ� 1�ʷ� ���� ����
	m = (c / 60) % 60;
	h = c / 3600;
	if ((c % alarm) == 0) { //�˶��ð��� �Ǹ� ������ ���
		printf("�ƹ�Ű �Է½� ����\n");
		for (int i = 0; i < 5; i++){
			Beep(262, 100);
			Beep(330, 100);
			Beep(392, 100);
			Beep(524, 100);
			if (_kbhit() != 0) {
				break;
			}
		}
	}

	printf("����ð� %.2d:%.2d\n", h, m);

}

void pTime() {	//present time ����ð�
	struct tm *t;
	time_t timer;
	timer = time(NULL);
	t = localtime(&timer);
	printf("����ð� %.2d:%.2d\n", t->tm_hour, t->tm_min);
}

void keyListener() {
	if (_kbhit() != 0) //Ű���� ���۰��� ������ �ݺ����� ��������
	{
		state = getch();
		switch (state) {
		case ESC:
			printf("�����մϴ�.\n");
			endProgram = 0;
			break;
		case '0':
			system("mode con:cols=50 lines=20");
			printf("1. �˶��ð� ����\n2. �Ǹ𵵸� �ð�����\n3. ��ǻ�� ��뷮 Ȯ��\nESC. ����\n");
			state = getch();
			switch (state) {
			case ESC:
				break;
			case '1':
				setAlarm();
				break;
			case '2':
				//pomodoro();
				break;
			case '3':
				readData();
				break;
			}
			system("mode con:cols=20 lines=5");
			break;
		}
	}

}

void setAlarm() {
	int alarmH = 0, alarmM = 01; // �˶��ð� ��, ��
	system("cls");
	printf("�˶� ���� �޴��Դϴ�.(�⺻ 1�ð����� �˶�)\n");
	printf("----------------------\n");
	while (1){
		while (1){  //�˶� �� ����
			printf("�ð��� ������ �ֽʽÿ�( 0 ~ 24 )\n");
			scanf("%d", &alarmH);
			if (alarmH > 24) {
				printf("24�ø� ���� �� �����ϴ�.\n");
				continue;
			}
			break;
		}
		while (1){ // �˶� �� ����
			printf("���� ������ �ֽʽÿ�( 0 ~ 59 )\n");
			scanf("%d", &alarmM);
			if (alarmH > 59) {
				printf("59�и� ���� �� �����ϴ�.\n");
				continue;
			}
			break;
		}
		alarm = (alarmH * 3600) + (alarmM * 60); //��, ���� �ʴ����� ��ȯ �Ͽ� alarm�� ����
		if (alarm == 0) {  //0�� 0���� ���� ����
			printf("�ð��� �ٽü��� �ϼ���.\n");
			continue;
		}
		break;
	}

}

void writeData() { //�ð� ����� ���� ��������� ����
	FILE * fp;
	
	if ((fp = fopen("Log.txt", "a")) == NULL) {
		printf("������ �� �� �����ϴ�.\n");
		return;
	}
	saveTime save;
	save.date = time(NULL);
	save.elaTime = clock();
	fwrite(&save, sizeof(saveTime), 1, fp);
	Sleep(500);
	fclose(fp);
}

void readData() { //�ð������ log.txt���� �о� ����
	FILE * fp;
	
	if ((fp = fopen("Log.txt", "r")) == NULL) {
		printf("������ �� �� �����ϴ�.\n");
	}

	saveTime read;
	struct tm * t;
	time_t timmer;

	while (fread(&read, sizeof(saveTime), 1, fp) != NULL){
		timmer = (time_t)read.date;
		t = localtime(&timmer);
		printf("%d %d\n", t->tm_hour, read.elaTime);
	}
	printf("�ƹ�Ű�� �����ÿ�\n");
	getch();

}