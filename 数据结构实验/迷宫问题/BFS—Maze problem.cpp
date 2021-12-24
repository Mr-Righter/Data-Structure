#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<queue>
using namespace std;
#define MaxSize 50
typedef struct node                              //�����Թ��Ľ��
{
	int x;                                       
	int y;
	int flag;                                    //flagΪ0��ʾ��ͨ��
	bool visited;                                //�ж��Ƿ����
	node* pre;                                   //��pre��¼�ý���ǰ����㣨�������Ĵ洢�ṹ��
}node;
int direct[4][2] = { 1,0,-1,0,0,-1,0,1 };
node maze[MaxSize][MaxSize];
void CreateMaze(int& r, int& c)                  //����ͼ
{
	ifstream infile;
	infile.open("maze.txt");
	infile >> r;
	infile >> c;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
		{
			infile >> maze[i][j].flag;
			maze[i][j].x = i;
			maze[i][j].y = j;
		}
	printf("maze:\n    ");
	for (int i = 0; i < c; i++)
		printf("%d ", i);
	printf("\n\n");
	for (int j = 0; j < r; j++)
	{
		printf("%d   ", j);
		for (int k = 0; k < c; k++)
			printf("%d ", maze[j][k].flag);
		printf("\n");
	}
	infile.close();
}

bool BFS(int r, int c, int x, int y)           //BFS�㷨
{
	node front;
	queue<node> Queue;                         //�������
	int x1, y1;
	if (maze[x][y].flag != 0)
		return false;
	maze[x][y].visited = true;
	maze[x][y].pre = NULL;                    //����ڵ�ǰ�������ΪNULL
	Queue.push(maze[x][y]);                   //��������
	while (!Queue.empty())                    //���Ӳ���ʱѭ��
	{
		front = Queue.front();
		Queue.pop();                          //������Ԫ�س���
		for (int i = 0; i < 4; i++)
		{
			x1 = front.x + direct[i][0];
			y1 = front.y + direct[i][1];
			if (0 <= x1 && x1 <= r && 0 <= y1 && y1 <= c)
			{
				if (maze[x1][y1].visited!=true && maze[x1][y1].flag != 1)
				{
					maze[x1][y1].pre = &maze[front.x][front.y];
					maze[x1][y1].visited = true;
					if (x1 == r  && y1 == c )  //�����յ�ʱ����true
						return true;
					Queue.push(maze[x1][y1]);  //���µĽ����ջ
				}
			}
		}


	}
	return false;
}
void Print(node p)                           //���õ������·��
{
	if (p.pre == NULL)
		printf("(%d,%d)", p.x, p.y);
	else
	{
		Print(*(p.pre));
		printf("(%d,%d)", p.x, p.y);
	}
}
int main()
{
	int r, c;
	CreateMaze(r, c);
	if (BFS(r - 1, c - 1, 0, 0))
	{
		printf("\nBFS_Path: ");
		Print(maze[r - 1][c - 1]);
	}
	else 
		printf("Path not found");
}