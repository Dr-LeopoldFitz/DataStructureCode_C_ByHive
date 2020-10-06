/*
 *@authuor Hive
 *@Description:SqStack
 *@Date:2020/10/6
 */

/*ADT_Of_SqStack*/
// int InitStack(SqStack* S)
// int ClearStack(SqStack* S)
// int StackEmpty(SqStack S)
// int StackLength(SqStack S)
// int GetTop(SqStack S,ElemType* e)
// int Push(SqStack* S,ElemType e)
// int Pop(SqStack* S,ElemType* e)
// int StackTraverse(SqStack S)

#include<stdio.h>
#include<stdlib.h>

#define INIT_SIZE 20
#define ElemType int
#define INCREACEMENT 10

typedef struct
{
    ElemType* base;
    ElemType* top;
    int stacksize;
}SqStack;

/*第二种声明方式*/
// typedef struct
// {
//      int data[INIT_SIZE];
//      int top; /* 用于栈顶指针 */
// }SqStack;

int InitStack(SqStack* S)
{
    S->base=(ElemType*)malloc(INIT_SIZE*sizeof(ElemType));
    if(!(S->base)) exit(-2);
    S->top=S->base;
    S->stacksize=INIT_SIZE;
    return 1;
}

int ClearStack(SqStack* S)
{
    S->top=S->base;
    return 1;
}

int StackEmpty(SqStack* S)
{
    if(S->base==S->top) return 1;
    else return 0;
}

int StackLength(SqStack* S)
{
    return(S->top-S->base);
}

int GetTop(SqStack* S,ElemType* e)
{
    if(S->top==S->base) return 0;
    *e=*((S->top)-1);
    return 1;
}

int Push(SqStack* S,ElemType e)
{
    if(S->top-S->base>=S->stacksize)
    {
        S->base=(ElemType*)realloc(S->base,
        (S->stacksize+INCREACEMENT)*sizeof(ElemType));
        if(!S->base) exit(-2);

        S->top=S->base+S->stacksize;
        S->stacksize+=INCREACEMENT;
    }
    *(S->top++)=e;
    return 1;
}

int Pop(SqStack* S,ElemType* e)
{
    if(S->top==S->base) return 0;
    *e=*(--(S->top));
    return 1;
}

int StackTraverse(SqStack* S)
{
    while(S->top!=S->base)
    {

        S->top--;
        printf("%d\n",*(S->top));
    }
    return 1;
}

int main()
{
    SqStack S;
    InitStack(&S);
    Push(&S,1);
    Push(&S,2);
    Push(&S,3);
    // int k=100;
    // int* e;
    // Pop(&S,e);
    // printf("%d\n",*e);
    // printf("*****\n");
    // StackTraverse(&S);
    int e;
    GetTop(&S,&e);
    StackTraverse(&S);
}

/*关于指针类型的++*/

/*测试性说明程序

#include<stdio.h>
#include<stdlib.h>
int main()
{
    int *a=(int*)malloc(5*sizeof(int));
    a[0]=1; a[1]=2; a[2]=3; a[3]=4; a[4]=5;
    for(int i=0;i<=4;i++)
    {
        printf("%d\n",*(a++));
    }
}
//指针类型的++不是一次加1，++, --的跳转的单位是其指向的数据类型，
//如果指针指向一般数据类型，则++跳转到下一地址；
//如果指针指向多维数组的一行，++则跳转到下一行
//指针型不能直接赋常量，只能赋变量，指针作为参数不能修改，若要修改需要传入指针的指针，如下
#include<stdio.h>
int c=3;
int hive(int* alv)
{
    *alv=c;
    return 1;
}
int main()
{
    int alv;
    int k=5;
    hive(&alv);
    printf("%d\n",alv);
    return 0;
}

//alv最后值为3，若写作如下2个版本均不能改变alv的值
1.
#include<stdio.h>
int c=3;
int hive(int* alv)
{
    alv=&c;
    return 1;
}
int main()
{
    int alv;
    int k=5;
    hive(&alv);
    printf("%d\n",alv);
    return 0;
}

2.
#include<stdio.h>
int c=3;
int hive(int* alv)
{
    alv=&c; //在hive函数中的alv和主函数里的alv不是同一个指针
    //printf("%d\n",*alv);
    return 1;
}
int main()
{
    int* alv;
    int k=5;
    hive(alv);
    printf("%d\n",*alv);
    return 0;
}

//若要将指针作为参数传入函数并在函数内改变指针，只能返回一个指针类型，
//因为传入的形参只是主函数内指针的地址域，不含数据域
//所以主函数内原指针的指针域不会被修改，但可以通过传入的指针域解引用来达到修改主函数指针数据域的效果
//所以下面的修改版也能够改变alv的值
#include<stdio.h>
int c=3;
int hive(int* alv)
{
    *alv=c;
    return 1;
}
int main()
{
    int* alv;
    int k=5;
    hive(alv);
    printf("%d\n",*alv);
    return 0;
}

//关于主函数内Pop部分的另一种写法
int e;
Pop(&S,&e);

*/