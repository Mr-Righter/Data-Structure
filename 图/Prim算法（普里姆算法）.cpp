#include"MatGraph.h"
void Prim(MatGraph G, int v)
{
	int lowcost[MAXV];
	int min;
	int closest[MAXV];
	int i, j, k;
	for (i = 0; i < G.n; i++)                   //��lowcost��cloest�ó�ֵ
	{
		lowcost[i] = G.edges[v][i];
		closest[i] = v;
	}
	lowcost[v] = 0;
	for (i = 1; i < G.n; i++)                   //�ҳ�n-1�����
	{
		min = INF;                              //ÿ�ο�ʼѰ����һ�����ʱ��Ҫ��minΪINF
		for(j=0;j<G.n;j++)                      //�ڣ�V-U���ҳ���U����Ķ���k��
			if (lowcost[j] != 0 && lowcost[j] < min)
			{
				min = lowcost[j];               
				k = j;                          //k��¼����Ķ�����
			}
		printf("��(%d,%d)��ȨֵΪ%d", closest[k], k, min);
		lowcost[k] = 0;                         //���k�Ѿ����뵽U��
		for (j = 0; j < G.n; j++)               //�ԣ�V-U���еĶ���j���е���
		{
			if (lowcost[j] != 0 && lowcost[j] > G.edges[k][j])   //����״̬
			{
				lowcost[j] = G.edges[k][j];
				closest[j] = k;
			}
		}
	}
}