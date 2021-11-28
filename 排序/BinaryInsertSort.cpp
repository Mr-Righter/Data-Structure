#include<iostream>
typedef int KeyType;
typedef char InfoType;
typedef struct RecType
{
	KeyType key;
	InfoType data;
}RecType;

void BinaryInsertSort(RecType R[], int n)
{
	int i, j, low, high, mid;                         
	RecType temp;
	for (i = 1; i < n; i++)
	{
		if (R[i].key > R[i - 1].key)
		{
			temp = R[i];                            //将R[i]保存到temp中
			low = 0;
			high = i - 1;
			while (low <= high)                     //在R[low..high]中查找位置
			{
				mid = (low + high) / 2;             //取中间位置
				if (temp.key < R[mid].key)
					high = mid - 1;                 //插入点在左半区
				else
					low = mid + 1;                  //插入点在右半区
			}
			//这里当low=high时只需要再循环一次，即判断插入的元素是在mid=(low+high)/2的右边还是左边，执行完成后high=low-1，插入的位置为high+1
			for (j = i; i > high + 1; i--)          //将R[high+1...i-1]元素后移一个位置
			{
				R[j] = R[j - 1];
			}
			R[high + 1] = temp;                     //置R[high+1]=temp
		}
	}
}
