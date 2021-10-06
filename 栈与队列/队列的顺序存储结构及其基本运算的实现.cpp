//队空的条件：q->front==q->rear
//队满的条件：q->rear==MaxSize-1(data数组的最大下表）
//元素e的进队操作：先将rear增加1，然后将元素e放在data数组的rear位置
//出队操作：先将front增加1，然后取出data数组中front位置的元素。

#include<iostream>
#include<cstdlib>
#define MaxSize 50
typedef int ELemType;
typedef struct SqQueue
{
	ELemType data[MaxSize];                 //存放队中元素
	int front, rear;                        //队头和队尾指针 
}SqQueue;                                   //顺序队类型



//初始化队列
void InitQueue(SqQueue* &q)
{
	q = (SqQueue*)malloc(sizeof(SqQueue));           //构造一个空队列
	q->front = q->rear = -1;                         //将front和rear指针均置为初始状态，即-1值
}



//销毁队列
void Destory(SqQueue*& q)
{
	free(q);
}



//判断队列是否为空
bool EmptyQueue(SqQueue* q)
{
	return(q->front == q->rear);                    //当q->front==q->rear时为空
}



//进队列
bool QueueInsert(SqQueue* &q, ELemType e)
{
	if (q->rear == MaxSize - 1)                    //队满上溢出
		return false;                              //返回假
	else
	{
		q->rear++;                                 //队尾加1
		q->data[q->rear] = e;                      //rear位置插入元素e
		return true;                               //返回真
	}
}



//出队列
bool QueueDelete(SqQueue*& q, ELemType& e)
{
	if (q->front == q->rear)                       //队空下溢出
		return false;                              
	else
	{
		q->front++;
		q->data[q->front] = e;                     //返回e
		return true;
	}
}


