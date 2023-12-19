#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Huffman.h"

char T[600] = "\0";//初始化模式串
int next[600];//定义模式串next数组,全局变量便于传递

void Translate(char str[],int flag)//将模式串T串转换为01流
{
	int ch;
	for (int i = 0; i < strlen(str); i++)
	{
		ch = str[i];//ch为str[i]的ASCII码
		List tmp = InitList(ch, -1, 1);
		if (ch > 128)
		{
			i++;
			tmp->low = str[i];//如果是汉字则再读一位
		}
		for (int j = 0; j < b_length; j++)
		{
			if (b[j]->high == tmp->high)
			{
				if (tmp->high > 128 && tmp->low == b[j]->low)//汉字
				{
					strcat(T, b[j]->code);
					/*char *strcat(char *dest, const char *src) 
					把 src 所指向的字符串追加到 dest 所指向的字符串的结尾。*/
				}
				if(tmp->high<=128)
				{
					strcat(T, b[j]->code);
				}
			}
		}
	}
	if (flag == 1)
	{
		printf("将该字符串转换为01流为：\n");
		puts(T);
		printf("\n");
	}
	Getnext();
	return;
}

void Getnext(void)//得到next数组
{
	int j = -1;
	next[0] = j;
	for (int i = 1; i < strlen(T); i++)
	{
		while (j >= 0 && T[i] != T[j + 1])//前后缀不同向前回溯
		{
			j = next[j];
		}
		if (T[i] == T[j + 1])//找到了相同的前后缀
		{
			j++;
		}
		next[i] = j;//将前缀长度赋给next[i]
	}
}

int Kmp(char S[])//查找字符串是否在该段落出现，出现则返回1，未出现返回0
{
	int S_length = strlen(S);
	int T_length = strlen(T);
	if (T_length == 0)
	{
		return 0;
	}
	int j = -1;
	for (int i = 0; i < S_length; i++)
	{
		while (j >= 0 && S[i] != T[j + 1])
		{
			j = next[j];
		}
		if (S[i] == T[j + 1])
		{
			j++;
		}
		if (j == T_length - 1)
		{
			return (i - T_length + 1);
		}
	}
	return -1;
}

void Search(char str[])//分段进行匹配
{
	FILE* fp = fopen("Source.txt", "r");

	char pra[1500];
	int flag1 = 0;
	int num = 0;//查找的段落数
	while (fgets(pra, 1500, fp))
	{
		//将读取的段落转化为01流
		char S[10000] = "\0";
		int ch;
		int pra_length = strlen(pra);
		for (int i = 0; i < pra_length; i++)
		{
			ch = pra[i];
			List tmp = InitList(ch, -1, 1);
			if (ch > 128)
			{
				i++;
				tmp->low = pra[i];
			}
			for (int j = 0; j < b_length; j++)
			{
				if (b[j]->high == tmp->high)
				{
					if (tmp->high > 128 && tmp->low == b[j]->low)
					{
						strcat(S, b[j]->code);
					}
					if (tmp->high <= 128)
					{
						strcat(S, b[j]->code);
					}
				}
			}
		}

		int flag = Kmp(S);
		if (flag > 0 && strstr(pra, str)!=NULL)
		{
			flag1 = 1;
			num++;
			printf("第%d次出现的段落：\n", num);
			printf("%s\n", pra);
		}
	}


	if (flag1 == 0)
	{
		printf("文本中未出现该字符串\n");
	}
	else
	{
		printf("文本中共有%d处出现该字符串\n", num);
	}
	strcpy(T, "\0");
	fclose(fp);
	return;
}