#include<iostream>
typedef int KeyType;
typedef char InfoType;
typedef struct RecType
{
	KeyType key;
	InfoType data;
}RecType;

void InsertSort(RecType R[], int n)     //对R[0...n-1]按递增有序序列进行直接排序
{
	int i, j;
	RecType temp;
	for (i = 1; i < n; i++)             
	{
		if (R[i].key < R[i - 1].key)    //反序时
		{
			temp = R[i];                //先记录R[i]
			j = i - 1;
			while (j >= 0 && R[j].key > temp.key)      //当j>=0且temp的key小于R[j]的key时就将R[j]后移一个位置
			{
				R[j + 1] = R[j];
				j--;                                   
			}
			R[j + 1] = temp;                           //在R[j+1]的位置插入R[i],j+1是因为循环结束后j还减一
		}
	}
}
