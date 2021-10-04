#include<iostream>
#include<cstdlib>
using namespace std;
typedef int ElemType;
typedef struct LinkNode
{
	ElemType data;                    //存放数组元素
	struct LinkNode* next;            //指向后继结点
}LinkNode;                          //单链表结构类型

//建立单链表的方法
// (1).头插法：将读取的元素存放到当前链表的表头上（即头结点之后）
void CreateListF(LinkNode*& L, ElemType a[], int n)      //读取并存储数组a中的所有元素
{
	LinkNode* s;                                         
	L = (LinkNode*)malloc(sizeof(LinkNode));             
	L->next = NULL;                                        //创建头结点，其next域置为NULL
	for (int i = 0; i < n; i++)                            //循环建立数据结点s
	{
		s = (LinkNode*)malloc(sizeof(LinkNode));         
		s->data = a[i];                                      //创建数据节点s
		s->next = L->next;                                   //将节点s插入到原首结点之后、头节点之前
		L->next = s;
	}
}//采用头插法建表时单链表中数据结点的顺序与数组a中元素的顺序相反



 //(2).尾插法：将读取的元素放在当前链表的最后
void CreateListR(LinkNode*& L, ElemType a[], int n)
{
	LinkNode* s;                  //生成的新结点
	LinkNode* r;                  //设置一个尾指针r，使其始终指向当前链表尾结点
	L = (LinkNode*)malloc(sizeof(LinkNode));
	r=L;                          //初始时r指向头节点
	for (int i = 0; i < n; i++)
	{
		s = (LinkNode*)malloc(sizeof(LinkNode));    //创建循环结点s
		s->data = a[i];        
		r->next = s;                                //将结点s插入到结点r之后
		r = s;                                      //将新插入的s结点设为r结点
	}
	r->next = NULL;                               //尾结点的next域设为NULL
}//采用尾插法建表时单链表中数据结点的顺序与数组a中的元素相同



//初始化链表
void InitList(LinkNode*& L)
{
	L = (LinkNode*)malloc(sizeof(LinkNode));
	L->next = NULL;
}



//销毁线性表
void DestoryList(LinkNode* &L)
{
	LinkNode* pre = L, * p = L->next;   //pre指向p的前驱结点
	while (p->next!=NULL)               //扫描单链表L
	{
		free(pre);                        //释放节点pre
		pre=p;                            //pre先后移一个结点
		p = pre->next;                    //p后移一个结点
	}
	free(pre);                          //循环结束时p为NULL，pre指向尾结点，释放它
}
//释放单链表L需要逐一释放全部结点的空间
/*原理：让pre和p指向相邻的两个结点（初始时让pre指向头节点，p指向首结点）。当p不为空时循环：
        释放结点pre，然后pre和p结点同步后移一个结点。循环结束后，pre指向尾结点，再将其释放*/

 

//判断线性表是否为空
bool ListEmpty(LinkNode* L)
{
	return(L->next == NULL);            //当单链表L中没有数据结点时返回true
}



//求线性表的长度
int ListLength(LinkNode* L)
{
	int n = 0;
	LinkNode* p = L;                    //p指向头结点，n置为0(即头结点的序号为0）
	while (p->next != NULL)             //当p的下一个结点不为0时执行循环
	{
		n++;                            
		p = p->next;
	}
	return(n);                          //循环结束，p指向尾结点，其序号n为结点个数
}



//输出线性表
void DisplayList(LinkNode* L)
{
	LinkNode* p = L->next;              //初始时让p指向首结点
	while (p != NULL)                   //p不为NULL，输出p结点的data域
	{
		cout << p->data << endl;
		p = p->next;                      //p移向下一个结点
	}
}



//求单链表中的某个数据元素值
bool GetElem(LinkNode* L, int i, ElemType &e)
{
	int j = 0;                  //用j来累计遍历过的数据节点个数，初始时值为0
	LinkNode* p=L;              //p指向头节点
	if (i <= 0)                
		return false;             //若i值错误则返回false
	while (j < i && p != NULL)  //找到第i个结点p，当j<i且p不为空时循环（可能出现要找的元素的位置大于链表长度的情况）
	{
		j++;                    
		p = p->next;
	}
	if (p == NULL)
		return false;             //若不存在第i个数据结点，返回false
	else
	{
		e = p->data;
		return true;
	}
}



//按元素值查找元素位置
int LocateElem(LinkNode* L, ElemType e)
{
	int i = 1;
	LinkNode* p=L->next;                    //p指向首结点，i置为1，即（首结点序号为1）
	while (p != NULL && p->data != e)       //查找data值为e的结点，其序号为i
	{
		i++;
		p = p->next;
	}
	if (p == NULL)                          //不存在值为e的结点，返回0
		return(0);
	else                                    //存在值为e的点，返回其逻辑序号i
		return(i);
}
//对链表中元素的访问均需要遍历



//插入数组元素
bool ListInsert(LinkNode*& L, int i, ElemType e)
{
	LinkNode* p = L;
	LinkNode* s;
	int j = 0;
	if (i <= 0)
		return false;
	while (j < i - 1 && p != NULL)                //这里要先找到第i-1个结点
	{
		j++;
		p = p->next;                                //这里p指向的是第i-1个结点
	}
	if (p == NULL)
		return false;
	else
	{
		s = (LinkNode*)malloc(sizeof(LinkNode));  
	    s->data = e;                              //创建新的结点s，其data域设为e
		s->next = p->next;
		p->next = s;
		return true;
	}
}//先在带单链表L中找到第i个结点，由p指向它。若存在这样的结点，将值为e的结点（s指向它）插入到p所指的结点后面



//删除单链表中的数据元素
bool DeleteElem(LinkNode*& L, int i, ElemType& e)
{
	int j = 0;
	LinkNode* p = L;
	if (i <= 0)
		return 0;
	while (j < i - 1 && p != NULL)                 //查找第i-1个结点
	{
		j++;
		p = p->next;
	}
	if (p == NULL)                                 //若未找到i-1个结点，返回false
		return false; 
	else                                           //找到第i-1个结点
	{
		LinkNode* q = p->next;                       //q指向第i个结点
		if (q == NULL)                               //若不存在第i个结点，返回false（之前是判断是否存在第i-1个结点）
			return false;                      
		e = q->data;                                 //返回删除的元素数据
		p->next = q->next;                           //从单链表中删除q结点
		free(q);                                     //释放q结点
		return true; 
	}
}
