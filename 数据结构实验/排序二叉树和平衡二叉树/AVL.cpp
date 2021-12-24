#include<iostream>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<string>
#include<algorithm>
using namespace std;
typedef int KeyType;
typedef struct AVLNode
{

	KeyType key;
	AVLNode* lchild;
	AVLNode* rchild;
	int height;
}AVLNode;

int GetHeight(AVLNode* T)                                //获取树高
{
	if (T != NULL)
		return(T->height);
	else return 0;
}


AVLNode* LL_Rotation(AVLNode* T)                         //LL型调整
{
	AVLNode* temp;
	temp = T->lchild;
	T->lchild = temp->rchild;
	temp->rchild = T;
	T->height = max(GetHeight(T->lchild), GetHeight(T->rchild)) + 1;
	temp->height = max(GetHeight(temp->lchild), GetHeight(temp->rchild)) + 1;
	return temp;                             //返回新的根节点
}

AVLNode* RR_Rotation(AVLNode* T)                         //RR型调整
{
	AVLNode* temp;
	temp = T->rchild;
	T->rchild = temp->lchild;
	temp->lchild = T;
	T->height = max(GetHeight(T->lchild), GetHeight(T->rchild)) + 1;
	temp->height = max(GetHeight(temp->lchild), GetHeight(temp->rchild)) + 1;
	return temp;                             //返回新的根节点
}

AVLNode* LR_Rotation(AVLNode* T)                         //LR型调整
{
	T->lchild = RR_Rotation(T->lchild);
	return(LL_Rotation(T));
}

AVLNode* RL_Rotation(AVLNode* T)                         //RL型调整
{
	T->rchild = LL_Rotation(T->rchild);
	return(RR_Rotation(T));
}

void InsertAVL(AVLNode*& T, KeyType k)                 //向平衡二叉树中插入结点
{
	if (T == NULL)
	{
		T = (AVLNode*)malloc(sizeof(AVLNode));
		T->key = k;
		T->lchild = T->rchild = NULL;
	}
	else if (T->key == k)
		return;
	else if (k < T->key)                              
	{
		InsertAVL(T->lchild, k);
		if (GetHeight(T->lchild) - GetHeight(T->rchild) > 1)      //左子树更重，为L_型旋转
		{
			if (k < T->lchild->key)                               //结点插入在左孩子的左子树上，为LL型旋转
				T = LL_Rotation(T);
			else                                                  //结点插入在左孩子的右子树上，为LL型旋转
				T = LR_Rotation(T);
		}
	}
	else if (k > T->key)
	{
		InsertAVL(T->rchild, k);
		if (GetHeight(T->lchild) - GetHeight(T->rchild) < -1)      //右子树更重，为R_型旋转
		{
			if (k > T->rchild->key)                               //结点插入在右孩子的右子树上，为RR型旋转
				T = RR_Rotation(T);
			else                                                  //结点插入在右孩子的左子树上，为RL型旋转
				T = RL_Rotation(T);
		}
	}
	T->height = max(GetHeight(T->lchild), GetHeight(T->rchild)) + 1;   //在出栈时更新插入结点到根结点中各个结点的深度
}

AVLNode* CreateAVL(ifstream& infile, int& n)           //读取文件中的数据构造一棵排序二叉树
{
	AVLNode *T;
	n = 0;                                       //n用于记录二叉树中结点数量
	T = NULL;
	string NumberLine;
	int KeyNum;
	getline(infile, NumberLine);                              //读取一行序列
	istringstream is(NumberLine);                             //将读出的一行转成数据流进行操作
	printf("Input a sequence stored in AVL:");
	while (!is.eof())
	{
		is >> KeyNum;
		n++;
		printf("%d ", KeyNum);
		InsertAVL(T, KeyNum);
	}
	return T;
}

int L_BTreeHeight(AVLNode* T)                                //求树高
{
	int left_height, right_height;
	if (T == NULL)
		return 0;
	else
	{
		left_height = L_BTreeHeight(T->lchild);
		right_height = L_BTreeHeight(T->rchild);
		return (left_height > right_height) ? (left_height + 1) : (right_height + 1);         //返回左右子树中高度最大的值
	}
}

void L_CountNode(AVLNode* T, int h, int k, int& count)        //求第h层的结点数
{
	if (T == NULL)
		return;
	else
	{
		if (h == k)
			count++;
		if (k < h)
		{
			L_CountNode(T->lchild, h, k + 1, count);
			L_CountNode(T->rchild, h, k + 1, count);
		}
	}
}

void L_ASL(AVLNode* T, int n)
{
	int height = L_BTreeHeight(T);
	int i;
	float sum = 0;
	int nodenum;
	for (i = 1; i <= height; i++)
	{
		nodenum = 0;
		L_CountNode(T, i, 1, nodenum);
		sum = i * nodenum + sum;
	}
	printf("Average search length :%0.3f", sum / n);
}

void L_MidOrder(AVLNode* btree)                                 //输出中序遍历结果
{
	if (btree != NULL)
	{
		L_MidOrder(btree->lchild);
		printf("%d ", btree->key);
		L_MidOrder(btree->rchild);
	}
}

int main()
{
	AVLNode* AVL;
	ifstream infile;
	int NodeNum;
	//打开文件
	infile.open("data.txt");
	AVL = CreateAVL(infile, NodeNum);
	printf("\n");
	L_ASL(AVL, NodeNum);
	infile.close();
	return 0;
}