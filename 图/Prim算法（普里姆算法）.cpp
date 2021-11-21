#include"MatGraph.h"
void Prim(MatGraph G, int v)
{
	int lowcost[MAXV];
	int min;
	int closest[MAXV];
	int i, j, k;
	for (i = 0; i < G.n; i++)                   //给lowcost和cloest置初值
	{
		lowcost[i] = G.edges[v][i];
		closest[i] = v;
	}
	lowcost[v] = 0;
	for (i = 1; i < G.n; i++)                   //找出n-1个结点
	{
		min = INF;                              //每次开始寻找下一个结点时都要置min为INF
		for(j=0;j<G.n;j++)                      //在（V-U中找出离U最近的顶点k）
			if (lowcost[j] != 0 && lowcost[j] < min)
			{
				min = lowcost[j];               
				k = j;                          //k记录最近的顶点编号
			}
		printf("边(%d,%d)的权值为%d", closest[k], k, min);
		lowcost[k] = 0;                         //标记k已经加入到U中
		for (j = 0; j < G.n; j++)               //对（V-U）中的顶点j进行调整
		{
			if (lowcost[j] != 0 && lowcost[j] > G.edges[k][j])   //更新状态
			{
				lowcost[j] = G.edges[k][j];
				closest[j] = k;
			}
		}
	}
}