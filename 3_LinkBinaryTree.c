/*
 *@authuor Hive
 *@Description:LinkBinaryTree
 *@Date:2020/10/26
 */

/*ADT_Of_LinkBinaryTree*/
// int StrAssign(String T,char *chars)
// int InitBiTree(BiTree *T)
// void DestroyBiTree(BiTree *T)
// void CreateBiTree(BiTree *T)
// int BiTreeEmpty(BiTree T)
// int BiTreeDepth(BiTree T)
// ElemType Root(BiTree T)
// ElemType Value(BiTree p)
// void Assign(BiTree p,ElemType value)
// void PreOrderTraverse(BiTree T)
// void InOrderTraverse(BiTree T)
// void PostOrderTraverse(BiTree T)

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define MAXSIZE 100

int index=1; //用于构造二叉树
typedef char String[100]; /* 0号单元存放串的长度 */
String str;

int StrAssign(String T,char *chars)
{ 
	int i;
	if(strlen(chars)>MAXSIZE)
		return 0;
	else
	{
		T[0]=strlen(chars);
		for(i=0;i<T[0];i++)
			T[i]=*(chars+i);
		return 1;
	}
}

typedef char ElemType;
ElemType Nil=' ';

int visit(ElemType e)
{
	printf("%c ",e);
	return 1;
}

typedef struct BiTNode 
{
   ElemType data;
   struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

int InitBiTree(BiTree *T)
{ 
	*T=NULL;
	return 1;
}

void DestroyBiTree(BiTree *T)
{ 
	if(*T) 
	{
		if((*T)->lchild)
			DestroyBiTree(&(*T)->lchild);
		if((*T)->rchild)
			DestroyBiTree(&(*T)->rchild);
		free(*T);
		*T=NULL; /* 空指针赋NULL! */
	}
}

/* 按前序输入二叉树中结点的值（一个字符） */
/* #表示空树，构造二叉链表表示二叉树T。 */
void CreateBiTree(BiTree *T)
{ 
	ElemType ch;
	//scanf("%c",&ch);
	ch=str[index++];

	if(ch=='#') 
		*T=NULL;
	else
	{
		*T=(BiTree)malloc(sizeof(BiTNode));
		(*T)->data=ch; /* 生成根结点 */
		CreateBiTree(&(*T)->lchild); /* 构造左子树 */
		CreateBiTree(&(*T)->rchild); /* 构造右子树 */
	}
 }

/* 若T为空二叉树,则返回1,否则0 */
int BiTreeEmpty(BiTree T)
{ 
	if(T)
		return 0;
	else
		return 1;
}

#define ClearBiTree DestroyBiTree

/* 返回T的深度 */
int BiTreeDepth(BiTree T)
{
	int i,j;
	if(!T)
		return 0;

	if(T->lchild)
		i=BiTreeDepth(T->lchild);
	else
		i=0;

	if(T->rchild)
		j=BiTreeDepth(T->rchild);
	else
		j=0;

	return i>j?i+1:j+1;
}

/* 返回T的根 */
ElemType Root(BiTree T)
{ 
	if(BiTreeEmpty(T))
		return Nil;
	else
		return T->data;
}

/* 返回p所指结点的值 */
ElemType Value(BiTree p)
{
	return p->data;
}

/* 给p所指结点赋值为value */
void Assign(BiTree p,ElemType value)
{
	p->data=value;
}

/* 前序递归遍历T */
void PreOrderTraverse(BiTree T)
{ 
	if(T==NULL)
		return;
	printf("%c",T->data);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
}

/* 中序递归遍历T */
void InOrderTraverse(BiTree T)
{ 
	if(T==NULL)
		return;
	InOrderTraverse(T->lchild);
	printf("%c",T->data);
	InOrderTraverse(T->rchild);
}

/* 后序递归遍历T */
void PostOrderTraverse(BiTree T)
{
	if(T==NULL)
		return;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf("%c",T->data);
}

int main()
{
	int i;
	BiTree T;
	ElemType e1;
	InitBiTree(&T);

	
	StrAssign(str,"ABDH#K###E##CFI###G#J##");

	CreateBiTree(&T);

	printf("构造空二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	e1=Root(T);
	printf("二叉树的根为: %c\n",e1);

	printf("\n前序遍历二叉树:");
	PreOrderTraverse(T);
	printf("\n中序遍历二叉树:");
	InOrderTraverse(T);
	printf("\n后序遍历二叉树:");
	PostOrderTraverse(T);
	ClearBiTree(&T);
	printf("\n清除二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	i=Root(T);
	if(!i)
		printf("树空，无根\n");
	system("pause");
	return 0;
}

