#include"MatGraph.h"
typedef struct
{
	int u;                               //边的起始结点
	int v;                               //边的终止结点
	int weight;                          //边的权值
}Edge;                                   //定义为Edge的类型
void Kurskal(MatGraph G, int v)          //Kruskal算法
{
	int i, j, k;                           
	int vset[MAXV];                      //用vset记录每一个顶点i所在的连通分量编号
	Edge E[MAXV];                        //存放图中所有的边
	k = 0;                               //数组E的下标从0开始计数
	for (i = 0; i < G.n; i++)            //从G.edges中读取数据，产生边集E，且不重复选取同一条边（只需读取G.edges的下三角矩阵即可）
	{
		for (j = 0; j <= i; j++)         //这里是j<=i
			if (G.edges[i][j] != 0 && G.edges[i][j] != INF)
			{
				E[k].u = i;              
				E[k].v = j;
				E[k].weight = G.edges[i][j];
				k++;                     //每产生一条边k++
			}
	}
	//InsertSort(E, G.e);   (采用直接插入排序法对E数组按权值递增排序）需要先排序
	for (i = 0; i < G.n; i++)
	{
		vset[i] = i;                     //初始化辅助数组，且初值与每个顶点的编号相同
	}
	k = 1;                               //k表示当前构成的生成树的第几条边，初值为1
	j = 0;                               //E中的下表，初值为0 
	while (k < G.n)                      //生成的边数小于n时循环（对于最小生成树而言，必须使用且仅使用n-1条边来连接图中的n个顶点）
	{
		int sn1 = vset[E[j].u];
		int sn2 = vset[E[j].v];        //分别得到两个顶点所属的集合编号
		if (sn1 != sn2)  //两个顶点属于不同的连通集合，该边是最小生成树的一条边
		{
			printf("(%d,%d):%d\n", E[j].u, E[j].v, E[j].weight);   //输出最小生成树的一条树
			k++;                                                   //生成树增加1
			for (i = 0; i < G.n; i++)                              //两个集合统一编号
			{
				if (vset[i] == sn2)                       //集合编号为sn2的改为sn1
					vset[i] = sn1;
			}
		}
		j++;                                              //扫描下一条边
	}
}