#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#define MaxSize 500
#define NULLKEY 0
#define DELEKEY -1
using namespace std;
typedef int KeyType;
void S_InsertBSTNode(KeyType BTree[], KeyType key , int j )       //向排序二叉树中插入结点
{

	if (BTree[j] == NULLKEY && j < MaxSize)
	{
		BTree[j] = key;
	}
	else if (BTree[j] == key )
		return;
	else if (key < BTree[j])
		S_InsertBSTNode(BTree, key, 2 * j + 1);              
	else if (key > BTree[j])
		S_InsertBSTNode(BTree, key, 2 * j + 2);
}

void S_CreateBSTree(ifstream& infile, int& n,KeyType BTree[])           //读取文件中的数据构造一棵排序二叉树
{
	n = 0;                                       //n用于记录二叉树中结点数量
	string NumberLine;
	int KeyNum;
	getline(infile, NumberLine);                              //读取一行序列
	istringstream is(NumberLine);                             //将读出的一行转成数据流进行操作
	printf("Input a sequence stored in SqList BSTree:");
	while (!is.eof())
	{
		is >> KeyNum;
		n++;
		printf("%d ", KeyNum);
		S_InsertBSTNode(BTree, KeyNum, 0);
	}
}

void S_MidOrder(KeyType BTree[],int k)                                 //输出中序遍历结果
{
	if (BTree[k] != NULLKEY && k < MaxSize)
	{
		S_MidOrder(BTree, 2 * k + 1);
		if(BTree[k]!=DELEKEY) printf("%d ", BTree[k]);
		S_MidOrder(BTree, 2 * k + 2);
	}
}


bool S_DeleteBSTNode(KeyType BTree[],int key,int i)                              //删除值为k的结点
{
	if (BTree[i]!= NULLKEY && i<MaxSize)
	{
		if (key == BTree[i])
		{
			if (BTree[2 * i + 1] == NULLKEY && BTree[2 * i + 2] == NULLKEY)             //若是叶子结点，则直接删除
			{
				BTree[i] = NULLKEY;
				return true;
			}
			else if (BTree[2 * i + 1] != NULLKEY && BTree[2 * i + 2] == NULLKEY)        //若只有左子树，无右子树，则将被删除节点的左孩子结点来代替
			{
				BTree[i] = BTree[2 * i + 1];
				BTree[2 * i + 1] = DELEKEY;
				return true;
			}
			else if (BTree[2 * i + 1] == NULLKEY && BTree[2 * i + 2] != NULLKEY)        //若只有右子树，无左子树，则将被删除节点的右孩子结点来代替
			{
				BTree[i] = BTree[2 * i + 2];
				BTree[2 * i + 2] = DELEKEY;
				return true;
			}
			else if (BTree[2 * i + 1] != NULLKEY && BTree[2 * i + 2] != NULLKEY)         //若左右子树都有，则将左子树中key最大的结点来代替（即被删除结点的最右下结点，此结点无右子树，但可能有左子树）
			{
				int p = i;
				i = 2 * i + 1;
				while (BTree[2 * i + 2] != NULLKEY && 2 * i + 2 < MaxSize)
				{
					i = 2 * i + 2;
				}
				BTree[p] = BTree[i];
				BTree[i] = DELEKEY;
				return true;
			}
		}
		else if (key < BTree[i])
			return S_DeleteBSTNode(BTree, key, 2 * i + 1);
		else if (key > BTree[i])
			return S_DeleteBSTNode(BTree, key, 2 * i + 2);
	}
	else
		return false;
}

void S_isDeleted(KeyType BTree[], ifstream& infile)             //判断是否删除成功
{
	string NumberLine;
	int x;
	getline(infile, NumberLine);                              //读取一行序列
	istringstream is(NumberLine);                             //将读出的一行转成数据流进行操作
	is >> x;
	printf("The key of the BTreeNode that needs to be deleted is %d\n", x);
	if (S_DeleteBSTNode(BTree,x,0) == true)
	{
		printf("Deleting %d successfully!\nAfter deleting %d,SqList-BSTree MidOrder:", x, x);
		S_MidOrder(BTree, 0);
	}
	else
		printf("%d doesn't exist", x);
}


int S_BTreeHeight(KeyType BTree[],int i)                                //求树高
{
	int left_height, right_height;
	if (BTree[i] == NULLKEY || i > MaxSize)
		return 0;
	else
	{
		left_height = S_BTreeHeight(BTree, 2 * i + 1);
		right_height = S_BTreeHeight(BTree, 2 * i + 2);
		return (left_height > right_height) ? (left_height + 1) : (right_height + 1);         //返回左右子树中高度最大的值
	}
}

void S_CountNode(KeyType BTree[], int h, int k, int& count,int i)        //求第h层的结点数
{
	if (BTree[i] == NULLKEY || i > MaxSize)
		return;
	else
	{
		if (h == k)
			count++;
		if (k < h)
		{
			S_CountNode(BTree, h, k + 1, count, 2 * i + 1);
			S_CountNode(BTree, h, k + 1, count, 2 * i + 2);
		}
	}
}

void S_ASL(KeyType BSTree[], int n)
{
	int height = S_BTreeHeight(BSTree, 0);
	int i;
	float sum = 0;
	int nodenum;
	for (i = 1; i <= height; i++)
	{
		nodenum = 0;
		S_CountNode(BSTree, i, 1, nodenum, 0);
		sum = i * nodenum + sum;
	}
	printf("Average Search Length :%0.2f\n", sum / n);
}

int main()
{
	KeyType BSTree[MaxSize] = {NULLKEY};
	ifstream infile;
	int NodeNum;
	//打开文件
    infile.open("data.txt");
	S_CreateBSTree(infile, NodeNum, BSTree);
	printf("\nSqList-BSTree MidOrder:");
	S_MidOrder(BSTree, 0);
	printf("\n");
	S_ASL(BSTree, NodeNum);
	S_isDeleted(BSTree, infile);
	cout << endl;
	infile.close();
	return 0;
}
