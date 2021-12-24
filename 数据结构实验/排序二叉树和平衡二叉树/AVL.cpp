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

int GetHeight(AVLNode* T)                                //��ȡ����
{
	if (T != NULL)
		return(T->height);
	else return 0;
}


AVLNode* LL_Rotation(AVLNode* T)                         //LL�͵���
{
	AVLNode* temp;
	temp = T->lchild;
	T->lchild = temp->rchild;
	temp->rchild = T;
	T->height = max(GetHeight(T->lchild), GetHeight(T->rchild)) + 1;
	temp->height = max(GetHeight(temp->lchild), GetHeight(temp->rchild)) + 1;
	return temp;                             //�����µĸ��ڵ�
}

AVLNode* RR_Rotation(AVLNode* T)                         //RR�͵���
{
	AVLNode* temp;
	temp = T->rchild;
	T->rchild = temp->lchild;
	temp->lchild = T;
	T->height = max(GetHeight(T->lchild), GetHeight(T->rchild)) + 1;
	temp->height = max(GetHeight(temp->lchild), GetHeight(temp->rchild)) + 1;
	return temp;                             //�����µĸ��ڵ�
}

AVLNode* LR_Rotation(AVLNode* T)                         //LR�͵���
{
	T->lchild = RR_Rotation(T->lchild);
	return(LL_Rotation(T));
}

AVLNode* RL_Rotation(AVLNode* T)                         //RL�͵���
{
	T->rchild = LL_Rotation(T->rchild);
	return(RR_Rotation(T));
}

void InsertAVL(AVLNode*& T, KeyType k)                 //��ƽ��������в�����
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
		if (GetHeight(T->lchild) - GetHeight(T->rchild) > 1)      //���������أ�ΪL_����ת
		{
			if (k < T->lchild->key)                               //�����������ӵ��������ϣ�ΪLL����ת
				T = LL_Rotation(T);
			else                                                  //�����������ӵ��������ϣ�ΪLL����ת
				T = LR_Rotation(T);
		}
	}
	else if (k > T->key)
	{
		InsertAVL(T->rchild, k);
		if (GetHeight(T->lchild) - GetHeight(T->rchild) < -1)      //���������أ�ΪR_����ת
		{
			if (k > T->rchild->key)                               //���������Һ��ӵ��������ϣ�ΪRR����ת
				T = RR_Rotation(T);
			else                                                  //���������Һ��ӵ��������ϣ�ΪRL����ת
				T = RL_Rotation(T);
		}
	}
	T->height = max(GetHeight(T->lchild), GetHeight(T->rchild)) + 1;   //�ڳ�ջʱ���²����㵽������и����������
}

AVLNode* CreateAVL(ifstream& infile, int& n)           //��ȡ�ļ��е����ݹ���һ�����������
{
	AVLNode *T;
	n = 0;                                       //n���ڼ�¼�������н������
	T = NULL;
	string NumberLine;
	int KeyNum;
	getline(infile, NumberLine);                              //��ȡһ������
	istringstream is(NumberLine);                             //��������һ��ת�����������в���
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

int L_BTreeHeight(AVLNode* T)                                //������
{
	int left_height, right_height;
	if (T == NULL)
		return 0;
	else
	{
		left_height = L_BTreeHeight(T->lchild);
		right_height = L_BTreeHeight(T->rchild);
		return (left_height > right_height) ? (left_height + 1) : (right_height + 1);         //�������������и߶�����ֵ
	}
}

void L_CountNode(AVLNode* T, int h, int k, int& count)        //���h��Ľ����
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

void L_MidOrder(AVLNode* btree)                                 //�������������
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
	//���ļ�
	infile.open("data.txt");
	AVL = CreateAVL(infile, NodeNum);
	printf("\n");
	L_ASL(AVL, NodeNum);
	infile.close();
	return 0;
}