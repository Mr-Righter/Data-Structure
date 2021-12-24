#include<iostream>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<string>
#include<math.h>
using namespace std;
typedef int KeyType;
typedef struct BSTnode
{
	KeyType key;
	BSTnode* lchild;
	BSTnode* rchild;
}BSTnode;

void L_InsertBSTnode(BSTnode*& BTree, KeyType k)                 //向排序二叉树中插入结点
{
	if (BTree == NULL)
	{
		BTree = (BSTnode*)malloc(sizeof(BSTnode));
		BTree->key = k;
		BTree->lchild = BTree->rchild = NULL;
	}
	else if (BTree->key == k)
		return;
	else if (k < BTree->key)                                     //关键字小于当前结点的key，继续向左子树中查找插入的位置
		L_InsertBSTnode(BTree->lchild, k);
	else if (k > BTree->key)
		L_InsertBSTnode(BTree->rchild, k);						 //关键字大于当前结点的key，继续向右子树中查找插入的位置
}

BSTnode* L_CreateBSTree(ifstream& infile, int& n)           //读取文件中的数据构造一棵排序二叉树
{
	BSTnode* BTree;
	n = 0;                                       //n用于记录二叉树中结点数量
	BTree = NULL;
	string numberline;
	int keynum;
	getline(infile, numberline);                              //读取一行序列
	istringstream is(numberline);                             //将读出的一行转成数据流进行操作
	printf("Input a sequence stored in linked-list BSTree:");
	while (!is.eof())
	{
		is >> keynum;
		n++;
		printf("%d ", keynum);
		L_InsertBSTnode(BTree, keynum);
	}
	return BTree;
}

void L_MidOrder(BSTnode* btree)                                 //输出中序遍历结果
{
	if (btree != NULL)
	{
		L_MidOrder(btree->lchild);
		printf("%d ", btree->key);
		L_MidOrder(btree->rchild);
	}
}

bool L_DeleteBSTnode(BSTnode*& BTnode, KeyType k)                              //删除值为k的结点
{
	BSTnode* p;
	if (BTnode != NULL)
	{
		if (k == BTnode->key)
		{
			if (BTnode->lchild == NULL && BTnode->rchild == NULL)             //若是叶子结点，则直接删除
			{
				p = BTnode;
				BTnode = NULL;                                                //注意这里不能直接释放btnode，还要将btnode的双亲结点的孩子结点设置为null
				free(p);
				return true;
			}
			else if (BTnode->lchild != NULL && BTnode->rchild == NULL)        //若只有左子树，无右子树，则将被删除节点的左孩子结点来代替
			{
				p = BTnode;
				BTnode = BTnode->lchild;
				free(p);
				return true;
			}
			else if (BTnode->lchild == NULL && BTnode->rchild != NULL)        //若只有右子树，无左子树，则将被删除节点的右孩子结点来代替
			{
				p = BTnode;
				BTnode = BTnode->rchild;
				free(p);
				return true;
			}
			else if(BTnode->lchild != NULL && BTnode->rchild != NULL)         //若左右子树都有，则将左子树中key最大的结点来代替（即被删除结点的最右下结点，此结点无右子树，但可能有左子树）
			{
				BSTnode* pre = BTnode;
				p = BTnode->lchild;            //p指向被删除结点的左子树
				while (p->rchild != NULL)
				{
					pre = p;
					p = p->rchild;
				}
				BTnode->key = p->key;
				pre->rchild = p->lchild;
				free(p);
				return true;
			}
		}
		else if (k < BTnode->key)
			return L_DeleteBSTnode(BTnode->lchild, k);
		else if (k > BTnode->key)
			return L_DeleteBSTnode(BTnode->rchild, k);
	}
	else
		return false;
}


void L_isDeleted(BSTnode*& btnode, ifstream& infile)             //判断是否删除成功
{
	string numberline;
	int x;
	getline(infile, numberline);                              //读取一行序列
	istringstream is(numberline);                             //将读出的一行转成数据流进行操作
	is >> x;
	printf("The key of the BTreeNode that needs to be deleted is %d\n", x);
	if (L_DeleteBSTnode(btnode, x) == true)
	{
		printf("Deleting %d successfully!\nAfter deleting %d,Linked-List BStree MidOrder:", x, x);
		L_MidOrder(btnode);
	}
	else
		printf("%d doesn't exist", x);
}


int L_BTreeHeight(BSTnode* btree)                                //求树高
{
	int left_height, right_height;
	if (btree == NULL)
		return 0;
	else
	{
		left_height = L_BTreeHeight(btree->lchild);
		right_height = L_BTreeHeight(btree->rchild);
		return (left_height > right_height) ? (left_height + 1) : (right_height + 1);         //返回左右子树中高度最大的值
	}
}

void L_CountNode(BSTnode* btree, int h, int k, int& count)        //求第h层的结点数
{
	if (btree == NULL)
		return;
	else
	{
		if (h == k)
			count++;
		if (k < h)
		{
			L_CountNode(btree->lchild, h, k + 1, count);
			L_CountNode(btree->rchild, h, k + 1, count);
		}
	}
}

void L_ASL(BSTnode* bstree, int n)
{
	int height = L_BTreeHeight(bstree);
	int i;
	float sum = 0;
	int nodenum;
	for (i = 1; i <= height; i++)
	{
		nodenum = 0;
		L_CountNode(bstree, i, 1, nodenum);
		sum = i * nodenum + sum;
	}
	printf("Average search length :%0.2f\n", sum / n);
}

int main()
{
	BSTnode* bstree;
	ifstream infile;
	int nodenum;
	//打开文件
	infile.open("data.txt");
	bstree = L_CreateBSTree(infile, nodenum);
	printf("\nlinked-list bstree midorder:");
	L_MidOrder(bstree);
	printf("\n");
	L_ASL(bstree, nodenum);
	L_isDeleted(bstree, infile);
	infile.close();
	return 0;
}
