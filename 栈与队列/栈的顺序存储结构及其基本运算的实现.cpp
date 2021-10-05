#include<iostream>
#include<cstdlib>
using namespace std;
#define MaxSize 50        //假设栈的元素个数最大不超过正整数MaxSize=50
typedef int ElemType;     //假设数据类型为int型

typedef struct                 //声明顺序栈SqStack
{
	ElemType data[MaxSize];    //存放栈中的数据元素
	int top;                   //栈顶指针，即存放栈顶元素在data数组中的下表
}SqStack;                      //顺序栈类型


//初始化栈表
void InitStack(SqStack*& s)
{ 
	s = (SqStack*)malloc(sizeof(SqStack));      //分配一个顺序栈空间，首地址存放在s中
	s->top = -1;                                //栈顶指针置为-1
}



//销毁栈
void DistoryStack(SqStack* &s)
{
	free(s);
}



//判断栈是否为空
bool EmptyStack(SqStack* s)
{
	return(s->top == -1);
}



//进栈
bool Push(SqStack* s, ElemType e)
{
	if (s->top == MaxSize - 1)            //栈满的情况，栈上溢出
		return false;
	else
	{
		s->top++;                         //栈顶指针增加1
		s->data[s->top] = e;              //元素e放在栈顶指针处
		return true;
	}
}



//出栈
bool Pop(SqStack*& s, ElemType& e)
{
	if (s->top == -1)
		return false;
	else
	{
		e = s->data[s->top];               //用e返回删除的数组值
		s->top--;
		return true;
	}
}



/*例题：设计一个算法用顺序栈判断是否是一为对称字符串。所谓对称字符串指从左向右读和从右向左读的序列相同*/

bool Symmetry(ElemType str[])               //symmetry指对称性，这里输入一个字符串str[]
{
	SqStack* s;
	InitStack(s);
	ElemType e;
	for (int i = 0; str[i] != '\0'; i++)   //将str的所有元素进栈，判断依据是不为'\0'，并且调用函数Push
	{
		Push(s, str[i]);                   
	}
	for (int i = 0; str[i] != '\0'; i++)   //处理所有str的字符
	{
		Pop(s, e);                         //用e存储退栈元素
		if (e != str[i])                   //若e与当前串字符不同则表示不是对称串
		{
			free(s);                       //这里注意要释放s的内存！！！
			return false;
		}
	}
	free(s);                               //释放s内存
	return true;                           //返回真
}
//n个元素连续进栈，产生的连续出栈序列和输入序列正好相反








