/*
 *@authuor Hive
 *@Description:Polynomial
 *@Date:2020/10/1
 */

/*ADT_Of_Polynomial*/
// int InitPolynomial(LinkList *l)
// int ListEmpty(LinkList *l)
// int cmp(int a1,int a2)
// int LocateTerm(LinkList *l,Node *p)
// int DestroyPoly(LinkList *l)
// Node* CreateNode()
// int SameExpPlus(LinkList *l,Node *p)
// int InsertNode(LinkList *l,Node *p)
// int TermPlus(LinkList *l,Node *p){
// int CreatePolynomial(LinkList *l,int m){
// int PolyTraverse(LinkList *l)
// LinkList AddPoly(LinkList *l1,LinkList *l2)
// int GetOpposite(LinkList *l)
// LinkList SubtractPoly(LinkList *l1,LinkList *l2)
// LinkList MultiplyPoly(LinkList *l1,LinkList *l2)

/*TestExample

2
2 3
2 4
3
3 6
4 3
3 7


*/

#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2

typedef struct
{
    double coef; // 系数 coefficient
    int exp; // 指数 exponent
}term,ElemType;
// 两个类型名:term用于本ADT(多项式的项),ElemType为LinkList数据对象名

typedef struct Node
{
    ElemType* data;
    struct Node* next;
}Node,* Link;

typedef struct LinkList
{
    Link head,tail;
    int len;
}LinkList;

/*多项式的初始化,建立头结点*/
int InitPolynomial(LinkList* l)
{
    Link p;
    p=(Link)malloc(sizeof(Node));
    if(!p)
        exit(OVERFLOW);
    p->next=NULL;
    (*l).head=(*l).tail=p;
    (*l).len=0;

    return OK;
}

/*判断多项式是否为空表*/
int ListEmpty(LinkList* l)
{
    return !(l->len);
}

/*整数比较函数*/
int cmp(int a1,int a2)
{
    if(a1>a2)
        return 1;
    else if(a1==a2)
        return 0;
    else
        return -1;
}

/*判断新节点的指数，定位节点在多项式中是否已经存在*/
int LocateTerm(LinkList* l,Node* p)
{

    Node* q=((*l).head)->next;
    while(q&&(q->data->exp!=p->data->exp))
    {
        q=q->next;
    }
    if(!q)
        return 0;
    else
        return 1;
}

/*销毁多项式*/
int DestroyPoly(LinkList* l)
{
    Node* p=l->head;
    Node* q;
    while(q)
    {
        q=p->next;
        free(p);
        p=q;
    }

    l->head=NULL; // 第一次写时忘记将头指针赋成NULL,导致仍然能输出被销毁的多项式(乱码)
    // 注：指针若free掉内存后不销毁会变成野指针，仍然存在且有时会出问题

    return OK;
}

/*创建一个结点*/
Node* CreateNode()
{
    Node* q=(Node*)malloc(sizeof(Node));
    q->data=(ElemType*)malloc(sizeof(ElemType));
    return q;
}

/*指数相等的项相加*/
int SameExpPlus(LinkList *l,Node *p)
{
    Node *q=((*l).head)->next;
    while(q && q->data->exp!=p->data->exp)
    {
        q=q->next;
    }
    if(!q)
        return OK;
    else
    {
        q->data->coef+=p->data->coef;
        return OK;
    }
}

/*插入新节点*/
int InsertNode(LinkList *l,Node *p)
{
    Node *q=((*l).head)->next;
    Node *prior=(*l).head;//q的前一个节点
    while(q&&q->data->exp < p->data->exp)
    {
        prior=q;
        q=q->next;
    }
    p->next=q;
    prior->next=p;
    l->len++;
    return OK;
}

/*向多项式加入项*/
int TermPlus(LinkList *l,Node *p){
    if(LocateTerm(l,p))
    {
        SameExpPlus(l,p);//指数相等时只需要系数相加
    }
    else
    {
        InsertNode(l,p);
    }
    return OK;
}

/*创建多项式m项的系数和指数*/
int CreatePolynomial(LinkList *l,int m){

    double coef; //系数coefficient
    int exp; //指数exponent
    for(int i=1;i<=m;i++)
    {
        printf("\n请输入第 %d 个系数和指数: ",i);
        Node* p=CreateNode();
        scanf("%lf",&(p->data->coef));
        scanf("%d",&(p->data->exp));
        TermPlus(l,p);
    }
    printf("\n********多项式创建完毕********\n\n");
    return 1;
}

