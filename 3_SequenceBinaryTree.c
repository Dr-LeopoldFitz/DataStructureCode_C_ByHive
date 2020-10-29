/*
 *@authuor Hive
 *@Description:SequenceBinaryTree
 *@Date:2020/10/26
 */

/*ADT_Of_SequenceBinaryTree*/
// int InitBiTree(SqBiTree T)
// int CreateBiTree(SqBiTree T)
// int BiTreeEmpty(SqBiTree T)
// int BiTreeDepth(SqBiTree T)
// int Root(SqBiTree T,int *e)
// int Value(SqBiTree T,Position e)
// int Assign(SqBiTree T,Position e,int value)
// int Parent(SqBiTree T,int e)
// int LeftChild(SqBiTree T,int e)
// int RightChild(SqBiTree T,int e)
// int LeftSibling(SqBiTree T,int e)
// int RightSibling(SqBiTree T,int e)
// void PreTraverse(SqBiTree T,int e)
// int PreOrderTraverse(SqBiTree T)
// void InTraverse(SqBiTree T,int e)
// int InOrderTraverse(SqBiTree T)
// void PostTraverse(SqBiTree T,int e)
// int PostOrderTraverse(SqBiTree T)
// void LevelOrderTraverse(SqBiTree T)
// void Print(SqBiTree T)

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define ElemType int
#define INIT_SIZE 100
int Nil=0;

typedef int SqBiTree[INIT_SIZE]; /* 0号单元存储根结点  */

typedef struct
{
	int level,order; /* 结点的层,本层序号(按满二叉树计算) */
}Position;

int visit(int c)
{
	printf("%d ",c);
	return 1;
}

/* 构造空二叉树T。因为T是固定数组，不会改变，故不需要& */
int InitBiTree(SqBiTree T)
{
	int i;
	for(i=0;i<INIT_SIZE;i++)
		T[i]=Nil;
	return 1;
}

/* 按层序次序输入二叉树中结点的值, 构造顺序存储的二叉树T */
int CreateBiTree(SqBiTree T)
{ 
	int i=0;
 	printf("请按层序输入结点的值(整型)，结点数≤%d:\n",INIT_SIZE);
	while(i<10)
	{
		T[i]=i+1;
		
		if(i!=0&&T[(i+1)/2-1]==Nil&&T[i]!=Nil) /* 此结点(不空)无双亲且不是根 */
		{
			printf("出现无双亲的非根结点%d\n",T[i]);
		}
		i++;
	}
	while(i<INIT_SIZE)
	{
		T[i]=Nil; /* 将空赋值给T的后面的结点 */
		i++;
	}
	return 1;
}

#define ClearBiTree InitBiTree /* 在顺序存储结构中，两函数完全一样 */

int BiTreeEmpty(SqBiTree T)
{ 
	if(T[0]==Nil) /* 根结点为空,则树空 */
		return 1;
	else
		return 0;
}

int BiTreeDepth(SqBiTree T)
{ 
   int i,j=-1;
   for(i=INIT_SIZE-1;i>=0;i--) /* 找到最后一个结点 */
     if(T[i]!=Nil)
       break;
   i++; 
   do
     j++;
   while(i>=powl(2,j));/* 计算2的j次幂。 */
   return j;
}

int Root(SqBiTree T,int *e)
{ 
	if(BiTreeEmpty(T))
		return 0;
	else
	{	
		*e=T[0];
		return 1;
	}
}

/* 返回处于位置e(层,本层序号)的结点的值 */
int Value(SqBiTree T,Position e)
{ 
	 return T[(int)powl(2,e.level-1)+e.order-2];
    /*处于e.level层的第e.order个元素在数组T中的下标
     为( 2^(e.level-1)-1 )+(e.order-1)*/
}

/* 给处于位置e(层,本层序号)的结点赋新值value */
int Assign(SqBiTree T,Position e,int value)
{ 
	int i=(int)powl(2,e.level-1)+e.order-2; /* 将层、本层序号转为矩阵的序号 */
	if(value!=Nil&&T[(i+1)/2-1]==Nil) /* 给叶子赋非空值但双亲为空 */
		return 0;
	else if(value==Nil&&(T[i*2+1]!=Nil||T[i*2+2]!=Nil)) /*  给双亲赋空值但有叶子（不空） */
		return 0;
	T[i]=value;
	return 1;
}

int Parent(SqBiTree T,int e)
{ 
	int i;
	if(T[0]==Nil)
		return Nil;
	for(i=1;i<=INIT_SIZE-1;i++)
		if(T[i]==e)
			return T[(i+1)/2-1];
	return Nil;
}

int LeftChild(SqBiTree T,int e)
{ 
	int i;
	if(T[0]==Nil)
		return Nil;
	for(i=0;i<=INIT_SIZE-1;i++)
		if(T[i]==e)
			return T[i*2+1];
	return Nil;
}

