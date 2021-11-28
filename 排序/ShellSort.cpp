#include"RecType.h"
void ShellSort(RecType R[], int n)              //取gap_1=n/2，gap_i+1=[(gap_i)/2]
{
	int i, j, gap;
	RecType temp;
	gap = n / 2;                                //增量置初值
	while (gap > 0)
	{
		for (i = gap; i < n; i++)               //对所有组采用直接插入排序
		{
			if (R[i].key < R[i - gap].key)
			{
				j = i - gap;
				temp = R[i];                    //对所有相隔d个位置一组采用直接插入排序
				while (j >= 0 && temp.key < R[j].key)
				{
					R[j + gap] = R[j];
					j = j - gap;
				}
				R[j + gap] = temp;
			}
		}
		gap = gap / 2;                          //当gap为1时即为直接插入排序
	}
}
