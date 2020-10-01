/*
 *@authuor Hive
 *@Description:StaticLinkList
 *@Description:数组第一个元素存放备用链表的第一个结点的下标
 *@Description:最后一个元素存放第一个有数值的元素的下标,相当于头结点作用,链表为空时为0
 *@Date:2020/10/1
 */

/*ADT_Of_StaticLinkList*/
// int InitList(StaticLinkList space) 
// int Malloc_SSL(StaticLinkList space) 
// int Free_SSL(StaticLinkList space, int k) 
// int ListLength(StaticLinkList L)
// int ListInsert(StaticLinkList L, int i, ElemType e)   
// int ListDelete(StaticLinkList L, int i)   
// int ListTraverse(StaticLinkList L)

#include<stdio.h>
#include<stdlib.h>

#define ElemType char
#define INIT_SIZE 100

typedef struct 
{
    char data;
    int cur;  /* 游标(Cursor) ，为0时表示无指向(空指针) */
} Component,StaticLinkList[INIT_SIZE];

/* 将一维数组space中各分量链成一个备用链表，space[0].cur为头指针 */
int InitList(StaticLinkList space) 
{
	int i;
	for (i=0; i<INIT_SIZE-1; i++)  
		space[i].cur = i+1;
	space[INIT_SIZE-1].cur = 0; /* 目前静态链表为空，最后一个元素的cur为0 */
	return 1;
}

/* 若备用空间链表非空，则返回分配的结点下标，否则返回0 */
int Malloc_SLL(StaticLinkList space) 
{ 
	int i = space[0].cur; //当前数组第一个元素的cur存的值就是要返回的第一个备用空闲的下标
	if (space[0]. cur)         
	    space[0]. cur = space[i].cur; // 把它的下一个分量用来做备用
	return i;
}

int Free_SLL(StaticLinkList space, int k) 
{  
    space[k].cur = space[0].cur; //相当于头插法将空闲结点加入备用链表
    space[0].cur = k;         
    return 1;
}

int ListLength(StaticLinkList L)
{
    int j=0;
    int i=L[INIT_SIZE-1].cur;
    while(i)
    {
        i=L[i].cur;
        j++;
    }
    return j;
}

/*  在L中第i个元素之前插入新的数据元素e   */
int ListInsert(StaticLinkList L, int i, ElemType e)   
{  
    int j, k, l;   
    k = INIT_SIZE - 1;
    if (i < 1 || i > ListLength(L) + 1)   
        return 0;   
    j = Malloc_SLL(L);
    if (j)
    {
		L[j].data = e;
		for(l = 1; l <= i - 1; l++)   /* 找到第i个元素之前的位置 */
		   k = L[k].cur;  
                 
		L[j].cur = L[k].cur;
		L[k].cur = j;
		return 1;   
    }   
    return 0;   
}

/*  删除在L中第i个数据元素   */
int ListDelete(StaticLinkList L, int i)   
{ 
    int j, k;   
    if (i < 1 || i > ListLength(L))   
        return 0;   
    k = INIT_SIZE - 1;   
    for (j = 1; j <= i - 1; j++)   
        k = L[k].cur;   
    j = L[k].cur;   
    L[k].cur = L[j].cur;   
    Free_SLL(L, j);   
    return 1;   
} 

int ListTraverse(StaticLinkList L)
{
    int j=0;
    int i=L[INIT_SIZE-1].cur;
    while(i)
    {
            printf("%c ",L[i].data);
            i=L[i].cur;
            j++;
    }
    return j;
    printf("\n");
    return 1;
}


int main()
{
    StaticLinkList L;
    int i;
    i=InitList(L);

    i=ListInsert(L,1,'F');  i=ListInsert(L,1,'E');
    i=ListInsert(L,1,'D');
    i=ListInsert(L,1,'B');  i=ListInsert(L,1,'A');

    printf("\n在L的表头依次插入FEDBA后：\nL.data=");
    ListTraverse(L); 

    i=ListInsert(L,3,'C');
    printf("\n在L的“B”与“D”之间插入“C”后：\nL.data=");
    ListTraverse(L); 

    i=ListDelete(L,1);
    printf("\n在L的删除“A”后：\nL.data=");
    ListTraverse(L); 

    printf("\n");
    system("pause");
    return 0;
}

