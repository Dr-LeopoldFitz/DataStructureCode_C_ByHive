/*
 *@authuor Hive
 *@Description:StaticLinkList
 *@Description:数组第一个元素存放备用链表的第一个结点的下标
 *@Description:最后一个元素存放第一个有数值的元素的下标,相当于头结点作用,链表为空时为0
 *@Date:2020/10/1
 */

/*ADT_Of_StaticLinkList*/
// int InitSpace(StaticLinkList space) 
// int Malloc_SSL(StaticLinkList space) 
// int Free_SSL(StaticLinkList space, int k) 
// int ListLength(StaticLinkList L)
// int ListInsert(StaticLinkList L, int i, ElemType e)   
// int ListDelete(StaticLinkList L, int i)  
// int ClearList(StaticLinkList L)
// int GetElem(StaticLinkList L, int i, ElemType *e)
// int LocateElem(StaticLinkList L, ElemType e)
// int PriorElem(StaticLinkList L, ElemType cur, ElemType *pre)
// int NextElem(StaticLinkList L, ElemType cur, ElemType *next)
// void difference(StaticLinkList *space)
// int ListTraverse(StaticLinkList L)

/*TestExample

①
3 4
1 2 3
2 5 3 4

②
3 4
7 1 3
2 5 3 4

*/

#include<stdio.h>
#include<stdlib.h>

#define ElemType char
#define INIT_SIZE 1000

typedef struct 
{
    char data;
    int cur;  /* 游标(Cursor) ，为0时表示无指向(空指针) */
} Component,StaticLinkList[INIT_SIZE];

/* 将一维数组space中各分量链成一个备用链表，space[0].cur为头指针 */
int InitSpace(StaticLinkList space) 
{
	int i;
	for (i=0; i<INIT_SIZE-1; i++)  
		space[i].cur = i+1;
	space[INIT_SIZE-1].cur = 0; /* 目前静态链表为空，最后一个元素的cur为0 */
	return 1;
}

/* 若备用空间链表非空，则返回分配的结点下标，否则返回0 */
int Malloc_SL(StaticLinkList space) 
{ 
	int i = space[0].cur; //当前数组第一个元素的cur存的值就是要返回的第一个备用空闲的下标
	if (space[0]. cur)         
	    space[0]. cur = space[i].cur; // 把它的下一个分量用来做备用
	return i;
}

int Free_SL(StaticLinkList space, int k) 
//将下标为k的结点加入备用链表
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
    j = Malloc_SL(L);
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
    Free_SL(L, j);   
    return 1;   
} 

int ClearList(StaticLinkList L)
{
	int p,q;
	if(!L)
		return -1;
    p=L[INIT_SIZE-1].cur;
    while(p)
    {
        q=L[p].cur;
        Free_SL(L,p);
        p=q;
    }
    L[INIT_SIZE-1].cur=0;
	return 1;
}

int GetElem(StaticLinkList L, int i,ElemType* e)
{
	int count,p;
	if(!L || i<1 || i>=INIT_SIZE-1)
		return -2;
	count = 0;
	p = L[INIT_SIZE-1].cur;
	while(p)
	{
		count++;
		if(count==i)
		{
			*e = L[p].data;		
			return 1;
		}
		p = L[p].cur;
	}

    return -1;
} 

int LocateElem(StaticLinkList L, ElemType e)
{
	int k, count;
	count = 1;
	if(L && L[INIT_SIZE-1].cur)
	{
		k = L[INIT_SIZE-1].cur;
		while(k && L[k].data!=e)
		{
			count++;
			k = L[k].cur;	
		}
		
		if(k)
			return count;
	}
	
	return 0;			
} 

int PriorElem(StaticLinkList L, ElemType cur, ElemType *pre)
{
	int p, q;
	if(L)
	{
		p = L[INIT_SIZE-1].cur;
		if(p && L[p].data!=cur)
		{
			q = L[p].cur;
			while(q && L[q].data!=cur)
			{
				p = q;
				q= L[q].cur;
			}
			if(q) // 找到
			{
				*pre = L[p].data;
				return 1;			
			}
		}
	}
	return -1;
} 

int NextElem(StaticLinkList L, ElemType cur, ElemType *next)
{
	int p;
	if(L)
	{
		p =L[INIT_SIZE-1].cur;	
		while(p && L[p].data!=cur)
		    p = L[p].cur;

		if(p && L[p].cur)	//找到了cur且不是最后一个结点 
		{
			p = L[p].cur;
			*next = L[p].data;
			return 1;
		}	
	}
	
	return -1;
} 

void difference(StaticLinkList *space) 
//在一维数组space中建立表示集合(A-B)∪(B-A)的静态链表
//假设备用空间足够大
//space[0].cur为备用空间头结点下标,space[INIT_SIZE-1].cur为头结点下标
{
    int i,j,m,n,b,p,k;
    InitSpace(*space); // 初始化备用空间
    int r=INIT_SIZE-1; //静态链表最后一个结点不存数据，一般只用来存储头结点下标，起到类似头指针的作用
    printf("输入A、B元素个数: ");
    scanf("%d%d",&m,&n); //输入AB元素个数
    printf("输入A: ");
    for(j=1;j<=m;j++)
    {
        i=Malloc_SL(*space);
        scanf("%d",&(*space)[i].data);
        (*space)[r].cur=i; r=i; //插入到表尾,r指向S当前的最后结点
    }
    (*space)[r].cur=0; //尾结点指针为空

    printf("输入B: ");
    for(j=1;j<=n;j++) //输入B元素,若不在当前表中则插入,否则删除
    {
        scanf("%d",&b);
        p=INIT_SIZE-1;
        k=(*space)[p].cur; // k指向A中第一个结点
        while(k!=0 && (*space)[k].data!=b)
        {
            p=k;
            k=(*space)[k].cur;
        }

        if( k== 0 ) //当前表中不存在该元素，插入在r所指结点之后，且r位置不变
        {
            i=Malloc_SL(*space);
            (*space)[i].data=b;
            (*space)[i].cur=(*space)[r].cur;
            (*space)[r].cur=i;
        }
        else //该元素已在表中，删除
        {
            (*space)[p].cur=(*space)[k].cur;
            Free_SL(*space,k);
            if(r==k) //若删除的是r所指结点，则需修改尾指针
                r=p;
        }
        
    }
}

int ListTraverse(StaticLinkList L)
{
    int j=0;
    int i=L[INIT_SIZE-1].cur;
    while(i)
    {
            printf("%d ",L[i].data);
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
    InitSpace(L);

    i=ListInsert(L,1,'F');  i=ListInsert(L,1,'E');
    i=ListInsert(L,1,'D');
    i=ListInsert(L,1,'B');  i=ListInsert(L,1,'A');

    printf("在L的表头依次插入FEDBA后：\nL.data=");
    ListTraverse(L); 

    i=ListInsert(L,3,'C');
    printf("\n在L的“B”与“D”之间插入“C”后：\nL.data=");
    ListTraverse(L); 

    i=ListDelete(L,1);
    printf("\n在L的删除“A”后：\nL.data=");
    ListTraverse(L); 

    printf("\n\n\n");
    StaticLinkList sp;
    int s;
    difference(&sp);
    printf("A,B去掉两者相同的元素后后: ");
    ListTraverse(sp);
    printf("\n");
    system("pause");
    return 0;
}
