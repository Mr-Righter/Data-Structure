#include<iostream>
#include<stdio.h>

//顺序结构先序遍历
void PreOrder(int i, char BtList[], int L)
{
    if (i <= L)
    {
        if (BtList[i] != '0')                //0表示空
        {
            printf("%c", BtList[i]);
            PreOrder(2 * i, BtList, L);
            PreOrder(2 * i + 1, BtList, L);
        }
    }
}

//链式结构先序遍历
void PreOrder(BTNode* b)
{
	if (b != NULL)
	{
		printf("%c", b->data);
		PreOrder(b->lchild);
		PreOrder(b->rchild);
	}
}


//顺序结构中序遍历
void InOrder(int i, char BtList[], int L)
{
    if (i <= L)
    {
        if (BtList[i] != '0')
        {
            InOrder(2 * i, BtList, L);
            printf("%c", BtList[i]);
            InOrder(2 * i + 1, BtList, L);
        }
    }
}


//链式结构中序遍历
void InOrder(BTNode* b)
{
	if (b != NULL)
	{
		InOrder(b->lchild);
		printf("%c", b->data);
		InOrder(b->rchild);
	}
}


//顺序结构后序遍历
void LastOrder(int i, char BtList[], int L)
{
    if (i <= L)
    {
        if (BtList[i] != '0')
        {
            LastOrder(2 * i, BtList, L);
            LastOrder(2 * i + 1, BtList, L);
            printf("%c", BtList[i]);
        }
    }
}


//链式结构后序遍历
void LastOrder(BTNode* b)
{
	if (b != NULL)
	{
		LastOrder(b->lchild);
		LastOrder(b->rchild);
		printf("%c", b->data);
	}
}

//可看出链式结构和顺序结构的遍历方式基本相同，都可采用递归的思想
//头结点b对应序号1
//b!=NULL对应BTList[i]!='0'
//b的lchild和rchild分别对应BTList[i]的BtLsit[2i]和BTList[2i+1]
