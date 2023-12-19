#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Huffman.h"

HufTree b[750];//哈夫曼树的结点，按层次编号
int b_length = 0;

int main()
{
	//打开Source.txt文件
	FILE* p_src_txt;
	char filename[30];
	while (1)
	{
		printf("请输入文件名:");
		scanf("%s", &filename);
		p_src_txt =fopen(filename, "r");
		if (p_src_txt == NULL)
		{
			printf("%s打开失败，one more try!\n", filename);
			continue;
		}
		else
		{
			printf("%s打开成功！\n", filename);
			break;
		}
	}


	List head = InitList(-1, -1, 0); //创建链表头结点
	int ch;
	double sum_char = 0;//记录文件字符总数,汉字字符算一个字符
	while ((ch = fgetc(p_src_txt)) != EOF)//读取文件，fgetc函数会以一个字符为单位进行读取，并返回字符的ASCII码
	{
		List tmp = InitList(ch, -1, 1);//记录读入字符
		if (ch > 128)
		{
			tmp->low = fgetc(p_src_txt);//如果是中文字符则再读一个字符
		}
		InsertList(head, new_or_old(head, tmp));//将该字符按频度从低到高插入链表
		sum_char++;
	}

	HufTree Tree_head = CreaTree(head);//根据链表头结点建立森林
	BuildHufTree(Tree_head);//根据森林建立哈夫曼树
	//在这个循环结束后，Tree_head->next指向最后合并得到的哈夫曼树的根节点。

	Encoding(Tree_head);//编码

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
			printf("请输入你要进行匹配的字符串（长度小于50）:");
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
			RestoreFiles();//重构文件
			Decoding(b_length);//解码
			printf("解码已完成！\n");
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