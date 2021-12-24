#include<iostream>
#include<string>
#define MAXV 16
using namespace std;

typedef struct VertexType   //顶点的类型
{
	int farmer;
	int wolf;
	int sheep;
	int vegetable;
}VertexType;

typedef struct MatGraph     
{
	int n;                      //边数和定点数
	int edges[MAXV][MAXV];      //邻阶矩阵
	VertexType Vertexs[MAXV];   //存放顶点信息
}MatGraph;                      // 定义图的邻接矩阵存储结构


int visited[MAXV] = { 0 };

//判断情景是否安全
bool IsSafe(int farmer, int wolf, int sheep, int vegetable)
{
	//狼与羊或羊与白菜在一起且此时农夫不在场时是不安全的
	if (farmer != sheep && (wolf == sheep || sheep == vegetable))   
		return false;
	else      
		return true;
}

//根据位置确定结点序号
int locate(MatGraph G, int farmer, int wolf, int sheep, int vegetable)
{
	for (int i = 0; i < G.n; i++)
	{
		if (G.Vertexs[i].farmer == farmer && G.Vertexs[i].wolf == wolf && G.Vertexs[i].sheep == sheep && G.Vertexs[i].vegetable == vegetable)
			return i; //返回当前位置
	}
	return -1;
}

// 判断状态i与状态j之间是否可转换
bool isConnect(MatGraph G, int i, int j)
{
	int k = 0;
	if (G.Vertexs[i].sheep != G.Vertexs[j].sheep)         
		k++;
	if (G.Vertexs[i].wolf != G.Vertexs[j].wolf)   
		k++;
	if (G.Vertexs[i].vegetable != G.Vertexs[j].vegetable)   
		k++;
	if (G.Vertexs[i].farmer!= G.Vertexs[j].farmer && k <= 1)     // 以上三个条件不同时满足两个且农夫状态改变时，返回真, 也即农夫每次最多只能带一件东西过桥
		return true;
	else 
		return false;
}

// 创建连接图
void CreateMatGraph(MatGraph &G)
{
    int i = 0; int j = 0;
    for (int farmer = 0; farmer <= 1; farmer++)      
    {
        for (int wolf = 0; wolf <= 1; wolf++)
        {
            for (int sheep = 0; sheep <= 1; sheep++)
            {
                for (int vegetable = 0; vegetable <= 1; vegetable++)
                {
                    if (IsSafe(farmer, wolf, sheep, vegetable))      // 生成所有安全的图的顶点
                    {
                        G.Vertexs[i].farmer = farmer;
                        G.Vertexs[i].wolf = wolf;
                        G.Vertexs[i].sheep = sheep;
                        G.Vertexs[i].vegetable = vegetable;
                        i++;
                    }
                }
            }
        }
    }
    // 邻接矩阵初始化即建立邻接矩阵
    G.n = i;           //图中安全结点数量赋值为i
    for (i = 0; i < G.n; i++)
    {
        for (j = 0; j < G.n; j++)
        {
            // 状态i与状态j之间可转化，初始化为1，否则为0
            if (isConnect(G, i, j) )
                G.edges[i][j] = 1;
            else        
                G.edges[i][j] = 0;
        }
    }
}

// 判断在河的哪一边
string judgement(int state)
{
    if (state == 0)  
        return "左岸";
    else
        return  "右岸";
}

//输出path中的结点信息
void printPath(MatGraph G, int d,int path[])        //d为路径长度
{
    int i,j;
    cout << "      farmer\t" << "wolf\t" << "sheep\t" << "vegetable\t" << endl;
    for(i=0;i<=d;i++)
    {
        j = path[i];
        cout <<"第"<<i<<"趟:"<<"(" << judgement(G.Vertexs[j].farmer)<<"\t"<<
            judgement(G.Vertexs[j].wolf) << "\t" << judgement(G.Vertexs[j].sheep) << "\t" <<
            judgement(G.Vertexs[j].vegetable) << ")";
        cout << endl;
    }
}

//基于深度优先输出路径
void FindPath(MatGraph G, int start, int end, int path[], int d)
{
    int i;
    d++;
    path[d] = start;
    visited[start] = 1;
    if (start == end)
    {
        printPath(G, d, path);
        return;
    }
    for (i = 0; i < G.n; i++)
    {
        if (G.edges[start][i] == 1 && visited[i] == 0)
        {
            FindPath(G, i, end, path, d);
        }
    }
}


int main()
{
    MatGraph Graph;
    CreateMatGraph(Graph);
    int start = locate(Graph, 0, 0, 0, 0);       //确定初始状态和最终状态对应的图结点的编号
    int end = locate(Graph, 1, 1, 1, 1);
    int d = -1;                                  //路径长度初始值置为-1
    int path[MAXV] = { -1 };
    FindPath(Graph, start, end, path, d);
    return 0;
}