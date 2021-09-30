#include<iostream>
#include<string>
#include<vector>
using namespace std;
#define MaxSize 10
typedef string ElemType;

typedef struct
{
	ElemType data[MaxSize];
	int length;             
}SqList;   

void DeleteElem(SqList &L, ElemType e)
{
	int i, k = 0;        //k是新线性表的元素地址，i是原来线性表的元素地址
	for (i = 0; i < L.length; i++)
	{
		if (L.data[i] != e)
		{
			L.data[k] = L.data[i];
			k++;
		}
	}
	L.length = k ;
}
int main()
{
	SqList StrList;  //使用顺序表指针的方式
	StrList.length = 0;
	string Elem;

	//用vector来存储输入的数量不定的元素
	vector<string> storage;     
	int i = 0;
	while (cin >> Elem)
	{
		storage.push_back(Elem);   //在vector最后添加元素
		if (cin.get() == '\n') break;   //按下回车后退出循环
	}


	for (int i = 0; i < storage.size(); i++)  //vector.size()表示容器中的元素个数
	{
		StrList.data[i] = storage[i];
		StrList.length++;
	}

	DeleteElem(StrList, "x");
	if (StrList.length == 0)      //如果顺序表中没有元素则输出换行
		cout << '\n';
	else
	{
		for (int i = 0; i < StrList.length; i++)
		{
			cout << StrList.data[i] << ' ';
		}
		cout << '\n';
	}
	return 0;
}

//________example___________
//input:11 22 33 x x 44 55
//output:11 22 33 44 55
