#include<iostream>
#define MaxSize 50
class SqString
{
public:
	char data[MaxSize];
	int length;
public: 
	int KMPIndex(SqString s);
};

void GetNext(SqString s,int next[])                  //由模式串求出next
{
	next[0] = -1;                                    //设置next[0]=-1（便于后续求解）
	int now = -1,x = 0;                              //用x来扫描s，now记录s[x]之前前缀与后缀相同的最大字符数 
	while (x < s.length-1)                           //求s所有的next值
	{
		if (s.data[x] == s.data[now]||now==-1)       //k==-1或比较的字符相等时
		{
			now++;                                   
			x++;                                     //now和x依次移动到下一个字符
			next[x] = now;                           //设置next[j]为k
		}
		else
		{
			now = next[now];                         //否则now回退
		}
	}
}

int SqString::KMPIndex(SqString s)
{
	int i = 0, j = 0;
	int next[100];
	GetNext(s, next);
	while (i < length && j < s.length)                      //注意这里是&&
	{
		if (data[i] == s.data[j] || j == -1)          
		{
			i++;
			j++;
		}
		else
			j = next[j];
	}
	if (j = s.length)                             //匹配成功
		return(i - s.length);                     //这里返回的是物理位置
	else                                          //匹配不成功
		return(-1);                               //返回-1
}
参考文献
//https://www.pythonf.cn/read/107379
//https://www.zhihu.com/question/21923021
//https://blog.csdn.net/v_july_v/article/details/7041827
