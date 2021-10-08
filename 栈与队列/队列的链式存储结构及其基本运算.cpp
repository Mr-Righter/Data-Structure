#include<iostream>
typedef int ElemType;
class QNode
{
public:
	ElemType data;
	QNode* next;
};


class LinkQueue
{
private:
	QNode* front;
	QNode* rear;

public:
	void InitQueue(LinkQueue& Q);              //初始化链队列
	void DestoryQueue(LinkQueue& Q);           //销毁链队列
	bool IsEmpty(LinkQueue& Q);                //判断链队列是否为空
	void enQueue(LinkQueue& Q, ElemType e);    //入队
	bool deQueue(LinkQueue& Q, ElemType& e);   //出队
};

void LinkQueue::InitQueue(LinkQueue& Q)      //类外定义成员函数，必须在函数名前面加上类名，予以限定(qualifed)，其中"::"是作用域限定符(field qualifier)或称作用域运算符，用它声明函数是属于哪个类的
{
	QNode* p = new QNode;                    //创建一个链队结点
	p->next = NULL;
	Q.front = Q.rear = p;                    //其front域和rear域均置为NULL       
}


void LinkQueue::DestoryQueue(LinkQueue& Q)
{
	QNode* pre = Q.front;                    //pre指向队首结点
	QNode* p;                                
	if (Q.front != NULL)                     //若首结点不为空   （在链表中有头节点且不为空，这里pre指向首结点，因此要考虑队列（首结点）为空的情况）
		p = pre->next;                       //则p指向pre的后继结点
	while (p != NULL)                        //p不为空时循环
	{
		delete(pre);                         //释放pre结点
		pre->next = p;
		p = p->next;                         //pre和p同步后移
	}
	delete(pre);                             //释放最后一个结点
}



bool LinkQueue::IsEmpty(LinkQueue& Q)
{
	return(Q.front == NULL);               //当front指针和rear指针相同时为空
}
//注意当Q.front==Q.rear时不一定为空，也可以时只有一个结点！！！


void LinkQueue::enQueue(LinkQueue& Q, ElemType e)
{
	QNode* p = new QNode;                    //创建新结点
	p->data = e;                              
	p->next = NULL;                          //创建的结点的next域要置为NULL，因为是在队尾插入
	if (IsEmpty)                             //注意要考虑链队为空的情况，此时Q.rear==NULL
		Q.front = Q.rear = p;                  //则新结点既是队首结点也是队尾结点
	else                                     //若链队不为空
	{
		Q.rear->next = p;                    //将结点p链到队尾，并用rear指向它
		p = Q.rear;                          
	}
}



bool LinkQueue::deQueue(LinkQueue& Q, ElemType& e)
{
	QNode* p = Q.front;                       //p指向首结点
	if (p == NULL)                            //若链队列为空
		return false;
	else if (Q.front==Q.front)                //当链队列只有一个数据结点时，即出队后链队列为空
	{
		e = p->data;
		Q.front = Q.rear = NULL;              //删除前先将链队的front和rear均置为NULL！！
		delete(p);
	}
	else                                      //原来队列有两个及以上的结点
	{
		e = p->data;
		delete(p);
	}
	return true;
}


