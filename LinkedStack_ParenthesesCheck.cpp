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

int check_matching(const char *in)
{
	LinkedStackType s;
	char ch, open_ch;
	int i, n = strlen(in);
	init(&s);
	
	for(i=0; i<n; i++)
	{
		ch = in[i];
		switch(ch)
		{
			case '(':	case '[':	case '{':
				push(&s, ch);
				break;
			case ')':	case ']':	case '}':
				if(is_empty(&s)) return FALSE;
				else
				{
					open_ch = pop(&s);
					if((open_ch == '(' && ch != ')') || (open_ch == '[' && ch != ']') || (open_ch == '{' && ch != '}'))
						return FALSE;
				}
				break;
		}
	}
	if(!is_empty(&s)) return FALSE;
	return TRUE;
}

int main(void)
{
	if(check_matching("{A[(i+1)]=0; }")==TRUE)
		printf("괄호검사성공\n");
	else
		printf("괄호검사실패\n");
		
	return 0;
}
