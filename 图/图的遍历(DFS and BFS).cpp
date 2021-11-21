#include<iostream>
#include<cstdlib>
#include "SqQueue.h"
#define MAXV 50
#define INF 32767


//深度优先遍历 Depth First Search（DFS）
int visited[MAXV] = {0};
void DFS(AdjGraph* G, int v)             //v是初始点v
{                          
	ArcNode* p;
	visited[v] = 1;                      //置已访问标记
	printf("%d", v);
	p = G->adjlist[v].firstarc;          //p指向顶点v的第一个邻接点
	while (p != NULL)                    
	{
		if (visited[p->adjvex] == 0)     //若p->adjvex顶点未被访问，递归访问它
			DFS(G, p->adjvex);
		p = p->nextarc;                  //p指向v的下一个邻接点
	}
}


void BFS(AdjGraph* G, int v)
{
	int w;
	ArcNode* p;
	SqQueue* queue;                           //定义环形队列指针
	InitQueue(queue);                         //初始化队列
	int visited[MAXV] = { 0 };                //访问标记数组初始化
	printf("%d", v);
	visited[v] = 1;                           //置已访问数组
	enQueue(queue, v);                        //将初始点入队
	while (!EmptyQueue(queue))                //队不空循环
	{
		deQueue(queue, w);                    //出队一个顶点
		p = G->adjlist[w].firstarc;           //p是w的第一个邻接点
		while (p != NULL)                     //查找w的所有邻接点
		{
			if (visited[p->adjvex] == 0)      //若当前邻接点未被访问
			{
				printf("%d", p->adjvex);
				visited[p->adjvex] = 1;
				enQueue(queue, p->adjvex);    //将该顶点进队
			}
			p = p->nextarc;                   //找下一个邻接点
		}
	}
}


//DFS和BFS在遍历过程中访问一个结点时首先要对其visuted值进行判断


