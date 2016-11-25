#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(void)
{
	//파일 생성
	ifstream fin;
	fin.open("output.txt");

	int data[10000]; // 기록
	int n,m=0; // n : 입력/ m : data 길이
	
	while (!fin.eof()){ // 파일 끝찾기
		
		fin >> n; // 파일입력
		data[m++] = n; // data 기록

	}

	int avg = data[m-1]; // 마지막 data avg에 저장

	for (int i = m-7; i < m-1; i++) {
		avg += data[i]; // 7개 data 저장

	}

	avg /= 7; // 평균

	fin.close();
	
	printf("평균 : %d\n",avg);

	return 0;
}
