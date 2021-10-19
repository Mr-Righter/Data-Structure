#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct LinkStNode
{
	char data;
	struct LinkStNode* next;
}LinkStNode;


int IsEmpty(LinkStNode* s)
{
	if (s->next == NULL)
		return 1;
	else
		return 0;
}

void DeleteStack(LinkStNode* s)
{
	LinkStNode* p=s;
	LinkStNode* q = s->next;
	while (q != NULL)
	{
		p = q;
		q = q->next;
		free(p);
	}
	free(s);
}


void push(LinkStNode* s, char e)
{
	LinkStNode* p;
	p = (LinkStNode*)malloc(sizeof(LinkStNode));
	p->data = e;
	p->next = s->next;
	s->next = p;
}


void pop(LinkStNode* s)
{
	if (IsEmpty(s) == 0)
	{
		LinkStNode* q = s->next;
		s->next = q->next;
		free(q);
	}
}

char GetTop(LinkStNode* s)
{
	if (IsEmpty(s) == 0)
		return(s->next->data);
	else
		return ('\0');
}


int main()
{
	char String[50];
	fgets(String, 50, stdin);
	LinkStNode* Stack;
	Stack = (LinkStNode*)malloc(sizeof(LinkStNode));
	Stack->next = NULL;
	int i = 0;
	int length = strlen(String);
	int flag = 1;
	while (i < length)
	{
		if (String[i] == '(' || String[i] == '[' || String[i] == '{')
		{
			push(Stack, String[i]);
		}
		else if (String[i] == ')')
		{
			if (IsEmpty(Stack)==0 && GetTop(Stack) == '(')
			{
				pop(Stack);
			}
			else
			{
				printf("缺少%c括号", '(');
				flag = 0;
			}
		}
		else if (String[i] == ']')
		{
			if (IsEmpty(Stack) == 0)
			{
				if (GetTop(Stack) == '[')
				{
					pop(Stack);
				}
				else if (GetTop(Stack) == '(')
				{
					printf("缺少%c括号", ')');
					pop(Stack);
					flag = 0;
				}
				else if (GetTop(Stack) == '{')
				{
					printf("缺少%c括号", '[');
					flag = 0;
				}
			}
			else if (IsEmpty(Stack) == 1)
			{
				printf("缺少%c括号", '[');
				flag = 0;
			}
		}
		else if (String[i] == '}')
		{
			if (IsEmpty(Stack) == 0)
			{
				if (GetTop(Stack) == '{')
				{
					pop(Stack);
				}
				else if (GetTop(Stack) == '(')
				{
					printf("缺少%c括号", ')');
					pop(Stack);
					flag = 0;
				}
				else if (GetTop(Stack) == '[')
				{
					printf("缺少%c括号", ']');
					pop(Stack);
					flag = 0;
				}
			}
			else if(IsEmpty(Stack)==1)
			{
				printf("缺少%c括号", '{');
				flag = 0;
			}
		}
		i++;
	}
	if (IsEmpty(Stack) == 1 && flag == 1)
		printf("匹配成功");
	else
	{
		LinkStNode* p = Stack->next;
		while (p != NULL)
		{
			if (p->data == '(')
				printf("缺少%c括号", ')');
			else if (p->data == '[')
				printf("缺少%c括号", ']');
			else if (p->data == '{')
				printf("缺少%c括号", '}');
			p = p->next;
		}
	}
	DeleteStack(Stack);
	return 0;
}
