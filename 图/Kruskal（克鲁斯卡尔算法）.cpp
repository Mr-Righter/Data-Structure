#include"MatGraph.h"
typedef struct
{
	int u;                               //�ߵ���ʼ���
	int v;                               //�ߵ���ֹ���
	int weight;                          //�ߵ�Ȩֵ
}Edge;                                   //����ΪEdge������
void Kurskal(MatGraph G, int v)          //Kruskal�㷨
{
	int i, j, k;                           
	int vset[MAXV];                      //��vset��¼ÿһ������i���ڵ���ͨ�������
	Edge E[MAXV];                        //���ͼ�����еı�
	k = 0;                               //����E���±��0��ʼ����
	for (i = 0; i < G.n; i++)            //��G.edges�ж�ȡ���ݣ������߼�E���Ҳ��ظ�ѡȡͬһ���ߣ�ֻ���ȡG.edges�������Ǿ��󼴿ɣ�
	{
		for (j = 0; j <= i; j++)         //������j<=i
			if (G.edges[i][j] != 0 && G.edges[i][j] != INF)
			{
				E[k].u = i;              
				E[k].v = j;
				E[k].weight = G.edges[i][j];
				k++;                     //ÿ����һ����k++
			}
	}
	//InsertSort(E, G.e);   (����ֱ�Ӳ������򷨶�E���鰴Ȩֵ����������Ҫ������
	for (i = 0; i < G.n; i++)
	{
		vset[i] = i;                     //��ʼ���������飬�ҳ�ֵ��ÿ������ı����ͬ
	}
	k = 1;                               //k��ʾ��ǰ���ɵ��������ĵڼ����ߣ���ֵΪ1
	j = 0;                               //E�е��±���ֵΪ0 
	while (k < G.n)                      //���ɵı���С��nʱѭ����������С���������ԣ�����ʹ���ҽ�ʹ��n-1����������ͼ�е�n�����㣩
	{
		int sn1 = vset[E[j].u];
		int sn2 = vset[E[j].v];        //�ֱ�õ��������������ļ��ϱ��
		if (sn1 != sn2)  //�����������ڲ�ͬ����ͨ���ϣ��ñ�����С��������һ����
		{
			printf("(%d,%d):%d\n", E[j].u, E[j].v, E[j].weight);   //�����С��������һ����
			k++;                                                   //����������1
			for (i = 0; i < G.n; i++)                              //��������ͳһ���
			{
				if (vset[i] == sn2)                       //���ϱ��Ϊsn2�ĸ�Ϊsn1
					vset[i] = sn1;
			}
		}
		j++;                                              //ɨ����һ����
	}
}