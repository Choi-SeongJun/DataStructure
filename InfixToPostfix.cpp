#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef char element;

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

int prec(char op)
{
	switch(op)
	{
		case '(': case ')': return 0;
		case '+': case '-': return 1;
		case '*': case '/': return 2;
	}
	return -1;
}

/* if문을 중첩하여 작성한 첫번째 코드 */
/*
void infix_to_postfix(const char exp[])
{
	int i, len, p;
	char ch;
	len = strlen(exp);
	
	LinkedStackType s;
	init(&s);
	
	for(i=0; i<len; i++)
	{
		ch = exp[i];
		p = prec(ch);
		
		if(p == -1)
			printf("%c", ch);
		else if(is_empty(&s))
			push(&s, ch);
		else
		{
			if(p == 0)
			{
				if(ch == '(')
					push(&s, ch);
				else
				{
					do{
						printf("%c", pop(&s));
					} while((peek(&s)!='('));
					pop(&s);
				}
			}
			else if(prec(peek(&s))<p)
				push(&s, ch);
			else
			{
				printf("%c", pop(&s));
				push(&s, ch);
			}
		}
	}
	
	while(!is_empty(&s))
		printf("%c", pop(&s));
}
*/

void infix_to_postfix(const char exp[])
{
	int i, p;
	char ch;
	LinkedStackType s;
	
	init(&s);
	
	for(i=0; i<strlen(exp); i++)
	{
		ch = exp[i];
		p = prec(ch);
		
		switch(p)
		{
			case -1:
				printf("%c", ch);
				break;
				
			case 0:
				if(ch=='(')
					push(&s, ch);
				else
				{
					while(peek(&s)!='(')
						printf("%c", pop(&s));
					pop(&s);
				}
				break;
				
			case 1: case 2:
				if(is_empty(&s))
					push(&s, ch);
				else if(p>prec(peek(&s)))
					printf("%c", ch);
				else
				{
					printf("%c", pop(&s));
					push(&s, ch);
					break;
				}
		}
	}
	
	while(!is_empty(&s))
		printf("%c", pop(&s));
}


int main(void)
{
	infix_to_postfix("(2+3)*4+9");
	
	return 0;
}
