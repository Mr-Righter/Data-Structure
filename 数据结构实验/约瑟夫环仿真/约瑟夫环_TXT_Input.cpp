#include<iostream>
#include<cstdlib>      
#include<vector>
#include<fstream>
using namespace std;
typedef struct LinkNode
{
	int num;                    //���
	int password;               //����
	struct LinkNode* next;
}LinkNode;

LinkNode* CreatNode(int num, int password)      //��㹹�캯��
{
	LinkNode* p;
	p = (LinkNode*)malloc(sizeof(LinkNode));
	p->num = num;
	p->password = password;
	return p;
}

void LinkAssign(LinkNode*& List,int &Initial_Limit)     //����ƴ�Ӻ���
{

	LinkNode* p;
	int password, n;

	//�Զ�ģʽ���ļ�
	ifstream infile;
	infile.open("data.txt");
	infile >> n;            //�ȶ�ȡ����

	List = (LinkNode*)malloc(sizeof(LinkNode));
	List->password = n;         //��ͷ����password���¼ѭ�������ڵĽ������

	cout << "������:" << n << endl;
	cout << n << "���˵���������Ϊ:";
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
	end->next = List->next;     //�����ڹ���ѭ������ʱ����û�н�β����ָ����ָ��ͷ��㣬����ָ���׽�㣨ͷ���ĺ�̽ڵ㣩��ʹ����ѭ���������������
	infile >> Initial_Limit;
	printf("��ʼ��������ֵ:%d\n", Initial_Limit);
	infile.close();
}


void GetList(int N, LinkNode*& L, int Initial_Limit, int List[])  //��List�洢���ӵ�����
{
	int limit = Initial_Limit;
	int password;
	int No = 0;
	int i;
	LinkNode* cur = L->next;
	LinkNode* pre = L;
	while (N--)                                                   //��ѭ�������н������Ϊ0ʱ
	{
		for (i = 0; i < limit - 1; i++)
		{
			pre = cur;
			cur = cur->next;
		}                                                         //�ҵ���Ҫ��ɾ������ǰ�����
		List[No++] = cur->num;
		limit = cur->password;
		pre->next = cur->next;
		free(cur);
		if (pre != NULL)                                          
			cur = pre->next;
	}
}

void PrintList(int List[], int NodeNum)            //���List�е�����
{
	cout << "�����˵ı������Ϊ:";
	for (int i = 0; i < NodeNum; i++)
		cout << List[i] << " ";
	cout << endl;
}


int main()
{
	LinkNode* Ring;
	int Initial_Limit, NodeNum;
	int List[50];
	LinkAssign(Ring,Initial_Limit);           //����ѭ������
	NodeNum = Ring->password;   //��¼��ʼ�������
	GetList(NodeNum, Ring, Initial_Limit, List);
	PrintList(List, Ring->password);
	free(Ring);                //ע��ͷ��㲻Ҫ�����ͷ�
	return 0;
}