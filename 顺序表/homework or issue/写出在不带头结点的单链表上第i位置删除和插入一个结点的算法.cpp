#include<iostream>
#include<cstdlib>
using namespace std;
typedef int ElemType;
typedef struct LinkNode
{
	ElemType data;                 //存放数组元素
	struct LinkNode* next;            //指向后继结点
}LinkNode;                         //单链表结构类型

bool ListInsert(LinkNode*& L, int i, ElemType e)           //插入
{
	LinkNode* p = L;
	LinkNode* s;
	s = (LinkNode*)malloc(sizeof(LinkNode));
	s->data = e;
	int j = 1;
	if (i < 1)
	{
		free(s);
		return false;
	}	
	else if (i == 1)                             //i==1的情况要单独拿出来考虑
	{
	
		s->next = L;
		return true;
	}
	else
	{
		while (j < i - 1 && p != NULL)
		{
			j++;
			p = p->next;
		}
		if (p == NULL)
			return false;
		s->next = p->next;
		p->next = s;
		return true;
	}		
}


bool ListDelete(LinkNode*& L, int i, ElemType& e)             //删除
{
	LinkNode* p = L;
	int j = 1;
	if (i < 1)
		return false;
	else if (i = 1)                               //i==1的情况单独拿出来考虑
	{
		free(p);
		return true;
	}
	else
	{
		while (j < i - 1 && p != NULL)
		{
			j++;
			p = p->next;
		}
		if (p == NULL)
			return false;
		LinkNode* q = p->next;
		e = q->data;
		p->next = q->next;
		free(q);
		return true;
	}
}
