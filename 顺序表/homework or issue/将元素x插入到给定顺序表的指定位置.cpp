/*  题目：
将元素x插入到给定顺序表的指定位置,输入的最后一个数据为插入的位置。
用例1：输入:1 2 3 4 5 3
输出：1 2 x 3 4 5
用例2：输入 1 2 3 4 5 1
输出：x 1 2 3 4 5
用例3：输入 1 2 3 4 5 6
输出：1 2 3 4 5 x
用例4：输入 1
输出：x
*/


#include<iostream>
#include<vector>
#include<string>
using namespace std;
#define MaxSize 10
typedef string ElemType;
typedef struct
{
	ElemType data[MaxSize];
	int length;
}SqList;


//_________使用函数来输入____________
void InputList(SqList& L,int &n)             //将输入的不定数量的元素存储到顺序表中
{
	string Str;
	vector<string> storage;            //先用vector存储所有输入的数据,最后一个数据为插入的位置
	while (cin >> Str)
	{
		storage.push_back(Str);          
		if (getchar() == '\n')           //输入换行后停止输入
			break;
	}
	L.length = storage.size()-1;   //输入的最后一个元素为元素插入的位置，顺序表实际长度为vector长度-1
	for (int i = 0; i < L.length; i++)
	{
		L.data[i] = storage[i];
  }
	n=atoi(storage[storage.size()-1].c_str());    //最后输入的位置的数据实际上是以string形式存储的，利用atoi函数转化为int型
}


bool InsertList(SqList& L, int n, ElemType x)   
{
	if (n<1 || n>L.length+1) //插入元素可以放在最后，因此是 length+1
		return false;        //先判断能否正确输入，若输入的位置有误，则返回false
	int i;
	for (i = L.length; i >= n; i--)
	{
		L.data[i] = L.data[i - 1];
	}
	L.data[i] = x;           //此时i=n-1
	L.length++;              //插入一个元素后顺序表长度+1
	return true;
}

void Output(SqList L)
{
	for (int i = 0; i < L.length; i++)
		cout << L.data[i]<<' ';
}

int main()
{
	SqList StrList;
	StrList.length = 0;
	int position;
	InputList(StrList,position);
	ElemType elem = "x";                //插入的元素为"x"
	if (InsertList(StrList, position, elem))  //如果成功插入元素，则输出插入后的线性表
	{
		Output(StrList);
		return 0;
	}
	else
		return 0;
}



//________________example________________
//input:1 2 3 4
//output:1 2 3 x
//input:1
//ouput:x

//atoi函数可以将string型的变量转化为int型变量，前提是string里都是数字
//________________example________________
//string Str = "123";
//int n = atoi(Str.c_str());
//cout<< n << endl;

//output:123
