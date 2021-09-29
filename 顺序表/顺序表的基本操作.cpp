#include<iostream>
#include<cstdlib>
using namespace std;
#define MaxSize 50   //假设数据最多有50个
typedef int ElemType;      //定义元素类型为int型
typedef struct
{
	ElemType data[MaxSize];
	int length;            //length为存放线形表的长度
}SqList;                   //采用结构体类型定义SqList

//顺序表的建立
void CreateList(SqList* &L, ElemType a[], int n)  //采用顺序表指针的方式建立和使用顺序表
{
	L = (SqList*)malloc(sizeof(SqList));
	int i, k=0;            //k表示L中的元素个数，初始值为0
	for (i = 0; i < n; i++)
	{
		L->data[k] = a[i]; //i扫描数组a中的元素
		k++;               //此时k==n，而不是n-1
	}
	L->length = k;
}


//顺序表的初始化
void InitList(SqList*& L)     //要返回实参，因此要在形参L的前面加上引用符“&”
{
	L = (SqList*)malloc(sizeof(SqList));
	L->length = 0;
}


//销毁线性表
void DestroyList(SqList*& L)  //要返回实参，因此要在形参L的前面加上引用符“&”，且释放指针指向的地址
{
	free(L);
}


//判断线性表是否为空
bool ListEmpty(SqList*& L)  //该运算返回一个布尔值
{
	return(L->length == 0);  //判断L是否为空列表，是则返回true，否则返回false
}


//求线性表的长度
int ListLength(SqList*& L)
{
	return(L->length);
}

//输出线性表
void DisplayList(SqList*& L)
{
	for (int i = 0; i < (L->length - 1); i++)
	{
		cout << L->data[i] << endl; cout << "\n" << endl;
	}
}

//求线性表中某个数据的元素值
bool GetElem(SqList *L, int n, ElemType &e) //这里L不需要采用引用，而e需要用&，因为e是输出型参数
{
	if (n<1 || n>L->length)
		return false;
	e = L->data[n - 1];  //注意物理地址和逻辑地址
	return true;          //返回true表示找到了该数据的元素值
}

//按元素值查找
int LocateElem(SqList* L, ElemType e)
{
	int i = 0;
	for (i = 0; i < L->length;i++)
	{
		if (L->data[i] == e)
			return i + 1;    //找到后返回其逻辑序号
	}
	if (i >= L->length)
		return 0;            //未找到返回零
}

//插入数据元素
bool Listinsert(SqList*& L, int n, ElemType e)   //这里函数类型为bool型，来判断是否插入成功
{
	if (n<1 || n>L->length+1)  //注意插入的位置可以是length+1的位置，因此是n>length+1
		return false;          //参数位置n错误时返回false

	for (int i = L->length; i > n - 1; i--)  //插入一个元素后顺序表长度变为Length+1
	{
		L->data[i] = L->data[i - 1];
	}
	L->data[n - 1] = e;        
	L->length++;              //顺序表长度增加1
	return true;
	//程序要保证通用性，因此要先判断是否能执行，养成好习惯
}

//删除数据元素
bool ListDelete(SqList*& L, int n, ElemType &e)  //注意&e
{
	if (n<1 || n>L->length)
		return false;
	e = L->data[n - 1];          //这里用e返回删除的元素值
	for (int i = n - 1; i < L->length - 1; i++)
	{
		L->data[i] = L->data[i + 1];
	}
	L->length--;
	return true;
}
