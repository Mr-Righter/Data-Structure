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
void S_InsertBSTNode(KeyType BTree[], KeyType key , int j )       //������������в�����
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

void S_CreateBSTree(ifstream& infile, int& n,KeyType BTree[])           //��ȡ�ļ��е����ݹ���һ�����������
{
	n = 0;                                       //n���ڼ�¼�������н������
	string NumberLine;
	int KeyNum;
	getline(infile, NumberLine);                              //��ȡһ������
	istringstream is(NumberLine);                             //��������һ��ת�����������в���
	printf("Input a sequence stored in SqList BSTree:");
	while (!is.eof())
	{
		is >> KeyNum;
		n++;
		printf("%d ", KeyNum);
		S_InsertBSTNode(BTree, KeyNum, 0);
	}
}

void S_MidOrder(KeyType BTree[],int k)                                 //�������������
{
	if (BTree[k] != NULLKEY && k < MaxSize)
	{
		S_MidOrder(BTree, 2 * k + 1);
		if(BTree[k]!=DELEKEY) printf("%d ", BTree[k]);
		S_MidOrder(BTree, 2 * k + 2);
	}
}


bool S_DeleteBSTNode(KeyType BTree[],int key,int i)                              //ɾ��ֵΪk�Ľ��
{
	if (BTree[i]!= NULLKEY && i<MaxSize)
	{
		if (key == BTree[i])
		{
			if (BTree[2 * i + 1] == NULLKEY && BTree[2 * i + 2] == NULLKEY)             //����Ҷ�ӽ�㣬��ֱ��ɾ��
			{
				BTree[i] = NULLKEY;
				return true;
			}
			else if (BTree[2 * i + 1] != NULLKEY && BTree[2 * i + 2] == NULLKEY)        //��ֻ���������������������򽫱�ɾ���ڵ�����ӽ��������
			{
				BTree[i] = BTree[2 * i + 1];
				BTree[2 * i + 1] = DELEKEY;
				return true;
			}
			else if (BTree[2 * i + 1] == NULLKEY && BTree[2 * i + 2] != NULLKEY)        //��ֻ���������������������򽫱�ɾ���ڵ���Һ��ӽ��������
			{
				BTree[i] = BTree[2 * i + 2];
				BTree[2 * i + 2] = DELEKEY;
				return true;
			}
			else if (BTree[2 * i + 1] != NULLKEY && BTree[2 * i + 2] != NULLKEY)         //�������������У�����������key���Ľ�������棨����ɾ�����������½�㣬�˽����������������������������
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

void S_isDeleted(KeyType BTree[], ifstream& infile)             //�ж��Ƿ�ɾ���ɹ�
{
	string NumberLine;
	int x;
	getline(infile, NumberLine);                              //��ȡһ������
	istringstream is(NumberLine);                             //��������һ��ת�����������в���
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


int S_BTreeHeight(KeyType BTree[],int i)                                //������
{
	int left_height, right_height;
	if (BTree[i] == NULLKEY || i > MaxSize)
		return 0;
	else
	{
		left_height = S_BTreeHeight(BTree, 2 * i + 1);
		right_height = S_BTreeHeight(BTree, 2 * i + 2);
		return (left_height > right_height) ? (left_height + 1) : (right_height + 1);         //�������������и߶�����ֵ
	}
}

void S_CountNode(KeyType BTree[], int h, int k, int& count,int i)        //���h��Ľ����
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
	//���ļ�
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
