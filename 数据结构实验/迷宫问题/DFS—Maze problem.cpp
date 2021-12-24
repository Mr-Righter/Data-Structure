#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
using namespace std;
#define MaxSize 50
int maze[MaxSize][MaxSize];
bool visited[MaxSize][MaxSize];
int path[MaxSize][2];
int direct[4][2] = { 0,1,0,-1,1,0,-1,0 };
void CreateMaze(int &r,int &c)
{
	ifstream infile;
	infile.open("maze.txt");
	infile >> r;
	infile >> c;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			infile >> maze[i][j];
	printf("maze:\n    ");
	for (int i = 0; i < c; i++)
		printf("%d ", i);
	printf("\n\n");
	for (int j = 0; j < r; j++)
	{
		printf("%d   ", j);
		for (int k = 0; k < c; k++)
			printf("%d ", maze[j][k]);
		printf("\n");
	}
	infile.close();
}

bool DFS(int r, int c, int x, int y,int step,int &length)
{
	int i, x1, y1;
	if (x == r  && y == c )
	{
		length = step + 1;                                      //length��¼·�����ȣ�����step��ֵΪ0����˳���Ϊstep+1
		return true;
	}
	visited[x][y] = true;                                       //��path��¼·���������ɷ���ʱ��step��1
	step++;                                                     //stepҪ����ѭ���⣬��������·��ʱ��step�������ܻᳬ��1
	for (i = 0; i < 4; i++)
	{
		x1 = x + direct[i][0];
		y1 = y + direct[i][1];
		if (0 <= x1 && x1 <= r && 0 <= y1  && y1 <= c)           //�жϸ�λ���Ƿ񳬹��Թ��߽�
		{
			if (visited[x1][y1] != true && maze[x1][y1] != 1)    //����λ�û�δ�����Ҳ�Ϊ�ϰ���
			{
				path[step][0] = x1;
				path[step][1] = y1;
				if(DFS(r, c, x1, y1, step, length))              //����һ��λ�ÿɴ�ʱ����true
					return true;
			}
		}
	}
	return false;                                                  //��û�ҵ�·���������з�������ﲻ�ˣ��򷵻�false
}


int main()
{
	int step = 0, length = 0;
	int r, c;                   //�����к���
	path[0][0] = 0;
	path[0][0] = 0;
	CreateMaze(r, c);
	if (DFS(r-1, c-1, 0, 0, step, length))
	{
		printf("\nDFS_Path: ");
		for (int i = 0; i < length; i++)
		{
			printf("(%d,%d) ", path[i][0], path[i][1]);
		}
	}
	else
		printf("Path not found");
	return 0;
}
