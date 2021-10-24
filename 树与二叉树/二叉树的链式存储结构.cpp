#include<iostream>
#include<cstdlib>
#define MaxSize 100
typedef char ElemType;
typedef struct BTNode
{
	ElemType data;                       //数据元素
	struct BTNode* lchild;               //指向左孩子结点
	struct BTNode* rchild;               //指向右孩子结点
}BTNode;


//创建二叉树
void CreatBTNode(BTNode* &b,char* str)
{
	BTNode* Stack[MaxSize];                                     //Stack数组作为顺序栈，存储树的结点指针
	BTNode* p=NULL;           
	int k, top = -1, j = 0;                                     //k的数值表示左或右孩子结点，top作为栈顶指针
	char ch = str[j];                                           //用ch扫描二叉树字符串
	b = NULL;                                                   //初始时二叉链为空
	while (ch != '\0')                                          //循环扫面str中的每个字符
	{
		switch (ch)
		{
		case '(':top++; Stack[top] = p; k = 1; break;           //开始处理左孩子结点
		case ')':top--; break;                                  //栈顶结点的子树处理完毕
		case ',':k = 2; break;                                  //开始处理右孩子结点
		default:
			p = (BTNode*)malloc(sizeof(BTNode));                //创建一个结点并用p指向它
			p->data = ch;                                        
			p->lchild = p->rchild = NULL;                       //将左右指针域均为空
			if (b == NULL)                                       //若尚未建立根节点
			{
				b = p;                                          //p所指结点就作为根结点
			}
			else
			{
				switch (k)
				{
				case 1:Stack[top]->lchild = p; break;           //k=1,新建结点就作为栈顶结点的左孩子结点
				case 2:Stack[top]->rchild = p; break;           //k=2,新建结点就作为栈顶结点的右孩子结点
				}
			}
		}    
		j++;
		ch = str[j];                   
	}                                                  //返回根结点地址      
}


//销毁二叉树
void DestoryBTree(BTNode* b)
{
	if (b != NULL)
	{
		DestoryBTree(b->lchild);
		DestoryBTree(b->rchild);
		free(b);
	}
}


//查找结点
BTNode* FindNode(BTNode* b, ElemType x)
{
	BTNode* p;                                            
	if (b == NULL) 
		return NULL;                                              
	else if (b->data == x)
		return b;
	else
	{
		p = FindNode(b->lchild, x);
		if (p != NULL)                                //这里要对左子树是否为空进行一个判断，若直接返回FindNode(b->lchild,x),则当左子树为空时就直接返回NULL了，而未考虑在右子树的情况
			return p;
		else
			return FindNode(b->rchild, x);            
	}
}
//递归模型
//f(b,x)=NULL          若b==NULL
//f(b,x)=b             若b->data==x
//f(b,x)=p             若在左子树中找到了，p=f(b->lchild,x)且p!=NULL
//f(b,x)=f(b->rchild)  其他情况（包括找不到和在右子树中找到了）



//求树高度
int TreeHeight(BTNode* b)
{
	int lchildHeight, rchildHeight;
	if (b == NULL)
		return(0);
	else
	{
		lchildHeight = TreeHeight(b->lchild);                      //左子树高度
		rchildHeight = TreeHeight(b->rchild);                      //右子树高度
		return (lchildHeight > rchildHeight) ? (lchildHeight + 1) : (rchildHeight + 1);    //返回两者最大值+1
	}
}
//递归模型
//f(b)=0                                    if b=NULL
//f(b)=MAX(f(b->lchild),f(b-rchild))+1      else


//输出二叉树
void DisplayBTree(BTNode* b)
{
	if (b != NULL)
	{
		printf("%c", b->data);
		if (b->lchild != NULL || b->rchild != NULL)
		{
			printf("(");
			DisplayBTree(b->lchild);
			if (b->rchild != NULL)
				printf(",");
			DisplayBTree(b->rchild);
			printf(")");
		}
	}
}


//二叉树的遍历
//先序遍历
void PreOrder(BTNode* b)
{
	if (b != NULL)
	{
		printf("%c", b->data);
		PreOrder(b->lchild);
		PreOrder(b->rchild);
	}
}

//中序遍历
void InOrder(BTNode* b)
{
	if (b != NULL)
	{
		InOrder(b->lchild);
		printf("%c", b->data);
		InOrder(b->rchild);
	}
}

//后序遍历
void LastOrder(BTNode* b)
{
	if (b != NULL)
	{
		LastOrder(b->lchild);
		LastOrder(b->rchild);
		printf("%c", b->data);
	}
}

//测试
int main()
{
	char str[] = "A(B(D(,G)),C(E,F)))";
	BTNode* Tree=NULL; 
	CreatBTNode(Tree, str);
	DisplayBTree(Tree);
}
