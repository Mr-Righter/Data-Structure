#include<iostream>
#define Num 50
#define MaxWeight 100
typedef char ElemType;
typedef struct HTNode                                     //哈夫曼树结点的结构体
{
	ElemType data;
	int weight;
	int parent;
	int lchild;
	int rchild;
}HTNode;

void CreateBTNode(HTNode ht[], int n0)                    //n0为叶子结点的个数
{
	int lnode, rnode;                                  
	double min1, min2;                                  
	int i, j;                                           
	for (i = 0; i < 2 * n0 - 2; i++)                    
		ht[i].lchild = ht[i].rchild = ht[i].parent = -1;  //所有结点的相关域初值置为-1
	for (i = n0; i < 2 * n0 - 2; i++)                     //构造n0-1个分支结点
	{
		min1 = min2 = MaxWeight;                          //min1和min2扫描并记录最小的两个权值，初值置为MaxWeight
		lnode = rnode = -1;							      //lnode和rnode扫描并记录权值最小两个结点的位置
		for (j = 0; j <= n0 - 1; j++)
		{
			if (ht[j].parent == -1)                       //只在尚未构造的二叉树节点中查找
			{
				if (ht[j].weight < min1)                  
				{
					min2 = min1;
					rnode = lnode;
					min1 = ht[j].weight;
					lnode = j;
				}
				else if (ht[j].weight < min2)
				{
					min2 = ht[j].weight;
					rnode = j;
				}
			}                                             //查找并记录权值最小的两个结点的序号和它们的权值
		}
		ht[i].weight = ht[lnode].weight + ht[rnode].weight;   //父亲结点的权值等于左右子树权值之和
		ht[lnode].parent = ht[rnode].parent = i;              //左右子树的父亲结点的位置置为i
		ht[i].lchild = lnode;                                 
		ht[i].rchild = rnode;                                 //父亲结点的左右子树位置分别置为lnode和rndoe
	}
}


//哈夫曼编码
typedef struct HTCode
{
	char code[Num];                 //这里通常将Num设为叶子结点的个数，这里假设为50
	int start;
};

//根据哈夫曼树求对应的哈夫曼编码
void CreateCode(HTNode ht[], HTCode num[], int n0)
{
	int i, f, c;                                  //i为循环变量                        
	HTCode hc;                                    //hc为第i个节点的哈夫曼编码
	for (i = 0; i < n0; i++)
	{
		hc.start = n0;                            //start从n0开始，编码也从后往前输入到hc中
		f = ht[i].parent;                         //f（father）为第i个节点的父亲节点的位置
		c = i;                                    //c（child）为当前结点的位置
		while (f != -1)                           //直到循环到无双亲结点
		{
			if (ht[f].lchild == c)                //当前结点为双亲结点的左孩子
			{
				hc.code[hc.start] = '0';          //编码输入'0'
				hc.start--;
			}
			if (ht[f].rchild == c)                //当前结点为双亲结点的右孩子
			{
				hc.code[hc.start] = '1';          //编码输入'1'
				hc.start--;
			}
		}
		hc.start++;                               //start+1，此时start指向哈夫曼编码最开始的字符
		num[i] = hc;                              //将哈夫曼编码存储到编码数组中
	}
}
