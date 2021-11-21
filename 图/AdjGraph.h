
#include<iostream>
#include<cstdlib>
#define MAXV 50
#define INF 32767
typedef char Info;
typedef struct ArcNode            //�߽��
{
	int adjvex;                   //�ñߵ��ٽ����
	struct ArcNode* nextarc;      //ָ����һ���߽��
	int weight;                   //Ȩֵ
}ArcNode;                   
typedef struct VexNode            //������     
{
	Info info;                    //�����������Ϣ
	ArcNode* firstarc;            //ָ���һ���߽��
}VexNode;
typedef struct AdjGraph           
{
   	int n, e;                     //ͼ�ж�����n�Ͷ�����e
	VexNode adjlist[MAXV];        //�ڽӱ��ͷ�������
}AdjGraph;


//����ͼ�������㷨
void CreateAdjGraph(AdjGraph* &G,int A[MAXV][MAXV],int n,int e)
{
	ArcNode* p; int i, j;
	G = (AdjGraph*)malloc(sizeof(AdjGraph));                //Ϊ�ڽӱ�����ڴ�
	for (i = 0; i < n; i++)
		G->adjlist[i].firstarc = NULL;                      //���ڽӱ�������ͷ����ָ�����ó�ֵΪNULL
	for (i = 0; i < n; i++)
	{	
		for (j = n - 1; j >= 0; j--)                        //����ͷ�巨����j˳��Ϊ�Ӵ�С
		{                                                   //����ڽӾ����е�ÿ��Ԫ��
			if (A[i][j] != 0 && A[i][j] != INF)             //����һ����
			{
				p = (ArcNode*)malloc(sizeof(ArcNode));      //����һ��p���
				p->adjvex = j;                              //����ڽӵ�
				p->weight = A[i][j];                        
				p->nextarc = G->adjlist[i].firstarc;        //����ͷ�巨������p
				G->adjlist[i].firstarc = p;
			}
		}
	}
	G->e = e;
	G->n = n;
}


void DestoryAdj(AdjGraph* &G)
{
	int i;
	ArcNode* p, * pre;
	for (i = 0; i < G->n; i++)
	{
		pre = G->adjlist[i].firstarc;         //����firstarc�ǽ��ĵ�һ���߽�㣬Ҳ����ΪNULL�����Ҳ��Ҫ�ж�
		if (pre != NULL)                      //������ڱ߽��
		{
			p = pre->nextarc;
			while (p != NULL)
			{
				free(pre);
				p = p->nextarc;
				pre = p;
			}
			free(pre);
		}
	}
	free(G);                                  //���Ҫ�ͷ�ͷ�������
}



