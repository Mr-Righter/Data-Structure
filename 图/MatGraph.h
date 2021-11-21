#pragma once
#include<iostream>
#define INF 32767
#define MAXV 20
typedef char InfoType;
typedef struct VetexType
{
	int no;                  //顶点编号
	InfoType info;           //顶点的其他信息
}VetexType;                  //顶点的类型
typedef struct MatGraph
{
	int n, e;                //定点数，边数
	int edges[MAXV][MAXV];   //邻阶矩阵数组
	VetexType vexs[MAXV];    //存放顶点信息
}MatGraph;
