/*
构建一个大小可变的约瑟夫环，并输出步长为3时的剩余元素
用例1：输入 41；
输出： 16 31
用例2：输入2
输出：1 2
用例3：输入16
输出：1 8
用例4：输入100
输出：58 91  
*/

#include<stdio.h>
#include<stdlib.h>              //C中头文件是stdlib.h,C++是cstdlib
typedef struct LinkNode         //注意C和C++的不同
{
	int data;
	struct LinkNode* next;      //这里要加个struct
}LinkNode;

LinkNode* CreatNode(int i)      //结点构造函数
{
	LinkNode* p;
	p = (LinkNode*)malloc(sizeof(LinkNode));
	p->data = i;
	return p;
}

LinkNode* LinkAssign(int n)     //链表拼接函数
{
	LinkNode* List,*p;
	List = (LinkNode*)malloc(sizeof(LinkNode));
	List->data = n;
	LinkNode* end = List;
	for (int i = 0; i < n; i++)  
	{
		p = CreatNode(i+1);     //注意这里是i+1，因为是从0开始的
		end->next = p;
		end = p;
	}
	end->next = List->next;     //这里在构造循环链表时，并没有将尾结点的指针域指向头结点，而是指向首结点（头结点的后继节点），使得在循环访问链表更方便
	return List;
}

int main()
{
	int n;
	scanf("%d", &n);
	LinkNode* Circle;
	Circle=LinkAssign(n);       //构造循环链表
	int count = 0;              //计数器
	LinkNode* p, * q;
	p = Circle;                 //p指向头结点
	while (Circle->data > 2)    //当链表内元素数量大于2时循环
	{
		if (count < 2)          //这里小于2，而不是3，因为当要删除一个结点时，此时指针p应该指向这个结点的前驱结点
		{
			p = p->next;
			count++;
		}
		else
		{
			q = p->next;        //q指向要删除的结点
			p->next = q->next;				
			free(q);            //删除结点操作
			count = 0;          //计数器归零
			Circle->data--;     //元素数减1
		}
	}
	printf("%d %d",p->next->data,p->data);
	free(Circle);               //注意头结点不要忘记释放
	return 0;
}
