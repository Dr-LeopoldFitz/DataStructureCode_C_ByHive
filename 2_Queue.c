/*
 *@authuor Hive
 *@Description:Queue
 *@Date:2020/10/6
 */

/*ADT_Of_Queue*/
// int InitQueue(LinkQueue* Q)
// int DestroyQueue(LinkQueue* Q)
// int ClearQueue(LinkQueue* Q)
// int QueueEmpty(LinkQueue Q)
// int QueueLength(LinkQueue Q)
// int GetHead(LinkQueue Q,ElemType* e)
// int EnQueue(LinkQueue* Q,ElemType e)
// int DeQueue(LinkQueue* Q,ElemType* e)
// int QueueTraverse(LinkQueue Q)

#include<stdio.h>
#include<stdlib.h>

#define ElemType int

typedef struct QNode
{
    ElemType data;
    struct QNode* next;
}QNode,*QueuePtr;

typedef struct
{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

int InitQueue(LinkQueue* Q)
{
    Q->front=Q->rear=(QueuePtr)malloc(sizeof(QNode));
    if(!Q->front) exit(-2);
    Q->front->next=NULL;
    return 1;
}

int DestroyQueue(LinkQueue* Q)
{
    while(Q->front)
	{
		Q->rear=Q->front->next;
		free(Q->front);
		Q->front=Q->rear;
	}
	return 1;
}

int ClearQueue(LinkQueue* Q)
{
	QueuePtr p,q;
	Q->rear=Q->front;
	p=Q->front->next;
	Q->front->next=NULL;
	while(p)
	{
		q=p;
		p=p->next;
		free(q);
	}
	return 1;
}

int QueueEmpty(LinkQueue Q)
{ 
	if(Q.front==Q.rear)
		return 1;
	else
		return 0;
}

int QueueLength(LinkQueue Q)
{ 
	int i=0;
	QueuePtr p;
	p=Q.front;
	while(Q.rear!=p)
	{
		i++;
		p=p->next;
	}
	return i;
}

int GetHead(LinkQueue Q,ElemType* e)
{ 
	QueuePtr p;
	if(Q.front==Q.rear)
		return 0;
	p=Q.front->next;
	*e=p->data;
	return 1;
}

int EnQueue(LinkQueue* Q,ElemType e)
{
    QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
    if(!p) exit(-2);
	p->data=e;
	p->next=NULL;
	Q->rear->next=p;
	Q->rear=p;
	return 1;
}

int DeQueue(LinkQueue* Q,ElemType* e)
{
	QueuePtr p;
	if(Q->front==Q->rear)
		return 0;
	p=Q->front->next;
	*e=p->data;
	Q->front->next=p->next;
	if(Q->rear==p)
		Q->rear=Q->front;
	free(p);
	return 1;
}

int QueueTraverse(LinkQueue Q)
{
	QueuePtr p;
	p=Q.front->next;
	while(p)
	{
		printf("%d ",p->data);
		p=p->next;
	}
	printf("\n");
	return 1;
}

int main()
{
	int i,d;
	LinkQueue q;
    InitQueue(&q);
	EnQueue(&q,-5); EnQueue(&q,5); EnQueue(&q,10);
	QueueTraverse(q);

	ClearQueue(&q);
	printf("清空队列后,q.front=%p q.rear=%p q.front->next=%p\n",q.front,q.rear,q.front->next);
	DestroyQueue(&q);
	printf("销毁队列后,q.front=%p q.rear=%p\n",q.front, q.rear);

	system("pause");
	return 0;
}
