/*
 *@authuor Hive
 *@Description:LinkList
 *@Date:2020/9/29
 */

/*ADT_Of_LinkList*/
// int InitList(LinkList *L)
// int ClearList(LinkList *L)
// int DestroyList(LinkList *L)
// int ListEmpty(LinkList L)
// int ListLength(LinkList L)
// int GetElem(LinkList L,int i,ElemType *e)
// int LocateElem(LinkList L,ElemType e)
// int ListInsert(LinkList *L,int i,ElemType e)
// int ListDelete(LinkList *L,int i,ElemType *e)
// int ListTraverse(LinkList L)
// void CreateList_Tail(LinkList* L, int n)
// void CreateList_Head(LinkList* L, int n)
// void MergeList(LinkList La,LinkList Lb,LinkList* Lc)

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ElemType int
#define INIT_SIZE 100

typedef struct Node
{
    ElemType data;
    struct Node* next;
}Node,* LinkList;

int InitList(LinkList *L)
{
    *L=(LinkList)malloc(sizeof(Node));
    if(!*L)
        exit(-2);
    (*L)->next=NULL;
    return 1;
}

int ClearList(LinkList *L)
{
    LinkList p,q;
    p=(*L)->next;
    while(p)
    {
        q=p->next;
        free(p);
        p=q;
    }
    (*L)->next=NULL;
    return 1;
}

int DestroyList(LinkList *L)
{
    LinkList q;
    while(*L)
    {
        q=(*L)->next;
        free(*L);
        *L=q;
    }
    return 1;
}

int ListEmpty(LinkList L)
{
    if(L->next)
        return 0;
    else
        return 1;
}

int ListLength(LinkList L)
{
    int i=0;
    LinkList p=L->next;
    while(p)
    {
        i++;
        p=p->next;
    }
    return i;
}

int GetElem(LinkList L,int i,ElemType *e)
{
    int j=1;
    LinkList p=L->next;
    while(p&&j<i)
    {
        p=p->next;
        j++;
    }
    if ( !p || j>i )
		return 0;
	*e = p->data;
	return 1;
}

int LocateElem(LinkList L,ElemType e)
{
    int i=0;
    LinkList p=L->next;
    while(p)
    {
        i++;
        if(p->data==e)
            return i;
        p=p->next;
    }
    return 1;
}

int ListInsert(LinkList *L,int i,ElemType e)
{
    int j=1;
    LinkList p,q;
    p=*L;
    while(p&&j<i)
    {
        p=p->next;
        j++;
    }
    if (!p || j > i)
		return 0;
    q=(LinkList)malloc(sizeof(Node));
    q->data=e;
    q->next=p->next;
    p->next=q;
    return 1;
}

int ListDelete(LinkList *L,int i,ElemType *e)
{
    int j=1;
    LinkList p,q;
    p=*L;
    while(p->next&&j<i) //这里用p->next作为临界标志是为了方便记录被删除结点的前驱
    {
        p=p->next;
        j++;
    }
    if(!(p->next)||j>i)
        return 0;
    
    q=p->next;
    p->next=q->next;
    *e=q->data;
    free(q);
    return 1;
}

int ListTraverse(LinkList L)
{
    LinkList p=L->next;
    while(p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
    return 1;
}

void CreateList_Tail(LinkList* L, int n)
{
    LinkList p,r;
	int i;
	srand(time(0)); //初始化随机数种子
	*L = (LinkList)malloc(sizeof(Node));
	r=*L;
	for (i=0; i<n; i++)
	{
		p = (LinkList)malloc(sizeof(Node));
		p->data = rand()%100+1; //随机生成100以内的数字
		r->next=p;
		r = p; //将当前的新结点定义为表尾终端结点
	}
	r->next = NULL; 
}

void CreateList_Head(LinkList* L, int n)
{
    LinkList p;
    int i;
    srand(time(0));
    *L=(LinkList)malloc(sizeof(Node));
    (*L)->next=NULL;
    for(int i=0;i<n;i++)
    {
        p=(LinkList)malloc(sizeof(Node));
        p->data=rand()%100+1;
        p->next=(*L)->next;
        (*L)->next=p;
    }

}

void MergeList(LinkList* La,LinkList* Lb,LinkList* Lc)
{
    LinkList pa=(*La)->next;
    LinkList pb=(*Lb)->next;
    LinkList pc=*Lc;
    while(pa&&pb)
    {
        if(pa->data<=pb->data)
        {
            pc->next=pa;
            pc=pa;
            pa=pa->next;
        }
        else
        {
            pc->next=pb;
            pc=pb;
            pb=pb->next;
        }
    }
     pc->next=(pa?pa:pb);

    // DestroyList(La);
    // DestroyList(Lb);
    // 起初写的时候犯了如上注释的错误，
    // 忘记了实际上Lc只新申请了一个头结点，
    // 实际数据还在La,Lb里没有移动，不可销毁La,Lb
}

int main()
{
    LinkList La,Lb,Lc;
    InitList(&La);
    InitList(&Lb);
    InitList(&Lc);
    // CreateList_Head(&La,20);
    // CreateList_Head(&Lb,20);

    for(int i=1;i<=10;i++)
    {
        ListInsert(&La,i,i);
        ListInsert(&Lb,i,i+100);
    }
    ListTraverse(La);
    ListTraverse(Lb);
    MergeList(&La,&Lb,&Lc);
    ListTraverse(Lc);
    system("pause");
    return 0;
}
