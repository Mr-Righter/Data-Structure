#include<iostream>
#define MaxSize 50
class SqString
{
private:
	char data[MaxSize];
	int length;

public:
	SqString()                                    //构造函数，初始化串（长度置为0）
	{
		length = 0; 
	}
	void StrAssign(char cstr[]);                  //生成串
	void StrCopy(SqString s);                     //复制串
	bool StrEqual(SqString& s);                   //判断串是否相等
	int StrLength();                              //求串长
	SqString StrConcat(SqString t);               //串的连接
	SqString InStr(int i, SqString s2);            
	SqString Getsub(int i, int j);
	SqString RepStr(int i, int j, SqString t);
};



//创建串
void SqString::StrAssign(char cstr[])             //s为引用型参数        
{
	int i;
	for (i = 0; cstr[i] != '\0'; i++)                          
		data[i] = cstr[i];
	length = i;                        //设置串的长度
}



//串的复制
void SqString::StrCopy(SqString s)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		data[i] = s.data[i];
	}
	length = s.length;
}



//判断串相等
bool SqString::StrEqual(SqString& s)
{
	if (length != s.length)                    //长度不相同时返回false（对长度要有一个判断）
		return false;                 
	for (int i = 0; i < s.length; i++)
	{
		if (data[i] != s.data[i])
			return false;
	}
	return true;
}


//求串长
int SqString::StrLength()
{
	return(length);
}



//串的连接
SqString SqString::StrConcat(SqString s)
{
	SqString str;
	str.length = s.length + length;                    //生成一个新串，串长等于原串长之和
	int i ;
	for (i = 0; i < length; i++)
		str.data[i] = s.data[i];
	for (i = length; i < str.length; i++)
		str.data[i] = s.data[i];
	return str;                                          //返回一个SqString类型的数据
}



SqString SqString::InStr(int i, SqString s)
{
	int j;
	SqString str;                                         //定义结果为串 
	str.length = 0;                                       //设置str初始为空（初始化）
	if (i <= 0 || i > length + 1)                      
		return str;                                       //参数不正确返回空
	for (j = 0; j < i - 1; j++)
		str.data[j] = data[j];                         
	for (j = 0; j < s.length ; j++)
		//str.data[i+j-1] = s.data[j];                      //从i-1开始插入
	for (j = i - 1; j < length + s.length; j++)
		str.data[j + s.length] = data[j];
	str.length = length + s.length;
	return str;
}


SqString SqString::Getsub(int i, int j)//找到从位置i开始，长度为j的子串，并返回
{
	SqString temp;
	if (i<0 || i>length || j<0 || i - 1 + j>length)
		return temp;
	else
	{
		for (int k = 0; k < j; k++)
		{
			temp.data[k] = data[i - 1 + k];
			temp.length++;
		}
		return temp;
	}
}


SqString SqString::RepStr(int i, int j, SqString t)
//将串中第i个元素开始，长度为j的字符串，用子串t代替
{
	SqString temp;
	if (i<0 || i>length || j<0 || i - 1 + j>length)
		return temp;
	else
	{
		if (t.length == j)
		{
			int k;
			for (k = 0; k < i - 1; k++)
			{
				temp.data[k] = data[k];
			}
			for (k; k < i - 1 + j; k++)
			{
				temp.data[k] = t.data[k - i + 1];
			}
			for (k; k < length; k++)
			{
				temp.data[k] = data[k];
			}
			temp.length = length;
			return temp;
		}
		else//这里的条件是子串的长度小于j，填不满空余位置
		{
			int k;
			for (k = 0; k < i - 1; k++)
			{
				temp.data[k] = data[k];
			}
			for (k; k < i - 1 + t.length; k++)
			{
				temp.data[k] = t.data[k - i + 1];
			}
			for (k; k < length - j + t.length; k++)
			{
				temp.data[k] = data[k + j - t.length];
			}
			temp.length = length + t.length - j;
			return temp;
		}
	}
}



