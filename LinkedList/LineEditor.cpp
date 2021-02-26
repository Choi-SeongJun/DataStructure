#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR_PER_LINE 1000
#define MAX_NAME 256

#define TRUE 1
#define FALSE 0

typedef struct {
	char a[MAX_CHAR_PER_LINE];
} element;

typedef struct ListNode{
	element data;
	struct ListNode *link;
} ListNode;

typedef struct{
	int length;
	ListNode *head;
} LinkedListType;

void init(LinkedListType *list)
{
	if(list==NULL) return;
	list->length = 0;
	list->head = NULL;
}
void error(const char *message)
{
	fprintf(stderr, "%s", message);
	exit(1);
}

void warning(const char *message)
{
	fprintf(stderr, "%s\n", message);
}

int is_empty(LinkedListType *list)
{
	if(list->length==0) return TRUE;
	
	return FALSE;
}

int get_length(LinkedListType *list)
{
	return list->length;
}
ListNode *get_node_at(LinkedListType *list, int pos)
{
	int i;
	ListNode *tmp_node = list->head;
	if(pos<0) return NULL;
	for(i=0; i<pos; i++)
		tmp_node = tmp_node->link;
	return tmp_node;
}

void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
	if(*phead==NULL)
	{
		new_node->link = NULL;
		*phead = new_node;
	}
	else if(p == NULL)
	{
		new_node->link = *phead;
		*phead = new_node;
	}
	else
	{
		new_node->link = p->link;
		p->link = new_node;
	}
}

void remove_node(ListNode **phead, ListNode *p, ListNode *removed)
{
	if(p==NULL)
		*phead = (*phead)->link;
	else
		p->link = removed->link;
	free(removed);
}

void add(LinkedListType *list, int position, element data)
{
	ListNode *p;
	ListNode *node;
	if((position>=0)&&(position<=list->length))
	{
		ListNode *node = (ListNode *)malloc(sizeof(ListNode));
		if(node==NULL) error("메모리 할당 오류");	
		node->data = data;
		
		p = get_node_at(list, position-1);
		insert_node(&(list->head), p, node);
		list->length++;
	}
}
 
void add_last(LinkedListType *list, element data)
{
	add(list, get_length(list), data);
}

void add_first(LinkedListType *list, element data)
{
	add(list, 0, data);
}

void remove(LinkedListType *list, int pos)
{
	ListNode *p;
	ListNode *removed;
	if((pos>=0)&&(pos<list->length))
	{
		p = get_node_at(list, pos-1);
		removed = get_node_at(list, pos);
		remove_node(&(list->head), p, removed);
		list->length--;
	}
}

element get_entry(LinkedListType *list, int pos)
{
	ListNode *p;
	if(pos>=list->length) error("위치 오류");
	p = get_node_at(list, pos);
	return p->data;
}

void clear(LinkedListType *list)
{
	int i;
	int length = list->length;
	for(i=0; i<length; i++)
		remove(list, 0);
}

void display(LinkedListType *buffer)
{
	int i;
	ListNode *tmp_node = buffer->head;
	
	printf("***************\n");
	for(i=0; i<buffer->length; i++)
	{
		printf("%s", tmp_node->data.a);
		tmp_node = tmp_node->link;
	}
	printf("***************\n");
}

void help()
{
	printf("***************\n");
	printf("i : 입력\n");
	printf("d : 삭제\n");
	printf("r : 파일읽기\n");
	printf("w : 파일쓰기\n");
	printf("q : 종료\n");
	printf("***************\n");
}

// 디스크 파일로부터 데이터를 읽는다. 
void read_file(LinkedListType *buffer)
{
	char fname[MAX_NAME];
	FILE *fd;
	element p;
	
	if(!is_empty(buffer))
		clear(buffer);
	
	init(buffer);
	
	printf("파일이름 : ");
	scanf("%s", fname);
	
	if((fd=fopen(fname, "r")) == NULL)
	{
		warning("파일을 열 수 없습니다.");
		return;
	}
	
	while(fgets(p.a, MAX_CHAR_PER_LINE, fd))
		add_last(buffer, p);
		
	fclose(fd);
	
	display(buffer);
}

void write_file(LinkedListType *buffer)
{
	char fname[MAX_NAME];
	FILE *fd;
	element p;
	int i;
	
	printf("파일이름 : ");
	scanf("%s", fname);
	
	if((fd=fopen(fname, "w"))==NULL)
	{
		warning("파일을 쓸 수 없습니다.");
		return;
	}
	for(i=0; i<get_length(buffer); i++)
	{
		p = get_entry(buffer, i);
		fputs(p.a, fd);
	}
	fclose(fd);
	display(buffer);
}

void delete_line(LinkedListType *buffer)
{
	int position;
	
	if(is_empty(buffer))
		printf("지울 라인이 없습니다.\n");
	else
	{
		printf("지우고 싶은 라인 번호를 입력하세요.\n");
		scanf("%d", &position);
		remove(buffer, position);
	}
	display(buffer);
}

void insert_line(LinkedListType *buffer)
{
	int position;
	char line[MAX_CHAR_PER_LINE];
	element p;
	
	printf("입력 행 번호를 입력하세요 : ");
	scanf("%d", &position);
	
	printf("내용을 입력하세요 : ");
	fflush(stdin);
	fgets(line, MAX_CHAR_PER_LINE, stdin);
	
	strcpy(p.a, line);
	add(buffer, position, p);
	
	display(buffer);
}

void do_command(LinkedListType *buffer, char command)
{
	switch(command)
	{
		case 'd':
			delete_line(buffer);
			break;
		case 'i':
			insert_line(buffer);
			break;
		case 'r':
			read_file(buffer);
			break;
		case 'w':
			write_file(buffer);
			break;
		case 'q':
			break;
	}
}

int main(void)
{
	char command;
	LinkedListType buffer;
	
	init(&buffer);
	
	do{
		help();
		command = getchar();
		do_command(&buffer, command);
		fflush(stdin);
	} while(command!='q');
}
