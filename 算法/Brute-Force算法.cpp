#include<iostream>
#define MaxSize 50
class SqString        //顺序串
{
private:
	char data[MaxSize];
	int length;
public:          
	int BruteFroce(SqString s);
};



int SqString::BruteFroce(SqString s)        //判断s是否为子串
{
	int i = 0, j = 0;                         //用i指向字符串，j指向文本
	while (i < s.length && j < length)        //当两个串都未扫描完时循环
	{
		if (s.data[i] != data[j])               //若两个字符不相同
		{
			j = j - i + 1;                        //文本串的j回退，扫描位置比上一次开始的位置加1
			i = 0;                                //子串从头开始匹配
		}
		else                                    //若两个字符相同
		{
			i++;
			j++;                                  //依次比较后续的两个字符
		}
	}
	if (i >= s.length)                        //i超界，表示t是s的子串
		return(j - s.length);                   //返回字串在文本串中的位置（这里返回的是物理位置，不是逻辑位置）
	else                                      //模式匹配失败
		return(-1);                             //返回-1
}
