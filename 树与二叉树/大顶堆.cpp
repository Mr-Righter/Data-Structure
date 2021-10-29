#include <iostream>

typedef int KeyType;
typedef char ElemType;
typedef struct MaxHeap             //定义一个大顶堆
{
	KeyType key;                   //关键字
	ElemType data;                 //其他数据
}MaxHeap;

void Sift(MaxHeap h[], int low, int high)              //对h[low...high]进行筛选，大者上浮，小者被筛选下去，在构造时high为总结点数
{
	int i = low;                                       //此时i指向low这个分支结点
	int j = 2 * i + 1;                                 //h[j]是h[i]的左孩子结点
	MaxHeap temp;                                      //这里用temp记录
	while (j <= high)                                  //防止越界
	{
		if (j < high && h[j].key < h[j + 1].key)       //这里j<high是为了确定该树是否存在右孩子结点
			j++;                                       //若右孩子较大，则j指向右孩子结点
		if (h[j].key > h[i].key)                       //若根节点小于最大孩子的关键字
		{
			temp = h[i];
			h[i] = h[j];                               //将R[j]调整到双亲结点位置上  
			h[j] = temp;
			i = j;                                     //交换后有可能破坏下一级的堆，因此需要再向下筛选，将j设为双亲结点
			j = 2 * i + 1;                             //j再设为原j结点的左孩子结点
		}
		else break;                                    //若根结点大于或等于最大孩子关键字，筛选结束
	}
}
void CreateMaxHeap(MaxHeap h[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)               //从最后一个分支结点开始，从右往左，从下向上进行筛选
		Sift(h, i, n);
}
