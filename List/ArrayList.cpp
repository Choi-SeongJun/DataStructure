#include <stdio.h>
#include <stdlib.h>
#define MAX_LIST_SIZE 100

typedef int element;
typedef struct {
	int list[MAX_LIST_SIZE];
	int length;
} ArrayListType;

void error(const char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init(ArrayListType *L)
{
	L->length = 0;
}

int is_empty(ArrayListType *L)
{
	return L->length==0;
}

int is_full(ArrayListType *L)
{
	return L->length==MAX_LIST_SIZE;
}

void display(ArrayListType *L)
{
	int i;
	for(i=0; i<L->length; i++)
		printf("%d\n", L->list[i]);
}

void add(ArrayListType *L, int position, element item)
{
	if(!is_full(L) && position<=L->length && position>=0)
	{
		int i;
		for(i=L->length; i>position; i--)
			L->list[i]=L->list[i-1];
		L->list[position] = item;
		L->length++;
	}
	else
		error("오류발생");
		
}

element del(ArrayListType *L, int position)
{
	int i;
	element item;
	
	if(position<0 || position>=L->length)
		error("오류발생");
	item = L->list[position];
	for(i=position; i<L->length-1; i++)
		L->list[i]=L->list[i+1];
	L->length--;
	return item;
}

void clear(ArrayListType *L)
{
	int i;
	for(i=0; i<L->length; i++)
		L->list[i] = 0;
	L->length = 0;
}

element replace(ArrayListType *L, int position, element item)
{
	int prev = L->list[position];
	L->list[position] = item;
	return prev;
}

element get_entry(ArrayListType *L, int position)
{
	return L->list[position];
}

int get_length(ArrayListType *L)
{
	return L->length;
}


int main()
{
	ArrayListType list1;
	ArrayListType *plist;
	
	init(&list1);
	add(&list1, 0, 10);
	add(&list1, 0, 20);
	add(&list1, 0, 30);
	display(&list1);
	
	plist = (ArrayListType *)malloc(sizeof(ArrayListType));
	init(plist);
	add(plist, 0, 10);
	add(plist, 0, 20);
	add(plist, 0, 30);
	display(plist);
	free(plist);
	
	return 0;
}
