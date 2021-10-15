#include<stdio.h>
#include<string.h>
#define MaxSize 50
typedef struct                                   //定义一个顺序串
{
	char data[MaxSize];
	int length;
}SqString;

int main()
{
	
	char str1[] = "abacababdeadcde";            
	SqString txt;
	int i;
	for (i = 0; str1[i] != '\0'; i++)
	{
		txt.data[i] = str1[i];
	}
	txt.length = i;                             //构造一个名称为txt的主串
	
	
	SqString cstr;
	char str2[MaxSize];
	gets(str2);                                 //用gets()获取一行字符
	for (i = 0; str2[i] != '\0'; i++)
	{
		cstr.data[i] = str2[i];
	}
    cstr.length = i;                            //构造一个名称为cstr的模式串
	

	int next[MaxSize];
	next[0] = -1;
	int now = -1;
	int x = 0;
	while (x < cstr.length - 1)
	{
		if (now == -1 || cstr.data[x] == cstr.data[now])
		{
			now++;
			x++;
			next[x] = now;
		}
		else
			now = next[now];
	}                                         //求next数组

  
	i = 0;
	int j = 0;
	while (i < txt.length && j < cstr.length)         //注意这里是&&，不是||，要保证i和j同时不越界
	{
		if (txt.data[i] == cstr.data[j] || j == -1)
		{
			i++;
			j++;
		}
		else
			j = next[j];
	}
  
  
	if (j >= cstr.length)                     //匹配成功
	{
		printf("匹配成功\n");
		for (i = 0; i < cstr.length; i++)
			printf("%d", next[i]);
	}
  
  
	else                                      //匹配失败
	{
		printf("匹配未成功\n");
		for (i = 0; i < cstr.length; i++)
			printf("%d", next[i]);
	}
}

//C语言不能用引用真是太麻烦了，STL也用不了，全部要地址传递，我太菜了，只好全放在一个main函数里，反正能过就够了
