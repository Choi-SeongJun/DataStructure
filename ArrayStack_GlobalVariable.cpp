#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 10
#define FALSE 0
#define TRUE 1

typedef int element;
element stack[MAX_STACK_SIZE];
int top = -1;

int is_empty()
{
	return top==-1;
	/*
	if(top==-1) return TRUE;
	return FALSE;
	*/
}

int is_full()
{
	return (top == (MAX_STACK_SIZE - 1));
	/*
	if(top==MAX_STACK_SIZE-1) return TRUE;
	return FALSE;
	*/
}

void push(element item)
{
	if(is_full())
	{
		fprintf(stderr, "STACK OVERFLOW\n");
		return;
	}
	else
	{
		stack[++top]=item;
		/*
		top = top + 1
		stack[top] = item;
		*/
	}
}

element pop()
{
	//element item;
	
	if(is_empty())
	{
		fprintf(stderr, "STACK UNDERFLOW\n");
		exit(1);
	}
	else
	{
		return stack[top--];
		/*
		item = stack[top];
		top = top - 1;
		return item;
		*/
	}
}

element seek()
{
	if(is_empty())
	{
		fprintf(stderr, "EMPTY STACK");
		exit(1);
	}
	else
		return stack[top];
}

int main(void)
{
	push(1);
	push(2);
	push(3);
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", is_empty());
}
