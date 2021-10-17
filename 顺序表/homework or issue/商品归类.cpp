#include<stdlib.h>
#include<stdio.h>
#include<string.h>
typedef struct LinkNode                          //定义一个链表节点
{
	char name;
	int data;
	struct LinkNode* next;
}LinkNode;

LinkNode* CreatList()                            //链表构造函数
{
	char Line[50];
	fgets(Line, 50, stdin);                      //获取一行所有数据并存储在字符串中
	int i;
	LinkNode* List;
	List = (LinkNode*)malloc(sizeof(LinkNode));
	LinkNode* p;
	LinkNode* end = List;
	for (i = 0; i < strlen(Line); i = i + 5)    //实际输入是：A 3, C 5, D 6（字母之间隔5个字符的位置）
	{
		p = (LinkNode*)malloc(sizeof(LinkNode));
		p->name = Line[i];
		p->data = atoi(&Line[i + 2]);           //atoi能将字符串转化为数字，atoi(char *),不过要传入地址
		end->next = p;
		end = p;
	}
	end->next = NULL;
	return List;                                //返回头结点地址
}

void DeleteList(LinkNode* L)                    //链表删除函数
{
	LinkNode* p = L;
	LinkNode* q = L->next;
	while (q != NULL)
	{
		p = q;
		q = q->next;
		free(p);
	}
	free(L);
}

void DisplayList(LinkNode* L)                   //链表输出函数
{
	LinkNode* p = L->next;
	while (p->next != NULL)
	{
		printf("%c %d, ", p->name, p->data);
		p = p->next;
	}
	printf("%c %d;", p->name, p->data);         
}

int main()
{
	LinkNode* PreList = CreatList();           //原有商品链表
	LinkNode* NewList = CreatList();           //新增商品链表
	LinkNode* p1, *q1; 
	LinkNode* p2, *q2;
	p1 = PreList;
	p2 = NewList;                              //p1和p2初始时都指向头结点
	q1 = p1->next;
	q2 = p2->next;                             //q1和q2分别指向p1和p2的后继结点
	while (q2 != NULL)                         //当NewList未遍历完时
	{
		if (q1 != NULL)                        //当PreList未遍历完时
		{
			if (q1->name == q2->name)          //若商品名称相同
			{
				q1->data = q2->data + q1->data;   //数据相加
				p1 = q1;
				q1 = q1->next;
				p2 = q2;
				q2 = q2->next;                    //p1,q1,p2,q2同步后移一个结点
			}
			else if (q1->name > q2->name)         //若q2不是原有商品且商品名在q1之前
			{
				q2 = q2->next;                    //q2后移一个结点 
				p1->next = p2->next;              
				p1 = p1->next;                    //将NewList中的新的商品对应的结点插入到PreList中
				p1->next = q1;                    //p1指向新插入的结点
				p2->next = q2;                    
			}
			else                                  //若q2不是原有商品且商品名在q1之后
			{
				p1 = q1;                          
				q1 = q1->next;                    //p1和p2同步后移一个结点
			}
		}
		else                                      //若此时PreList已近遍历完而NewList还未遍历完
		{
			p1->next = q2;                        //将NewList后的所有结点直接一次转移到PreList后
			p2->next = NULL;         
			break;                                //结束循环
		}
	}
	DisplayList(PreList);
	DeleteList(PreList);
	DeleteList(NewList);                          //记得要释放内存
	return 0; 
}

//输入
//A 3, C 5, D 6;
//A 2, B 3, C 5, E 7, F 8;
//输出
//A 5, B 3, C 10, D 6, E 7, F 8;
//这些zz老师怎么总喜欢搞些乱七八糟的标点在里面，不知道输入输出多不方便吗，全空格不好吗
