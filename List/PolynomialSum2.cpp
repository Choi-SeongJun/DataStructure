#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101
struct{
	float coef;
	int expon;
} terms[MAX_TERMS] = {{8, 3}, {7, 1}, {1, 0}, {10, 3}, {3, 2}, {1, 0}};
int avail=6;
// �� ���� ������ ��

char compare(int a, int b)
{
	if(a>b) return '>';
	else if(a==b) return '=';
	else return '<';
}
// ���ο� ���� ���׽Ŀ� �߰��Ѵ�.
void attach(float coef, int expon)
{
	if(avail>=MAX_TERMS){
		fprintf(stderr, "���� ������ �ʹ� ����\n");
		exit(1);
	}
	terms[avail].coef=coef;
	terms[avail++].expon=expon;
}
// C = A + B
void poly_add2(int As, int Ae, int Bs, int Be, int *Cs, int *Ce)
{
	float tempcoef; // A�� B�� ���� ������ ���� ���� �� �ش� ���� ��� ���� 
	*Cs = avail;
	while(As <= Ae && Bs <= Be)
	switch(compare(terms[As].expon, terms[Bs].expon)){ // A�� B�� �ְ������� ���� �� 
		case '>': // A�� ���� > B�� ����
			attach(terms[As].coef, terms[As].expon);
			As ++; break;
		case '=': // A�� ���� == B�� ����
			tempcoef = terms[As].coef + terms[Bs].coef;
			if(tempcoef)
				attach(tempcoef, terms[As].expon);
			As++; Bs++; break;
		case '<': // A�� ���� < B�� ����
			attach(terms[Bs].coef, terms[Bs].expon);
			Bs++; break;
	}
	// A�� ������ �׵��� �̵���
	for(; As<=Ae; As++)
		attach(terms[As].coef, terms[As].expon);
	// B�� ������ �׵��� �̵���
	for(; Bs<=Be; Bs++)
		attach(terms[Bs].coef, terms[Bs].expon);
	*Ce = avail - 1;
}

int main()
{
	int Cs, Ce;
	poly_add2(0, 2, 3, 5, &Cs, &Ce);
}