/*循环输出多项式的系数和指数*/
int PolyTraverse(LinkList *l)
{
    if(!(l->head)) //不加此项时main函数最后一个操作(输出已被销毁的多项式)会出现异常
        return 0;
    Node *q=(l->head)->next;
    printf("多项式有 %d 个项:\n",l->len);

    while(q->next)
    {
        printf("%lf x^%d + ",q->data->coef,q->data->exp);
        q=q->next;
    }
    printf("%lf x^%d\n",q->data->coef,q->data->exp);

    return OK;
}

/*多项式的加法*/
LinkList AddPoly(LinkList *l1,LinkList *l2)
{
    Node *q1=((*l1).head)->next;
    Node *q2=((*l2).head)->next;
    LinkList l;
    InitPolynomial(&l);
    Node* p=l.head;//p指向多项式最后一项
    while(q1 && q2)
    {
        switch(cmp(q1->data->exp,q2->data->exp))
        {
            case 1:
            {
                Node *q=CreateNode();

                q->data->coef=q2->data->coef;
                q->data->exp=q2->data->exp;

                q->next=NULL;
                p->next=q;
                p=p->next;

                q2=q2->next;
                l.len++;
                break;
            }
            case 0:
            {
                Node *q=CreateNode();

                q->data->coef=q1->data->coef+q2->data->coef;
                q->data->exp=q1->data->exp;

                q->next=NULL;
                p->next=q;
                p=p->next;

                q1=q1->next;
                q2=q2->next;
                l.len++;
                break;
            }
            case -1:
            {
                Node *q=CreateNode();

                q->data->coef=q1->data->coef;
                q->data->exp=q1->data->exp;

                q->next=NULL;
                p->next=q;
                p=p->next;

                q1=q1->next;
                l.len++;
                break;
            }
        }
    }

    while(q1)
    {
        Node *q=CreateNode();
        q->data->coef=q1->data->coef;
        q->data->exp=q1->data->exp;
        q->next=NULL;
        p->next=q;
        p=p->next;
        q1=q1->next;
        l.len++;
    }

    while(q2)
    {
        Node *q=CreateNode();
        q->data->coef=q2->data->coef;
        q->data->exp=q2->data->exp;
        q->next=NULL;
        p->next=q;
        p=p->next;
        q2=q2->next;
        l.len++;
    }

    return l;
}

/*多项式系数取反*/
int GetOpposite(LinkList *l)
{
    Node *q=l->head->next;
    while(q)
    {
        q->data->coef=(-(q->data->coef));
        q=q->next;
    }
    return OK;
}

/*多项式的减法*/
LinkList SubtractPoly(LinkList *l1,LinkList *l2)
{
    GetOpposite(l2);
    LinkList l=AddPoly(l1,l2);
    GetOpposite(l2);
    return l;
}

/*多项式的乘法*/
LinkList MultiplyPoly(LinkList *l1,LinkList *l2)
{
    LinkList l;
    InitPolynomial(&l);
    Node *q1=l1->head->next;
    Node *q2=l2->head->next;
    while(q1){
        q2=l2->head->next;
        while(q2)
        {
            Node *q=CreateNode();
            q->data->coef=q1->data->coef*q2->data->coef;
            q->data->exp=q1->data->exp+q2->data->exp;
            TermPlus(&l,q);
            q2=q2->next;
        }
        q1=q1->next;
    }
    return l;
}


int main()
{
    LinkList l1,l2;
    int m,n;

    InitPolynomial(&l1);
    InitPolynomial(&l2);

    printf("请输入多项式 1 的项数: ");
    scanf("%d",&m);
    CreatePolynomial(&l1,m);

    printf("请输入多项式 2 的项数: ");
    scanf("%d",&n);
    CreatePolynomial(&l2,n);
    
    printf("第一个");
    PolyTraverse(&l1);
    printf("第二个");
    PolyTraverse(&l2);

    LinkList L3=AddPoly(&l1,&l2);
    printf("\n相加后,");
    PolyTraverse(&L3);

    LinkList L4=SubtractPoly(&l1,&l2);
    printf("\n相减后,");
    PolyTraverse(&L4);

    LinkList L5=MultiplyPoly(&l1,&l2);
    printf("\n相乘后,");
    PolyTraverse(&L5);
    
    DestroyPoly(&L5);
    printf("\n销毁L5后输出L5: \n");
    PolyTraverse(&L5);
    system("pause");
    return 0;
}
