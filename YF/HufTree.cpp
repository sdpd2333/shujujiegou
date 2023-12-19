#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Huffman.h"

HufTree InitTree(int high, int low,int weight)//初始化二叉树结点信息，字符和其频度
{
	HufTree tmp = (HufTree)malloc(sizeof(struct node));
	tmp->high = high;
	tmp->low = low;
	tmp->weight = weight;
	strcpy(tmp->code,"\0");
	tmp->start = 0;
	tmp->lchild = NULL;
	tmp-> rchild = NULL;
	tmp->next = NULL;
	return tmp;
}

HufTree CreaTree(List head)//根据链表建森林，Tree本质上也是一个链表
{
	HufTree Tree_head = InitTree(head->high, head->low, 0);
	HufTree t = Tree_head;
	List p = head;
	while (p->next)
	{
		p = p->next;
		t->next = InitTree(p->high, p->low, p->weight);
		t = t->next;
		Tree_head->weight++;//记录树结点个数
	}
	return Tree_head;
}

void BuildHufTree(HufTree Tree_head)//建立哈夫曼树
{
	while (Tree_head->weight > 1)
	{
		HufTree t1 = Tree_head->next;
		Tree_head->next = Tree_head->next->next;
		HufTree t2 = Tree_head->next;
		Tree_head->next = Tree_head->next->next;
		HufTree t = InitTree(-1, -1, t1->weight + t2->weight);//合并两个结点
		t->lchild = t1;
		t->rchild = t2;
		InsertList(Tree_head, t);//合并之后再插回森林中
		Tree_head->weight--;//森林中树的个数减一
	}
	return;
}

void Encoding(HufTree Tree)//编码和转码解码同时进行，生成码流文件Encode.dat
{
	HufTree a[1500];
	int left = 0;
	int right = 1;

	a[0] = Tree->next;
	while (left < right)//层次遍历哈夫曼树,哈夫曼树的每一个飞叶子节点均有左右儿子
	{
		
		if (a[left]->lchild)//有左孩子
		{
			a[right] = a[left]->lchild;//把左结点编号，right记录节点的总数
			right++;
			strcpy(a[left]->lchild->code, a[left]->code);//将此节点的编号复制给下一个左节点
			a[left]->lchild->start = strlen(a[left]->code);//找出长度，也就是找出编码指针
			a[left]->lchild->code[a[left]->lchild->start] = '0';
			a[left]->lchild->code[a[left]->lchild->start+1] = '\0';
			a[left]->lchild->start++;
		}
		
		if (a[left]->rchild)//有右孩子
		{
			a[right] = a[left]->rchild;//把右节点编号，right记录节点的个数
			right++;
			strcpy(a[left]->rchild->code, a[left]->code);//将此节点的编号复制给下一个右节点
			a[left]->rchild->start = strlen(a[left]->code);//找出编码数组指针
			a[left]->rchild->code[a[left]->rchild->start] = '1';
			a[left]->rchild->code[a[left]->rchild->start+1] = '\0';
			a[left]->rchild->start + 1;
		}
		left++;
	}

	for (int i = 0; i < right; i++)//队列b存储字符编码信息
	{
		
		if(a[i]->high != -1)
		{
			b[b_length++] = a[i];
		}
	}
    coding(b_length);
	/*
编码，输出Encode.txt和Encode.dat
Encode.txt文件中只有字符‘0’和‘1’
Encode.dat文件是将8位的‘0’和‘1’以字符的形式输出
    */
	return;
}

