//队头指针front循环增1：front=(front+1)%MaxSize
//队尾指针rear循环增1：rear=(rear+1)%MaxSize
//循环队列的队头指针和队尾指针初始化时都置为0，即front=rear=0
//队空条件：p->front==p->rear
//队满条件：队尾指针循环加1时等于队头指针，即(q->rear+1) % MaxSize==q->front
//环形队少用一个元素空间，即该队列中在任何时刻最多只有一个MaxSize-1个元素

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
void InitQueue(SqQueue*& q)
{
	q = (SqQueue*)malloc(sizeof(SqQueue));
	q->front = q->rear = 0;                 //循环队列将front和rear指针初值均设置为初始状态，即0，而不是-1
}



//销毁队列
void DestoryQueue(SqQueue*& q)
{
	free(q);
}



//判断队列是否为空 
bool EmptyQueue(SqQueue* q)
{
	return(q->front == q->rear);
}



//进队列
bool QueueInsert(SqQueue*& q, ELemType e)
{
	if ((q->rear + 1) % MaxSize == q->front)           //堆满上溢出
		return false;
	else
	{
		q->rear = (q->rear + 1) % MaxSize;             //队尾指针循环加1
		q->data[q->rear] = e;
		return true;
	}
}




//出队列
bool QueueDelete(SqQueue*& q, ELemType& e)
{
	if (q->front == q->rear)
		return false;
	else
	{
		q->front = (q->front + 1) % MaxSize;
		e = q->data[q->front];
		return true;
	}
}



//判断循环队列中元素个数
int LengthQueue(SqQueue* q)
{
	return((q->rear - q->front + MaxSize) % MaxSize);
}
