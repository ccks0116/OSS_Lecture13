#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(void)
{
	//���� ����
	ifstream fin;
	fin.open("output.txt");

	int data[10000]; // ���
	int n,m=0; // n : �Է�/ m : data ����
	
	while (!fin.eof()){ // ���� ��ã��
		
		fin >> n; // �����Է�
		data[m++] = n; // data ���

	}

	int avg = data[m-1]; // ������ data avg�� ����

	for (int i = m-7; i < m-1; i++) {
		avg += data[i]; // 7�� data ����

	}

	avg /= 7; // ���

	fin.close();
	
	printf("��� : %d\n",avg);

	return 0;
}
