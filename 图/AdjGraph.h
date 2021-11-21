
#include<iostream>
#include<cstdlib>
#define MAXV 50
#define INF 32767
typedef char Info;
typedef struct ArcNode            //边结点
{
	int adjvex;                   //该边的临界点编号
	struct ArcNode* nextarc;      //指向下一条边界点
	int weight;                   //权值
}ArcNode;                   
typedef struct VexNode            //顶点结点     
{
	Info info;                    //顶点的其他信息
	ArcNode* firstarc;            //指向第一个边界点
}VexNode;
typedef struct AdjGraph           
{
   	int n, e;                     //图中顶点数n和顶点数e
	VexNode adjlist[MAXV];        //邻接表的头结点数组
}AdjGraph;


//创建图的运算算法
void CreateAdjGraph(AdjGraph* &G,int A[MAXV][MAXV],int n,int e)
{
	ArcNode* p; int i, j;
	G = (AdjGraph*)malloc(sizeof(AdjGraph));                //为邻接表分配内存
	for (i = 0; i < n; i++)
		G->adjlist[i].firstarc = NULL;                      //给邻接表中所有头结点的指针域置初值为NULL
	for (i = 0; i < n; i++)
	{	
		for (j = n - 1; j >= 0; j--)                        //采用头插法所以j顺序为从大到小
		{                                                   //检查邻接矩阵中的每个元素
			if (A[i][j] != 0 && A[i][j] != INF)             //存在一条边
			{
				p = (ArcNode*)malloc(sizeof(ArcNode));      //创建一个p结点
				p->adjvex = j;                              //存放邻接点
				p->weight = A[i][j];                        
				p->nextarc = G->adjlist[i].firstarc;        //采用头插法插入结点p
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
		pre = G->adjlist[i].firstarc;         //这里firstarc是结点的第一个边界点，也可能为NULL，因此也需要判断
		if (pre != NULL)                      //如果存在边结点
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
	free(G);                                  //最后还要释放头结点数组
}



