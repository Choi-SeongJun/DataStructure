#include <stdio.h>
#define MAX_SIZE 10
#define MAX_DEGREE 101
// 배열을 매개 변수로 받는 함수 

void sub(int var, int list[])
{
	var = 10;
	list[0] = 10;
}

void main()
{
	int var;
	int list[MAX_SIZE];
	
	var = 0; // 정수 변수의 선언 
	list[0] = 0; // 정수 배열의 선언 
	
	sub(var, list);
	printf("var=%d", list[0]=%d\n", var, list[0]);
}


