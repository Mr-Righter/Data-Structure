#include<iostream>
#include<cstdlib>
typedef int ElemType;
typedef struct DLinkNode
{
	ElemType data;                   //存放元素值
	struct DLinkNode* prior;         //指向前驱结点
	struct DLinkNode* next;          //指向后继结点
}DLinkNode;                          //双链表的结点类型


//头插法建立双链表
void CreateListF(DLinkNode*& L, ElemType a[], int n)   //n为a[]中数据的数量
{
	DLinkNode* s;                               //先声明s类型
	L = (DLinkNode*)malloc(sizeof(DLinkNode));  //创建头结点
	L->prior = L->next = NULL;                  //前后指针域置为NULL
	for (int i = 0; i < n; i++)                 //循环建立数据结点
	{
		s = (DLinkNode*)malloc(sizeof(DLinkNode));
		s->data = a[i];                         //创建数据结点s
		s->next = L->next;                      //将s结点插入到头结点之后
		if (L->next != NULL)                    //这里需要先判断，因为最开始L->next==NULL,L->next不存在前域
			L->next->prior = s;                   //修改L->next的前驱指针
		L->next = s;                            
		s->prior = L;                           //修改s的前驱指针
	}
}



//尾插法创建双链表
void CreateListR(DLinkNode*& L, ElemType a[], int n)
{
	DLinkNode* s, * r;
	L = (DLinkNode*)malloc(sizeof(DLinkNode));
	L->prior = L->next = NULL;
	r = L;
	for (int i = 0; i < n; i++)
	{
		s = (DLinkNode*)malloc(sizeof(DLinkNode));
		s->data = a[i];
		s->prior = r;
		r->next = s;
		r = s;
	}
	r->next = NULL;
}



//双链表中元素的插入
bool ListInsert(DLinkNode*& L, int i , ElemType e)
{
	DLinkNode* s;
	DLinkNode* p = L;
	int j = 0;
	if (i <= 0)
		return false;
	while (j < i - 1 && p != NULL)
	{
		j++;
		p = p->next;
	}
	if (p == NULL)
		return false;
	else
	{
		s = (DLinkNode*)malloc(sizeof(DLinkNode));
		s->data = e;
		s->next = p->next;             
		if (p->next != NULL)           //若p结点后存在后继结点，修改其前驱指针
			p->next->prior = s;
		s->prior = p;
		p->next = s;                   //修改p->next的地址尽量放在后面执行，否则会因为找不到结点p的后继结点而导致插入错误
		return true;
	}
}



//双链表中元素的删除
bool ListDelete(DLinkNode*& L, int i, ElemType& e)
{
	DLinkNode* p = L;
	int j = 0;
	if (i <= 0)
		return false;
	while (j < i - 1 && p != NULL)
	{
		j++;
		p = p->next;
	}
	if (p == NULL)
		return false;                 //未找到第i-1个结点
	else
	{
		DLinkNode* q;
		q = p->next;
		if (q == NULL)
			return false;
		e = q->data;                  //返回删除的数据值
		p->next = q->next;
		if (q->next != NULL)          //如果q结点后存在后继结点（即q不为尾结点），则修改后继结点的前驱指针(这里需要先判断一下）
			q->next->prior = p;
		free(q);                      //释放q结点 
		return true;
	}
}
