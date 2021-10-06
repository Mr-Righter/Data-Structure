#include<iostream>
#include<cstdlib>
typedef char ElemType;
typedef struct LinkStNode
{
	ElemType data;
	LinkStNode* next;
}LinkStNode;

 
//初始化栈
void InitStack(LinkStNode*& s)
{
	s = (LinkStNode*)malloc(sizeof(LinkStNode));
	s->next = NULL;
}



//销毁栈
void DestoryStack(LinkStNode*& s)
{
	LinkStNode* pre = s;                 //pre指向头节点
	LinkStNode* p = s->next;             //p指向首结点
	while (p != NULL)                    //循环到p为空为止
	{
		free(pre);                       //释放pre结点
		pre = p;                
		p = pre->next;                   //pre，p结点同步后移
	}
	free(pre);                           //此时pre指向尾结点，释放其空间
}



//判断栈是否为空
bool EmptyStack(LinkStNode* s)
{
	return(s->next == NULL);
}



//进栈
void Push(LinkStNode*& s, ElemType e)              //由于只有在内存溢出时才出现栈满，所以在链栈中可以看成不存在栈满
{
	LinkStNode* p;                                 //新建结点p
	p = (LinkStNode*)malloc(sizeof(LinkStNode));   
	p->data = e;                                   //存放元素e
	p->next = s->next;                             //将p结点插入作为新的首结点
	p->next = s->next;                             
	s->next = p;
}
//这里进栈操作是将创建的结点插入到头节点之后作为新的首结点（与头插法类似）



//出栈
bool Pop(LinkStNode*& s, ElemType& e)
{
	LinkStNode* p = s->next;
	if (p == NULL)                         //栈空的情况（栈下溢出）
		return false;                      //返回假
	else
	{
		e = p->data;                       //提取首结点值
		s->next = p->next;                 //删除首结点
		free(p);
		return true;
	}
}



//获取栈顶元素
bool GetTop(LinkStNode* s, ElemType& e)
{
	if (s->next == NULL)
		return false;
	else
	{
		e = s->next->data;
		return true;
	}
}



/*例题：设计一个算法判断输入的表达式中括号是否配对（假设只含有左右圆括号）*/
bool Match(char str[], int n)
{
	int i = 0;
	char e;                                 //用e来存储栈顶元素
	LinkStNode* Stack;                            
	InitStack(Stack);
	bool match = true;                      //match初值设为true
	while(i < n && match)                   //扫描str中的所有字符，且仅当match==true时执行循环
	{
		if (str[i] == '(')                  //当前字符为左括号，将其进栈
			Push(Stack,str[i]);
		else if (str[i] == ')')             //当前字符为右括号
		{
			if (GetTop(Stack, e))           //若成功取得栈顶元素e
			{
				if (e != '(')               //当栈顶元素不为'('时
					match = false;          //表示不匹配
				else                        //栈顶元素为')'时
					Pop(Stack, e);          //将栈顶元素出栈
			}
			else
				match = false;              //无法取得栈顶元素时表示不匹配（此时栈为空）
		}
		i++;                                //继续处理其他元素（且要求此时match==true时才能执行循环）
	}
	if (!EmptyStack(Stack))                 //栈不空时表示不匹配（比如全是'('的情况）
		match = false;                      //表示不匹配
	DestoryStack(Stack);                    //销毁栈，最后一定要释放内存
	return match;                           //返回match的值
}
/*设置一个链栈Stack，扫描表达式str，遇到左括号时进栈；遇到右括号，若栈顶为左括号，则出栈，否则返回假。
  当表达式扫描完毕而且栈为空时返回真；否则返回假*/
