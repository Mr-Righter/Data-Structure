#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<queue>
using namespace std;
#define MaxSize 50
typedef struct node                              //构建迷宫的结点
{
	int x;                                       
	int y;
	int flag;                                    //flag为0表示可通过
	bool visited;                                //判断是否访问
	node* pre;                                   //用pre记录该结点的前驱结点（类似树的存储结构）
}node;
int direct[4][2] = { 1,0,-1,0,0,-1,0,1 };
node maze[MaxSize][MaxSize];
void CreateMaze(int& r, int& c)                  //创建图
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

bool BFS(int r, int c, int x, int y)           //BFS算法
{
	node front;
	queue<node> Queue;                         //定义队列
	int x1, y1;
	if (maze[x][y].flag != 0)
		return false;
	maze[x][y].visited = true;
	maze[x][y].pre = NULL;                    //将入口的前驱结点置为NULL
	Queue.push(maze[x][y]);                   //将入口入队
	while (!Queue.empty())                    //当队不空时循环
	{
		front = Queue.front();
		Queue.pop();                          //将队首元素出队
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
					if (x1 == r  && y1 == c )  //到达终点时返回true
						return true;
					Queue.push(maze[x1][y1]);  //将新的结点入栈
				}
			}
		}


	}
	return false;
}
void Print(node p)                           //利用迭代输出路径
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