int RightChild(SqBiTree T,int e)
{ 
	int i;
	if(T[0]==Nil)
		return Nil;
	for(i=0;i<=INIT_SIZE-1;i++)
		if(T[i]==e)
			return T[i*2+2];
	return Nil;
}

int LeftSibling(SqBiTree T,int e)
{ 
	int i;
	if(T[0]==Nil)
		return Nil;
	for(i=1;i<=INIT_SIZE-1;i++)
		if(T[i]==e&&i%2==0) /* 找到e且其序号为偶数(是右孩子) */
			return T[i-1];
	return Nil;
}

int RightSibling(SqBiTree T,int e)
{ 
	int i;
	if(T[0]==Nil)
		return Nil;
	for(i=1;i<=INIT_SIZE-1;i++)
		if(T[i]==e&&i%2) /* 找到e且其序号为奇数(是左孩子) */
			return T[i+1];
	return Nil;
}

/* PreOrderTraverse()调用 */
void PreTraverse(SqBiTree T,int e)
{ 
	visit(T[e]);
	if(T[2*e+1]!=Nil)
		PreTraverse(T,2*e+1);
	if(T[2*e+2]!=Nil)
		PreTraverse(T,2*e+2);
}

/* 先序遍历T */
int PreOrderTraverse(SqBiTree T)
{ 
	if(!BiTreeEmpty(T))
	 PreTraverse(T,0);
	printf("\n");
	return 1;
}

/* InOrderTraverse()调用 */
void InTraverse(SqBiTree T,int e)
{ 
	if(T[2*e+1]!=Nil)
		InTraverse(T,2*e+1);
	visit(T[e]);
	if(T[2*e+2]!=Nil)
		InTraverse(T,2*e+2);
}

/* 中序遍历T */
int InOrderTraverse(SqBiTree T)
{ 
	if(!BiTreeEmpty(T))
		InTraverse(T,0);
	printf("\n");
	return 1;
}

/* PostOrderTraverse()调用 */
void PostTraverse(SqBiTree T,int e)
{ 
	if(T[2*e+1]!=Nil)
		PostTraverse(T,2*e+1);
	if(T[2*e+2]!=Nil)
		PostTraverse(T,2*e+2);
	visit(T[e]);
}

/* 后序遍历T */
int PostOrderTraverse(SqBiTree T)
{ 
	if(!BiTreeEmpty(T))
		PostTraverse(T,0);
	printf("\n");
	return 1;
}

/* 层序遍历二叉树 */
void LevelOrderTraverse(SqBiTree T)
{ 
	int i=INIT_SIZE-1,j;
	while(T[i]==Nil)
		i--; /* 找到最后一个非空结点的序号 */
	for(j=0;j<=i;j++)  /* 从根结点起,按层序遍历二叉树 */
		if(T[j]!=Nil)
			visit(T[j]); /* 只遍历非空的结点 */
	printf("\n");
}

/* 逐层、按本层序号输出二叉树 */
void Print(SqBiTree T)
{ 
	int j,k;
	Position p;
	int e;
	for(j=1;j<=BiTreeDepth(T);j++)
	{
		printf("第%d层: ",j);
		for(k=1;k<=powl(2,j-1);k++)
		{
			p.level=j;
			p.order=k;
			e=Value(T,p);
			if(e!=Nil)
				printf("%d:%d ",k,e);
		}
		printf("\n");
	}
}


int main()
{
	int i,e;
	Position p;
	SqBiTree T;
	InitBiTree(T);
	CreateBiTree(T);

	printf("建立二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));

	i=Root(T,&e);
	if(i)
		printf("二叉树的根为：%d\n",e);
	else
		printf("树空，无根\n");

	printf("层序遍历二叉树:\n");
	LevelOrderTraverse(T);
	printf("前序遍历二叉树:\n");
	PreOrderTraverse(T);
	printf("中序遍历二叉树:\n");
	InOrderTraverse(T);
	printf("后序遍历二叉树:\n");
	PostOrderTraverse(T);
	
	printf("修改结点的层号3本层序号2。");
	p.level=3;
	p.order=2;
	e=Value(T,p);
	printf("待修改结点的原值为%d请输入新值:50 ",e);
	e=50;
	Assign(T,p,e);
	printf("前序遍历二叉树:\n");
	PreOrderTraverse(T);
	printf("结点%d的双亲为%d,左右孩子分别为",e,Parent(T,e));
	printf("%d,%d,左右兄弟分别为",LeftChild(T,e),RightChild(T,e));
	printf("%d,%d\n",LeftSibling(T,e),RightSibling(T,e));
	ClearBiTree(T);
	printf("清除二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	i=Root(T,&e);
	if(i)
		printf("二叉树的根为：%d\n",e);
	else
		printf("树空，无根\n");
	
    system("pause");
	return 0;
}