void coding(int right)
/*
编码，输出Encode.txt和Encode.dat
Encode.txt文件中只有字符‘0’和‘1’
Encode.dat文件是将8位的‘0’和‘1’以字符的形式输出
*/
{
	FILE* p_src_txt = fopen("Source.txt", "r");//r 打开只读文件
	FILE* out = fopen("Encode.txt", "wb");//wb 只写或新建文件
	
	int ch;
	while ((ch = fgetc(p_src_txt)) != EOF)//fp是Source.txt的指针
	{
		List tmp = InitList(ch, -1, 1);
		if (ch > 128)
			tmp->low = fgetc(p_src_txt);
		for (int left = 0; left < right; left++)//遍历哈夫曼树，在哈夫曼树中寻找读入字符的编码，并输出到Encode.txt文件中
		{
			if (b[left]->high == tmp->high)
			{
				if (tmp->high > 128 && tmp->low == b[left]->low)
				{
					fprintf(out, "%s", b[left]->code);//fprintf函数可以将数据写入文件中
				}
				if (tmp->high <= 128)
				{
					fprintf(out, "%s", b[left]->code);//fprintf函数可以将数据写入文件中
				}
			}
		}
		free(tmp);
	}
	fclose(p_src_txt);
	fclose(out);


	out = fopen("Encode.txt", "r");
	int sum=0;
	while ((ch = fgetc(out)) != EOF)
	{
		sum++;
	}
	fclose(out);

	out = fopen("Encode.txt", "r");
	FILE* dat = fopen("Encode.dat", "wb");
	char code[8] = "\0";
	char inch = 0;
	while ((ch = (char)fgetc(out)) != EOF)
	{
		code[0] = ch;
		for (int i = 1; i <= 7; i++)
		{
			code[i] = (char)fgetc(out);//out是Encode.txt的指针
		}
		for (int i = 0; i < 8; i++)
		{
			inch <<= 1;//低位向高位进
			if (code[i] == '1')
			{
				inch |= 1;//位运算，让inch最后一位为1
			}
		}
		fputc(inch, dat);
		inch = 0;
	}
	fclose(out);
	fclose(dat);
}

void RestoreFiles()//二进制文件转换为txt文件
{
	FILE* En_dat = fopen("Encode.dat", "rb");//Encode.dat文件是将8位的‘0’和‘1’以字符的形式输出
	FILE* En_txt = fopen("Encode.txt", "w");//Encode.txt文件中只有字符‘0’和‘1’
	int p;
	char ch1 = 0;
	while (!feof(En_dat))//文件非空
	{
		fscanf(En_dat, "%c", &ch1);
		for (p = 7; p >= 0; p--)
		{
			if (ch1 & (1 << p))
			{
				fprintf(En_txt, "1");
			}
			else
			{
				fprintf(En_txt, "0");
			}
		}
	}
	fclose(En_dat);//En_dat是Encode.dat的指针
	fclose(En_txt);//En_txt是Encode.txt的指针
}

void Decoding(int front)//解码输出DecodeDoc.txt文件
{
	FILE* En_txt = fopen("Encode.txt", "r");
	FILE* En_dat = fopen("Decode.txt", "w");
	int ch;
	int str_index = 0;
	char str[30];
	while ((ch = fgetc(En_txt)) != EOF)
	{
		str[str_index++] = ch;
		str[str_index] = '\0';
		for (int left = 0; left < front; left++)
		{
			if (strcmp(b[left]->code, str) == 0)
			{
					fprintf(En_dat, "%c", b[left]->high);//高位字节
					if (b[left]->high > 128)
					{
						fprintf(En_dat, "%c", b[left]->low);//输出是中文
					}
				str_index = 0;
				break;
			}
		}
	}
	fclose(En_txt);
	fclose(En_dat);
	return;
}

void DestroyTree(HufTree Tree)//销毁二叉树
{
	if (Tree == NULL)
	{
		return;
	}
	else
	{
		DestroyTree(Tree->lchild);
		DestroyTree(Tree->rchild);
		free(Tree);
	}
}


void Check(char filename[])
{
	FILE* fp1, * fp2;
	char ch1, ch2;
	double sum = 0;//文件字符总数
	double k = 0;//两文件按顺序字符相同数
	fp1 = fopen(filename, "r");
	fp2 = fopen("Decode.txt", "r");
	if (fp2 == NULL)
	{
		printf("Decode.txt打开失败！");
		exit(1);
	}
	while (!feof(fp1))
	{
		ch1 = fgetc(fp1);
		ch2 = fgetc(fp2);
		sum++;
		if (ch1 == ch2)
		{
			k++;
		}
	}
	printf("经检验，解码正确率为%lf%%",100*(k-1)/(sum-1));
	return;
}

void Huffencode_put(HufTree *)
{
	for (int i = 0; i < b_length; i++)
	{
		if (b[i]->low != -1)//中文字符
			printf("字符：%c%c   哈夫曼编码：%s\n", b[i]->high, b[i]->low, b[i]->code);

		if (b[i]->low == -1)//非中文字符
		{
			if ((char)b[i]->high == '\n')//如果为换行字符
				printf("字符：\\n   哈夫曼编码：%s\n", b[i]->code);

			else 
				printf("字符：%c   哈夫曼编码：%s\n", b[i]->high,b[i]->code);
		}
	}
	return;
}