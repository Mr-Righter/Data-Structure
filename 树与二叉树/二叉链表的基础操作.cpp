#include<iostream>
#include<cstdlib>
#define MaxSize 100
typedef char ElemType;
typedef struct BTNode
{
	ElemType data;                       //数据元素
	struct BTNode* lchild;               //指向左孩子结点
	struct BTNode* rchild;               //指向右孩子结点
}BTNode;


//求二叉树的结点数量
int CountNode(BTNode* b)
{
	if (b = NULL)
		return (0);
	else
		return (CountNode(b->lchild) + CountNode(b->rchild) + 1);
}


//求叶子结点个数
int LeafNodeNum(BtNdoe* b)       
{
	if (b == NULL)
		return(0);
	else if (b->lchild == NULL && b->rchild == NULL)
		return(1);
	else
		return(LeafNodeNum(b->lchild) + LeafNodeNum(b->rchild));
}



//输出一棵二叉树的叶子结点 
void DispLeaf(BTNode* b)
{
	if (b != NULL)
	{
		if (b->lchild == NULL && b->rchild == NULL)
			printf("%c", b->data);
		else
		{
			DispLeaf(b->lchild);
			DispLeaf(b->rchild);
		}
	}
}
//先序遍历从左到右输出叶子结点



//求一个二叉树b中结点值为x结点的深度
int Level(BTNode* b, ElemType x,int h)                   //h初值置为1
{
	int l;
	if (b == NULL)
		return 0;
	else if (b->data == x)
		return h;
	else
	{
		l = Level(b->lchild, x, h + 1);                  //在左子树中查找
		if (l != 0)
			return(l);                                   //找到了，返回l
		else                                             //在左子树中未找到，再在右子树中查找
			return(Level(b->rchild, x, h + 1));
	}
}
/*形参用于在二叉链表中遍历结点，该算法中又需要知道它的层次，在这种情况下就需要加一个形参h，它
  表示b所指的结点的层次。调用本算法时，总是从根结点开始查找的，而根结点的层次为1，h初值为1*/


//求第k层结点个数
void NodeNum(BTNode* b, int h, int k, int& n)        //h初值设为1，n初值设为0，且表示此时b所指的层次，
{
	if (b = NULL)                                    //空树直接返回
		return;
	else
	{
		if (h == k)
			n++;
		else if (h < k)
		{
			NodeNum(b->lchild, h + 1, k, n);
			NodeNum(b->rchild, h + 1, k, n);
		}
	}
}
