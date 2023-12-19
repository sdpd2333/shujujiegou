#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Huffman.h"

HufTree b[750];//���������Ľ�㣬����α��
int b_length = 0;

int main()
{
	//��Source.txt�ļ�
	FILE* p_src_txt;
	char filename[30];
	while (1)
	{
		printf("�������ļ���:");
		scanf("%s", &filename);
		p_src_txt =fopen(filename, "r");
		if (p_src_txt == NULL)
		{
			printf("%s��ʧ�ܣ�one more try!\n", filename);
			continue;
		}
		else
		{
			printf("%s�򿪳ɹ���\n", filename);
			break;
		}
	}


	List head = InitList(-1, -1, 0); //��������ͷ���
	int ch;
	double sum_char = 0;//��¼�ļ��ַ�����,�����ַ���һ���ַ�
	while ((ch = fgetc(p_src_txt)) != EOF)//��ȡ�ļ���fgetc��������һ���ַ�Ϊ��λ���ж�ȡ���������ַ���ASCII��
	{
		List tmp = InitList(ch, -1, 1);//��¼�����ַ�
		if (ch > 128)
		{
			tmp->low = fgetc(p_src_txt);//����������ַ����ٶ�һ���ַ�
		}
		InsertList(head, new_or_old(head, tmp));//�����ַ���Ƶ�ȴӵ͵��߲�������
		sum_char++;
	}

	HufTree Tree_head = CreaTree(head);//��������ͷ��㽨��ɭ��
	BuildHufTree(Tree_head);//����ɭ�ֽ�����������
	//�����ѭ��������Tree_head->nextָ�����ϲ��õ��Ĺ��������ĸ��ڵ㡣

	Encoding(Tree_head);//����

	while (1)
	{
		int select;
		menu();
		scanf_s("%d", &select);
		switch (select)
		{
		case 1:
			DispList(head, sum_char,1);
			system("pause");
			system("cls");
			break;
		case 2:
			Huffencode_put(b);
			system("pause");
			system("cls");
			break;
		case 3:
			char str[50];
			printf("��������Ҫ����ƥ����ַ���������С��50��:");
			gets_s(str);
			gets_s(str);
	        Translate(str,1);
			Search(str);
			system("pause");
			system("cls");
			break;
		case 4:
			wordFx(filename);
			system("pause");
			system("cls");
			break;
		case 5:
			RestoreFiles();//�ع��ļ�
			Decoding(b_length);//����
			printf("��������ɣ�\n");
			//Check(filename);
			system("pause");
			system("cls");
			break;
		case 6:
			Check(filename);
			system("pause");
			system("cls");
			break;
		case 7:
			return 0;
		}
	}

	DestroyList(head);
	DestroyTree(Tree_head);
	return 0;
}