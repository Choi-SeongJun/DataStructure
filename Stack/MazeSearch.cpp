#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAZE_SIZE 6

typedef struct{
	short r;
	short c;
} element;

element here = {1, 0}, entry = {1, 0};

char maze[MAZE_SIZE][MAZE_SIZE] = {
	{'1', '1', '1', '1', '1', '1'},
	{'e', '0', '1', '0', '0', '1'},
	{'1', '0', '0', '0', '1', '1'},
	{'1', '0', '1', '0', '1', '1'},
	{'1', '0', '1', '0', '0', 'x'},
	{'1', '1', '1', '1', '1', '1'}
};

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

void push_loc(LinkedStackType *s, int r, int c)
{
	if(r < 0 || c < 0)
		return;
	if(maze[r][c]!='1' && maze[r][c]!='.')
	{
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
}

int main(void)
{
	int r, c;
	LinkedStackType s;
	
	init(&s);
	here = entry;
	while(maze[here.r][here.c]!='x')
	{
		r = here.r;
		c = here.c;
		
		maze[r][c] = '.';
		
		push_loc(&s, r-1, c);
		push_loc(&s, r+1, c);
		push_loc(&s, r, c-1);
		push_loc(&s, r, c+1);
		
		if(is_empty(&s))
		{
			printf("실패\n");
			
			return 0;
		}
		else
			here = pop(&s);
	}
	printf("성공\n");
}
