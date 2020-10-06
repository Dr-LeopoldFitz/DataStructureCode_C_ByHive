/*
 *@authuor Hive
 *@Description:设有n个人站成一排,从左向右的编号分别为1～n,现在从左往右报数“1,2,3,1,2,3…”
 *@Description:数到“1、2”的人出列,数到“3”的立即站到队伍的最右端
 *@Description:报数过程反复进行，直到n个人都出列为止。要求给出他们的出列顺序
 *@Description:注:前面均为2_Queue中实现的内容,题目算法为最后一个函数 void QueueNumber(LinkQueue *Q,int n)
 *@Date:2020/10/6
 */

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

int InitQueue(LinkQueue* Q);
int DestroyQueue(LinkQueue* Q);
int ClearQueue(LinkQueue* Q);
int QueueEmpty(LinkQueue Q);
int QueueLength(LinkQueue Q);
int GetHead(LinkQueue Q,ElemType* e);
int EnQueue(LinkQueue* Q,ElemType e);
int DeQueue(LinkQueue* Q,ElemType* e);
int QueueTraverse(LinkQueue Q);

void QueueNumber(LinkQueue *Q,int n)
{
	int e = 0;
	for (int i =1; i <= n; i++)
		EnQueue(Q, i);	
	while (!QueueEmpty(*Q))
	{
		DeQueue(Q, &e);
		printf("%d ", e); //1
        DeQueue(Q, &e);
		printf("%d ", e); //2
		if (!QueueEmpty(*Q) )
		{
			DeQueue(Q, &e);
			EnQueue(Q, e);
		}
	}
	printf("\n");
}

/*TestExample

***Input***
10

***Output***

1 2 4 5 7 8 10 3 9 6

*/

int main()
{
    int n;
	printf("输入人数N: ");
    scanf("%d",&n);
	printf("出队顺序: ");
    LinkQueue Q;
    InitQueue(&Q);
    QueueNumber(&Q,n);
    system("pause");
    return 0;
}

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

/*
设有n个人站成一排,从左向右的编号分别为1～n,现在从左往右报数“1,2,3,1,2,3…”
数到“1、2”的人出列,数到“3”的立即站到队伍的最右端
报数过程反复进行，直到n个人都出列为止。要求给出他们的出列顺序
注:前面的函数均为2_Queue中实现的内容,题目算法为最后一个函数 void QueueNumber(LinkQueue *Q,int n)
*/
