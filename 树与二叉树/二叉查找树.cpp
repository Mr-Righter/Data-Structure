#include<iostream>
#include<cstdlib>
typedef int KeyType;
typedef char ELemType;
typedef struct BSTNode
{
	KeyType key;                                 //关键字项
	ELemType data;                               //存储数据
	struct BSTNode* lchild, * rchild;            //左右孩子指针
}BSTNode;

void InsertBST(BSTNode* &bt, KeyType k)          //注意这里的bt指针是可能发生变化的（如bt原来值为NULL，后来值为一段新的内存），所以一定要采用应用型指针
{
	if (bt == NULL)                              //若原树为空，新插入的结点为根节点
	{
		bt = (BSTNode*)malloc(sizeof(BSTNode));
		bt->key = k;
		bt->lchild = bt->rchild = NULL;          //注意要将左右孩子指针置为NULL
	}
	else if (bt->key == k)                       //树中存在相同关键字结点，不执行操作
		return;
	else if (k < bt->key)                        //插入到左孩子结点中
		InsertBST(bt->lchild, k);                //采用递归的插入方法
	else if (k > bt->key)                        //插入到右孩子结点中
		InsertBST(bt->rchild, k);
}

BSTNode* CreateBST(KeyType List[], int n)        //创建二叉查找树，用Lsit顺序存储key
{
	BSTNode* bt;                                 //初始时bt置为NULL
	bt = NULL;
	for (int i = 0; i < n; i++)
	{
		InsertBST(bt, List[i]);                  //这了每次插入的时候都是从头结点开始找插入的位置，所以InsertBST要采用递归的构造方法
	}
	return bt;                                   //返回头结点
}
