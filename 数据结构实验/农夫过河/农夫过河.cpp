#include<iostream>
#include<string>
#define MAXV 16
using namespace std;

typedef struct VertexType   //���������
{
	int farmer;
	int wolf;
	int sheep;
	int vegetable;
}VertexType;

typedef struct MatGraph     
{
	int n;                      //�����Ͷ�����
	int edges[MAXV][MAXV];      //�ڽ׾���
	VertexType Vertexs[MAXV];   //��Ŷ�����Ϣ
}MatGraph;                      // ����ͼ���ڽӾ���洢�ṹ


int visited[MAXV] = { 0 };

//�ж��龰�Ƿ�ȫ
bool IsSafe(int farmer, int wolf, int sheep, int vegetable)
{
	//�����������ײ���һ���Ҵ�ʱũ���ڳ�ʱ�ǲ���ȫ��
	if (farmer != sheep && (wolf == sheep || sheep == vegetable))   
		return false;
	else      
		return true;
}

//����λ��ȷ��������
int locate(MatGraph G, int farmer, int wolf, int sheep, int vegetable)
{
	for (int i = 0; i < G.n; i++)
	{
		if (G.Vertexs[i].farmer == farmer && G.Vertexs[i].wolf == wolf && G.Vertexs[i].sheep == sheep && G.Vertexs[i].vegetable == vegetable)
			return i; //���ص�ǰλ��
	}
	return -1;
}

// �ж�״̬i��״̬j֮���Ƿ��ת��
bool isConnect(MatGraph G, int i, int j)
{
	int k = 0;
	if (G.Vertexs[i].sheep != G.Vertexs[j].sheep)         
		k++;
	if (G.Vertexs[i].wolf != G.Vertexs[j].wolf)   
		k++;
	if (G.Vertexs[i].vegetable != G.Vertexs[j].vegetable)   
		k++;
	if (G.Vertexs[i].farmer!= G.Vertexs[j].farmer && k <= 1)     // ��������������ͬʱ����������ũ��״̬�ı�ʱ��������, Ҳ��ũ��ÿ�����ֻ�ܴ�һ����������
		return true;
	else 
		return false;
}

// ��������ͼ
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
                    if (IsSafe(farmer, wolf, sheep, vegetable))      // �������а�ȫ��ͼ�Ķ���
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
    // �ڽӾ����ʼ���������ڽӾ���
    G.n = i;           //ͼ�а�ȫ���������ֵΪi
    for (i = 0; i < G.n; i++)
    {
        for (j = 0; j < G.n; j++)
        {
            // ״̬i��״̬j֮���ת������ʼ��Ϊ1������Ϊ0
            if (isConnect(G, i, j) )
                G.edges[i][j] = 1;
            else        
                G.edges[i][j] = 0;
        }
    }
}

// �ж��ںӵ���һ��
string judgement(int state)
{
    if (state == 0)  
        return "��";
    else
        return  "�Ұ�";
}

//���path�еĽ����Ϣ
void printPath(MatGraph G, int d,int path[])        //dΪ·������
{
    int i,j;
    cout << "      farmer\t" << "wolf\t" << "sheep\t" << "vegetable\t" << endl;
    for(i=0;i<=d;i++)
    {
        j = path[i];
        cout <<"��"<<i<<"��:"<<"(" << judgement(G.Vertexs[j].farmer)<<"\t"<<
            judgement(G.Vertexs[j].wolf) << "\t" << judgement(G.Vertexs[j].sheep) << "\t" <<
            judgement(G.Vertexs[j].vegetable) << ")";
        cout << endl;
    }
}

//��������������·��
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
    int start = locate(Graph, 0, 0, 0, 0);       //ȷ����ʼ״̬������״̬��Ӧ��ͼ���ı��
    int end = locate(Graph, 1, 1, 1, 1);
    int d = -1;                                  //·�����ȳ�ʼֵ��Ϊ-1
    int path[MAXV] = { -1 };
    FindPath(Graph, start, end, path, d);
    return 0;
}