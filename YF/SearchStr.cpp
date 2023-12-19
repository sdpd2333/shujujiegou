#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Huffman.h"

char T[600] = "\0";//��ʼ��ģʽ��
int next[600];//����ģʽ��next����,ȫ�ֱ������ڴ���

void Translate(char str[],int flag)//��ģʽ��T��ת��Ϊ01��
{
	int ch;
	for (int i = 0; i < strlen(str); i++)
	{
		ch = str[i];//chΪstr[i]��ASCII��
		List tmp = InitList(ch, -1, 1);
		if (ch > 128)
		{
			i++;
			tmp->low = str[i];//����Ǻ������ٶ�һλ
		}
		for (int j = 0; j < b_length; j++)
		{
			if (b[j]->high == tmp->high)
			{
				if (tmp->high > 128 && tmp->low == b[j]->low)//����
				{
					strcat(T, b[j]->code);
					/*char *strcat(char *dest, const char *src) 
					�� src ��ָ����ַ���׷�ӵ� dest ��ָ����ַ����Ľ�β��*/
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
		printf("�����ַ���ת��Ϊ01��Ϊ��\n");
		puts(T);
		printf("\n");
	}
	Getnext();
	return;
}

void Getnext(void)//�õ�next����
{
	int j = -1;
	next[0] = j;
	for (int i = 1; i < strlen(T); i++)
	{
		while (j >= 0 && T[i] != T[j + 1])//ǰ��׺��ͬ��ǰ����
		{
			j = next[j];
		}
		if (T[i] == T[j + 1])//�ҵ�����ͬ��ǰ��׺
		{
			j++;
		}
		next[i] = j;//��ǰ׺���ȸ���next[i]
	}
}

int Kmp(char S[])//�����ַ����Ƿ��ڸö�����֣������򷵻�1��δ���ַ���0
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

void Search(char str[])//�ֶν���ƥ��
{
	FILE* fp = fopen("Source.txt", "r");

	char pra[1500];
	int flag1 = 0;
	int num = 0;//���ҵĶ�����
	while (fgets(pra, 1500, fp))
	{
		//����ȡ�Ķ���ת��Ϊ01��
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
			printf("��%d�γ��ֵĶ��䣺\n", num);
			printf("%s\n", pra);
		}
	}


	if (flag1 == 0)
	{
		printf("�ı���δ���ָ��ַ���\n");
	}
	else
	{
		printf("�ı��й���%d�����ָ��ַ���\n", num);
	}
	strcpy(T, "\0");
	fclose(fp);
	return;
}