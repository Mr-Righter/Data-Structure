#include<iostream>
#include<cstdlib>      
#include<vector>
#include<fstream>
using namespace std;
typedef struct LinkNode
{
	int num;                    //序号
	int password;               //密码
	struct LinkNode* next;
}LinkNode;

LinkNode* CreatNode(int num, int password)      //结点构造函数
{
	LinkNode* p;
	p = (LinkNode*)malloc(sizeof(LinkNode));
	p->num = num;
	p->password = password;
	return p;
}

void LinkAssign(LinkNode*& List,int &Initial_Limit)     //链表拼接函数
{

	LinkNode* p;
	int password, n;

	//以读模式打开文件
	ifstream infile;
	infile.open("data.txt");
	infile >> n;            //先读取人数

	List = (LinkNode*)malloc(sizeof(LinkNode));
	List->password = n;         //用头结点的password域记录循环链表内的结点总数

	cout << "总人数:" << n << endl;
	cout << n << "个人的密码依次为:";
	LinkNode* end = List;
	for (int i = 1; i <= n; i++)
	{
		infile >> password;
		printf("%d ", password);
		p = CreatNode(i, password);
		end->next = p;
		end = p;
	}
	printf("\n");
	end->next = List->next;     //这里在构造循环链表时，并没有将尾结点的指针域指向头结点，而是指向首结点（头结点的后继节点），使得在循环访问链表更方便
	infile >> Initial_Limit;
	printf("初始报数上限值:%d\n", Initial_Limit);
	infile.close();
}


void GetList(int N, LinkNode*& L, int Initial_Limit, int List[])  //用List存储出队的序列
{
	int limit = Initial_Limit;
	int password;
	int No = 0;
	int i;
	LinkNode* cur = L->next;
	LinkNode* pre = L;
	while (N--)                                                   //当循环链表中结点数不为0时
	{
		for (i = 0; i < limit - 1; i++)
		{
			pre = cur;
			cur = cur->next;
		}                                                         //找到需要被删除结点的前驱结点
		List[No++] = cur->num;
		limit = cur->password;
		pre->next = cur->next;
		free(cur);
		if (pre != NULL)                                          
			cur = pre->next;
	}
}

void PrintList(int List[], int NodeNum)            //输出List中的序列
{
	cout << "出列人的编号序列为:";
	for (int i = 0; i < NodeNum; i++)
		cout << List[i] << " ";
	cout << endl;
}


int main()
{
	LinkNode* Ring;
	int Initial_Limit, NodeNum;
	int List[50];
	LinkAssign(Ring,Initial_Limit);           //构造循环链表
	NodeNum = Ring->password;   //记录初始编号总数
	GetList(NodeNum, Ring, Initial_Limit, List);
	PrintList(List, Ring->password);
	free(Ring);                //注意头结点不要忘记释放
	return 0;
}