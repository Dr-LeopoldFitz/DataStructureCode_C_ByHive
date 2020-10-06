/*
 *@authuor Hive
 *@Description:LinkStack
 *@Date:2020/10/6
 */

/*ADT_Of_LinkStack*/
// int InitStack(LinkStack *S)
// int ClearStack(LinkStack *S)
// int StackEmpty(LinkStack S)
// int StackLength(LinkStack S)
// int GetTop(LinkStack S,int *e)
// int Push(LinkStack *S,int e)
// int Pop(LinkStack *S,int *e)
// int StackTraverse(LinkStack S)

#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 20

typedef struct StackNode
{
    int data;
    struct StackNode *next;
}StackNode,*LinkStackPtr;
//注意*LinkStackPtr之前是逗号，类似于int a,b; 的逗号
//等价于 typedef struct StackNode* LinkStackPtr

typedef struct
{
    LinkStackPtr top; //头指针
    int count; //栈内元素数量
}LinkStack;

/*  构造一个空栈S */
int InitStack(LinkStack *S)
{ 
    S->top = (LinkStackPtr)malloc(sizeof(StackNode));
    if(!S->top)
        return 0;
    S->top=NULL;
    S->count=0;
    return 1;
}

/* 把S置为空栈 */
int ClearStack(LinkStack *S)
{ 
    LinkStackPtr p,q;
    p=S->top;
    while(p)
    {  
        q=p;
        p=p->next;
        free(q);
    } 
    S->count=0;
    return 1;
}

/* 若栈S为空栈，则返回1，否则返回0 */
int StackEmpty(LinkStack S)
{ 
    if (S.count==0)
        return 1;
    else
        return 0;
}

/* 返回S的元素个数，即栈的长度 */
int StackLength(LinkStack S)
{ 
    return S.count;
}

/* 若栈不空，则用e返回S的栈顶元素，并返回1；否则返回0 */
int GetTop(LinkStack S,int *e)
{
    if (S.top==NULL)
        return 0;
    else
        *e=S.top->data;
    return 1;
}

/* 插入元素e为新的栈顶元素 */
int Push(LinkStack *S,int e)
{
    LinkStackPtr s=(LinkStackPtr)malloc(sizeof(StackNode)); 
    s->data=e; 
    s->next=S->top;	/* 把当前的栈顶元素赋值给新结点的直接后继*/
    S->top=s;         /* 将新的结点s赋值给栈顶指针 */
    S->count++;
    return 1;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回1；否则返回0 */
int Pop(LinkStack *S,int *e)
{ 
    LinkStackPtr p;
    if(StackEmpty(*S))
        return 0;
    *e=S->top->data;
    p=S->top;					/* 将栈顶结点赋值给p*/
    S->top=S->top->next;    /* 使得栈顶指针下移一位，指向后一结点*/
    free(p);   
    S->count--;
    return 1;
}

int StackTraverse(LinkStack S)
{
    LinkStackPtr p;
    p=S.top;
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
        int j;
        LinkStack s;
        int e;
        if(InitStack(&s)==1)
                for(j=1;j<=10;j++)
                        Push(&s,j);
        printf("栈中元素依次为：");
        StackTraverse(s);
        Pop(&s,&e);
        printf("弹出的栈顶元素 e=%d\n",e);
        printf("栈空否：%d(1:空 0:否)\n",StackEmpty(s));
        GetTop(s,&e);
        printf("栈顶元素 e=%d 栈的长度为%d\n",e,StackLength(s));
        ClearStack(&s);
        printf("清空栈后，栈空否：%d(1:空 0:否)\n",StackEmpty(s));
        system("pause");
        return 0;
}