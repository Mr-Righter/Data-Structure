#include<iostream>
#include<cstdlib>
#include "SqQueue.h"
#define MAXV 50
#define INF 32767
typedef char Info;
typedef struct ArcNode            //�߽��
{
	int adjvex;                   //�ñߵ��ٽӵ���
	struct ArcNode* nextarc;      //ָ����һ���߽��
	int weight;                   //Ȩֵ
}ArcNode;
typedef struct VNode            //������     
{
	Info info;                    //�����������Ϣ
	ArcNode* firstarc;            //ָ���һ���߽ӵ�
}VNode;
typedef struct AdjGraph
{
	int n, e;                     //ͼ�ж�����n�Ͷ�����e
	VNode adjlist[MAXV];        //�ڽӱ��ͷ�������
}AdjGraph;


//������ȱ��� Depth First Search��DFS��
int visited[MAXV] = {0};
void DFS(AdjGraph* G, int v)             //v�ǳ�ʼ��v
{                          
	ArcNode* p;
	visited[v] = 1;                      //���ѷ��ʱ��
	printf("%d", v);
	p = G->adjlist[v].firstarc;          //pָ�򶥵�v�ĵ�һ���ڽӵ�
	while (p != NULL)                    
	{
		if (visited[p->adjvex] == 0)     //��p->adjvex����δ�����ʣ��ݹ������
			DFS(G, p->adjvex);
		p = p->nextarc;                  //pָ��v����һ���ڽӵ�
	}
}


void BFS(AdjGraph* G, int v)
{
	int w;
	ArcNode* p;
	SqQueue* queue;                           //���廷�ζ���ָ��
	InitQueue(queue);                         //��ʼ������
	int visited[MAXV] = { 0 };                //���ʱ�������ʼ��
	printf("%d", v);
	visited[v] = 1;                           //���ѷ�������
	enQueue(queue, v);                        //����ʼ�����
	while (!EmptyQueue(queue))                //�Ӳ���ѭ��
	{
		deQueue(queue, w);                    //����һ������
		p = G->adjlist[w].firstarc;           //p��w�ĵ�һ���ڽӵ�
		while (p != NULL)                     //����w�������ڽӵ�
		{
			if (visited[p->adjvex] == 0)      //����ǰ�ڽӵ�δ������
			{
				printf("%d", p->adjvex);
				visited[p->adjvex] = 1;
				enQueue(queue, p->adjvex);    //���ö������
			}
			p = p->nextarc;                   //����һ���ڽӵ�
		}
	}
}


//DFS��BFS�ڱ��������з���һ�����ʱ����Ҫ����visutedֵ�����ж�


