#include"MatGraph.h"
void Dijkstra(MatGraph G, int v)
{
	int distance[MAXV];                            //结点v到其他结点的距离
	int path[MAXV];                                //用path记录当前下标对应的结点前驱结点
	int flag[MAXV];                                //flag[i]=1表示顶点i在已经确定了v到i的路径
	int i, j, u;
	for (i = 0; i < G.n; i++)
	{
		distance[i] = G.edges[v][i];               //初始化距离（包括INF）
		flag[i] = 0;                               //flag[]置空
		if (G.edges[v][i] < INF)                   //路径初始化
			path[i] = v;                           //顶点v到顶点i有边时，置顶点i的前一个顶点为v
		else
			path[i] = -1;                          //顶点v到顶点i没有边时，置顶点i的前一个顶点为-1
	}
	flag[v] = 1;                                   //源点编号v放入S中
	int MinDistance;                               
	for (i = 0; i < G.n - 1; i++)
	{
		MinDistance = INF;                         //MinDistance最大初值长度
		for (j = 0; j < G.n; j++)
		{
			if (flag[j] == 0 && distance[j] < MinDistance)   //选取不在S中的（即U中的）且具有最小最短路径长度的顶点u
			{
				MinDistance = distance[j];
				u = j;
			}
		}
		flag[u] = 1;                               //顶点u加入S中
		for (j = 0; j < G.n; j++)                  //修改不在S中的（即U中）的顶点的最短路径
		{
			if (flag[j] == 0)
			{
				if (G.edges[u][j] != INF && G.edges[u][j] + distance[u] < distance[j])
				{
					distance[j] = G.edges[u][j] + distance[u];
					path[j] = u;                   //在修改了distance之后记得还要将path修改为u
				}
			}
		}
	}
	//Dispath(G,distance,path,flag,v)
}