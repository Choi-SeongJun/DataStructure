#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef int element;
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

void display(LinkedListType *list)
{
	ListNode *p = list->head;
	printf("( ");
	while(p!=NULL)
	{
		printf("%d ", p->data);
		p = p->link;
	}
	printf(")\n");
}

int is_in_list(LinkedListType *list, element item)
{
	ListNode *p = list->head;
	while(p!=NULL)
	{
		if(p->data == item) return TRUE;
		p = p->link;
	}
	return FALSE;
}

int main(void)
{
	LinkedListType list1;
	
	init(&list1);
	add(&list1, 0, 20);
	add_last(&list1, 30);
	add_first(&list1, 10);
	add_last(&list1, 40);
	
	display(&list1);
	
	remove(&list1, 3);
	display(&list1);
	
	remove(&list1, 0);
	display(&list1);
	
	printf("%s\n", is_in_list(&list1, 20)==TRUE ? "성공" : "실패");
	printf("%d\n", get_entry(&list1, 0));
	
	return 0;
}
