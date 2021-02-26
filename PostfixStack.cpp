#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef int element;

typedef struct StackNode{
	element item;
	struct StackNode *link;
} StackNode;

typedef struct{
	StackNode *top;
} LinkedStackType;

void init(LinkedStackType *s)
{
	s->top = NULL;
}

int is_empty(LinkedStackType *s)
{
	return(s->top==NULL);
}

void push(LinkedStackType *s, element item)
{
	StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
	if(temp==NULL)
	{
		fprintf(stderr, "메모리 할당오류\n");
		return;
	}
	else
	{
		temp->item = item;
		temp->link = s->top;
		s->top = temp;
	}
}

element pop(LinkedStackType *s)
{
	if(is_empty(s))
	{
		fprintf(stderr, "스택이 비어있음\n");
		exit(1);
	}
	else
	{
		StackNode *temp = s->top;
		element item = temp->item;
		s->top = s->top->link;
		free(temp);
		return item;
	}
}

element peek(LinkedStackType *s)
{
	if(is_empty(s))
	{
		fprintf(stderr, "스택이 비어있음\n");
		exit(1);
	}
	else
		return s->top->item;
}

int eval(const char exp[])
{
	LinkedStackType s;
	char ch;
	int i, op1, op2;
	init(&s);
	
	for(i=0; i<strlen(exp); i++)
	{
		ch = exp[i];
		
		if((ch!='+')&&(ch!='-')&&(ch!='*')&&(ch!='/'))
			push(&s, ch-'0');
		else
		{
			op2 = pop(&s);
			op1 = pop(&s);
			switch(ch)
			{
				case '+': push(&s, op1+op2); break;
				case '-': push(&s, op1-op2); break;
				case '*': push(&s, op1*op2); break;
				case '/': push(&s, op1/op2); break;
			}
		}
	}
	return pop(&s);
}

int main(void)
{
	int result;
	printf("후위표기식은 82/3-32*+\n");
	result = eval("82/3-32*+");
	printf("결과값은 %d\n", result);
	
	return 0;
}
