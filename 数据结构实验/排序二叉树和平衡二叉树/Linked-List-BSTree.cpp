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

void L_InsertBSTnode(BSTnode*& BTree, KeyType k)                 //������������в�����
{
	if (BTree == NULL)
	{
		BTree = (BSTnode*)malloc(sizeof(BSTnode));
		BTree->key = k;
		BTree->lchild = BTree->rchild = NULL;
	}
	else if (BTree->key == k)
		return;
	else if (k < BTree->key)                                     //�ؼ���С�ڵ�ǰ����key���������������в��Ҳ����λ��
		L_InsertBSTnode(BTree->lchild, k);
	else if (k > BTree->key)
		L_InsertBSTnode(BTree->rchild, k);						 //�ؼ��ִ��ڵ�ǰ����key���������������в��Ҳ����λ��
}

BSTnode* L_CreateBSTree(ifstream& infile, int& n)           //��ȡ�ļ��е����ݹ���һ�����������
{
	BSTnode* BTree;
	n = 0;                                       //n���ڼ�¼�������н������
	BTree = NULL;
	string numberline;
	int keynum;
	getline(infile, numberline);                              //��ȡһ������
	istringstream is(numberline);                             //��������һ��ת�����������в���
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

void L_MidOrder(BSTnode* btree)                                 //�������������
{
	if (btree != NULL)
	{
		L_MidOrder(btree->lchild);
		printf("%d ", btree->key);
		L_MidOrder(btree->rchild);
	}
}

bool L_DeleteBSTnode(BSTnode*& BTnode, KeyType k)                              //ɾ��ֵΪk�Ľ��
{
	BSTnode* p;
	if (BTnode != NULL)
	{
		if (k == BTnode->key)
		{
			if (BTnode->lchild == NULL && BTnode->rchild == NULL)             //����Ҷ�ӽ�㣬��ֱ��ɾ��
			{
				p = BTnode;
				BTnode = NULL;                                                //ע�����ﲻ��ֱ���ͷ�btnode����Ҫ��btnode��˫�׽��ĺ��ӽ������Ϊnull
				free(p);
				return true;
			}
			else if (BTnode->lchild != NULL && BTnode->rchild == NULL)        //��ֻ���������������������򽫱�ɾ���ڵ�����ӽ��������
			{
				p = BTnode;
				BTnode = BTnode->lchild;
				free(p);
				return true;
			}
			else if (BTnode->lchild == NULL && BTnode->rchild != NULL)        //��ֻ���������������������򽫱�ɾ���ڵ���Һ��ӽ��������
			{
				p = BTnode;
				BTnode = BTnode->rchild;
				free(p);
				return true;
			}
			else if(BTnode->lchild != NULL && BTnode->rchild != NULL)         //�������������У�����������key���Ľ�������棨����ɾ�����������½�㣬�˽����������������������������
			{
				BSTnode* pre = BTnode;
				p = BTnode->lchild;            //pָ��ɾ������������
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


void L_isDeleted(BSTnode*& btnode, ifstream& infile)             //�ж��Ƿ�ɾ���ɹ�
{
	string numberline;
	int x;
	getline(infile, numberline);                              //��ȡһ������
	istringstream is(numberline);                             //��������һ��ת�����������в���
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


int L_BTreeHeight(BSTnode* btree)                                //������
{
	int left_height, right_height;
	if (btree == NULL)
		return 0;
	else
	{
		left_height = L_BTreeHeight(btree->lchild);
		right_height = L_BTreeHeight(btree->rchild);
		return (left_height > right_height) ? (left_height + 1) : (right_height + 1);         //�������������и߶�����ֵ
	}
}

void L_CountNode(BSTnode* btree, int h, int k, int& count)        //���h��Ľ����
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
	//���ļ�
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
