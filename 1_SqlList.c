/*
 *@authuor Hive
 *@Description:SqList
 *@Date:2020/9/24
 */

/*ADT_Of_SqList*/
// int IninList(SqList *L)
// int ClearList(SqList *L)
// int DestroyList(SqList *L)
// int ListEmpty(SqList L)
// int ListLength(SqList L)
// int GetElem(SqList L,int i,ElemType *e)
// int LocateElem(SqList L,ElemType e)
// int PriorElem(SqList L,ElemType cur,ElemType pre)
// int NextElem(SqList L,ElemType cur,ElemType next)
// int ListInsert(SqList *L,int i,ElemType e)
// int ListDelete(SqList *L,int i,ElemType *e)
// int ListTraverse(SqList L)
// void MergeList(SqList La,SqList Lb,SqList* Lc)
// void UnionList(SqList *La,SqList Lb)

#include<stdio.h>
#include<stdlib.h>

#define ElemType int
#define INIT_SIZE 100
#define MEMADD 10

typedef struct
{
    ElemType *elem;
    int length;
    int listsize;
}SqList;

int InitList(SqList *L)
{
    L->elem=(ElemType *)malloc(INIT_SIZE*sizeof(ElemType));
    if(!L->elem) exit(-2);
    L->length=0;
    L->listsize=INIT_SIZE;
    return 1;
}

int ClearList(SqList *L)
{
    L->length=0;
    return 1;
}

int ListEmpty(SqList L)
{
    if(L.length==0)
        return 1;
    return 0;
}

int ListLength(SqList L)
{
    return L.length;
}

int GetElem(SqList L,int i,ElemType *e)
{
    if(L.length==0 || i<1 || i>L.length)
            return 0;
    *e=L.elem[i-1];
    return 1;
}

int LocateElem(SqList L,ElemType e)
{
    int i;
    if (L.length==0)
            return 0;
    for(i=0;i<L.length;i++)
    {
        if (L.elem[i]==e)
            break;
    }
    if(i>=L.length)
        return 0;
    return i+1;
}

ElemType PriorElem(SqList L,ElemType cur,ElemType pre)
{
    return L.elem[cur-1];
}

int NextElem(SqList L,ElemType cur,ElemType next)
{
    return L.elem[cur-1];
}

int ListInsert(SqList *L,int i,ElemType e)
{
    if(i<1||i>L->length+1) return 0;
    //i>L->length+1,不能写成i>L->length 否则空表插第一个元素时1>0
    if(L->length >= L->listsize)
    {
        ElemType *newbase=(ElemType *)realloc
        (L->elem,(L->listsize+MEMADD)*sizeof(ElemType));
        //内存已满，增加分配
        if(!newbase) exit(-2);
        L->elem=newbase;
        L->listsize+=MEMADD;
    }
    ElemType *p,*q=&(L->elem[i-1]);
    for(p=&(L->elem[L->length-1]);p>=q;p--)
        *(p+1)=*p;
    *q=e;
    L->length++;
    return 1;
}

int ListDelete(SqList *L,int i,ElemType *e)
{
    if(i<1||i>L->length) return 0;
    *e=L->elem[i-1];
    ElemType *p;
    for(p=&(L->elem[i-1]);p<&(L->elem[L->length-1]);p++)
        *p=*(p+1);
    L->length--;
    return 1;
}

int visit(ElemType e)
{
    printf("%d ",e);
    return 1;
}

int ListTraverse(SqList L)
{
    for(int i=0;i<L.length;i++)
    {
        visit(L.elem[i]);
    }
    printf("\n");
    return 1;
}

void MergeList(SqList La,SqList Lb,SqList* Lc)//两表归并(La,Lb已有序)
{
    int i=1;
    ElemType* pa=La.elem;
    ElemType* pb=Lb.elem;
    Lc->listsize=La.length+Lb.length; Lc->listsize=Lc->length;
    Lc->elem=(ElemType*)malloc(Lc->listsize*sizeof(ElemType));
    if(!Lc->elem) exit(-2);
    ElemType* pc=Lc->elem;
    while(pa<=La.elem+La.length-1&&pb<=Lb.elem+Lb.length-1)
    {
        if(*pa<=*pb) ListInsert(Lc,i++,*pa++);
        else ListInsert(Lc,i++,*pb++);
    }
    while(pa<=La.elem+La.length-1) ListInsert(Lc,i++,*pa++); //*pc++=*pa++;
    while(pb<=Lb.elem+Lb.length-1) ListInsert(Lc,i++,*pb++); //*pc++=*pb++;
}

void UnionList(SqList *La,SqList Lb)//去重
{
	int La_len,Lb_len,i;
	ElemType e;
	La_len=ListLength(*La);
	Lb_len=ListLength(Lb);
	for (i=1;i<=Lb_len;i++)
	{
		GetElem(Lb,i,&e);
		if (!LocateElem(*La,e))
			ListInsert(La,++La_len,e);
	}
}

int main()
{
    SqList L1,L2,L3;
    InitList(&L1);
    //每创建一个新表必须初始化，忘记初始化直接使用会报错
    InitList(&L2);
    InitList(&L3);
    for(int i=1;i<=200;i++)
    {
        ListInsert(&L1,i,i);
        ListInsert(&L2,i,i);
    }
    ListTraverse(L1);
    MergeList(L1,L2,&L3);
    ListTraverse(L3);
    UnionList(&L1,L2);
    ListTraverse(L1);
    system("pause");
}
