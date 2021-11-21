#include"MatGraph.h"
void Dijkstra(MatGraph G, int v)
{
	int distance[MAXV];                            //���v���������ľ���
	int path[MAXV];                                //��path��¼��ǰ�±��Ӧ�Ľ��ǰ�����
	int flag[MAXV];                                //flag[i]=1��ʾ����i���Ѿ�ȷ����v��i��·��
	int i, j, u;
	for (i = 0; i < G.n; i++)
	{
		distance[i] = G.edges[v][i];               //��ʼ�����루����INF��
		flag[i] = 0;                               //flag[]�ÿ�
		if (G.edges[v][i] < INF)                   //·����ʼ��
			path[i] = v;                           //����v������i�б�ʱ���ö���i��ǰһ������Ϊv
		else
			path[i] = -1;                          //����v������iû�б�ʱ���ö���i��ǰһ������Ϊ-1
	}
	flag[v] = 1;                                   //Դ����v����S��
	int MinDistance;                               
	for (i = 0; i < G.n - 1; i++)
	{
		MinDistance = INF;                         //MinDistance����ֵ����
		for (j = 0; j < G.n; j++)
		{
			if (flag[j] == 0 && distance[j] < MinDistance)   //ѡȡ����S�еģ���U�еģ��Ҿ�����С���·�����ȵĶ���u
			{
				MinDistance = distance[j];
				u = j;
			}
		}
		flag[u] = 1;                               //����u����S��
		for (j = 0; j < G.n; j++)                  //�޸Ĳ���S�еģ���U�У��Ķ�������·��
		{
			if (flag[j] == 0)
			{
				if (G.edges[u][j] != INF && G.edges[u][j] + distance[u] < distance[j])
				{
					distance[j] = G.edges[u][j] + distance[u];
					path[j] = u;                   //���޸���distance֮��ǵû�Ҫ��path�޸�Ϊu
				}
			}
		}
	}
	//Dispath(G,distance,path,flag,v)
}