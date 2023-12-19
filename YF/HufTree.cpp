#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Huffman.h"

HufTree InitTree(int high, int low,int weight)//��ʼ�������������Ϣ���ַ�����Ƶ��
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

HufTree CreaTree(List head)//��������ɭ�֣�Tree������Ҳ��һ������
{
	HufTree Tree_head = InitTree(head->high, head->low, 0);
	HufTree t = Tree_head;
	List p = head;
	while (p->next)
	{
		p = p->next;
		t->next = InitTree(p->high, p->low, p->weight);
		t = t->next;
		Tree_head->weight++;//��¼��������
	}
	return Tree_head;
}

void BuildHufTree(HufTree Tree_head)//������������
{
	while (Tree_head->weight > 1)
	{
		HufTree t1 = Tree_head->next;
		Tree_head->next = Tree_head->next->next;
		HufTree t2 = Tree_head->next;
		Tree_head->next = Tree_head->next->next;
		HufTree t = InitTree(-1, -1, t1->weight + t2->weight);//�ϲ��������
		t->lchild = t1;
		t->rchild = t2;
		InsertList(Tree_head, t);//�ϲ�֮���ٲ��ɭ����
		Tree_head->weight--;//ɭ�������ĸ�����һ
	}
	return;
}

void Encoding(HufTree Tree)//�����ת�����ͬʱ���У����������ļ�Encode.dat
{
	HufTree a[1500];
	int left = 0;
	int right = 1;

	a[0] = Tree->next;
	while (left < right)//��α�����������,����������ÿһ����Ҷ�ӽڵ�������Ҷ���
	{
		
		if (a[left]->lchild)//������
		{
			a[right] = a[left]->lchild;//�������ţ�right��¼�ڵ������
			right++;
			strcpy(a[left]->lchild->code, a[left]->code);//���˽ڵ�ı�Ÿ��Ƹ���һ����ڵ�
			a[left]->lchild->start = strlen(a[left]->code);//�ҳ����ȣ�Ҳ�����ҳ�����ָ��
			a[left]->lchild->code[a[left]->lchild->start] = '0';
			a[left]->lchild->code[a[left]->lchild->start+1] = '\0';
			a[left]->lchild->start++;
		}
		
		if (a[left]->rchild)//���Һ���
		{
			a[right] = a[left]->rchild;//���ҽڵ��ţ�right��¼�ڵ�ĸ���
			right++;
			strcpy(a[left]->rchild->code, a[left]->code);//���˽ڵ�ı�Ÿ��Ƹ���һ���ҽڵ�
			a[left]->rchild->start = strlen(a[left]->code);//�ҳ���������ָ��
			a[left]->rchild->code[a[left]->rchild->start] = '1';
			a[left]->rchild->code[a[left]->rchild->start+1] = '\0';
			a[left]->rchild->start + 1;
		}
		left++;
	}

	for (int i = 0; i < right; i++)//����b�洢�ַ�������Ϣ
	{
		
		if(a[i]->high != -1)
		{
			b[b_length++] = a[i];
		}
	}
    coding(b_length);
	/*
���룬���Encode.txt��Encode.dat
Encode.txt�ļ���ֻ���ַ���0���͡�1��
Encode.dat�ļ��ǽ�8λ�ġ�0���͡�1�����ַ�����ʽ���
    */
	return;
}

void coding(int right)
/*
���룬���Encode.txt��Encode.dat
Encode.txt�ļ���ֻ���ַ���0���͡�1��
Encode.dat�ļ��ǽ�8λ�ġ�0���͡�1�����ַ�����ʽ���
*/
{
	FILE* p_src_txt = fopen("Source.txt", "r");//r ��ֻ���ļ�
	FILE* out = fopen("Encode.txt", "wb");//wb ֻд���½��ļ�
	
	int ch;
	while ((ch = fgetc(p_src_txt)) != EOF)//fp��Source.txt��ָ��
	{
		List tmp = InitList(ch, -1, 1);
		if (ch > 128)
			tmp->low = fgetc(p_src_txt);
		for (int left = 0; left < right; left++)//���������������ڹ���������Ѱ�Ҷ����ַ��ı��룬�������Encode.txt�ļ���
		{
			if (b[left]->high == tmp->high)
			{
				if (tmp->high > 128 && tmp->low == b[left]->low)
				{
					fprintf(out, "%s", b[left]->code);//fprintf�������Խ�����д���ļ���
				}
				if (tmp->high <= 128)
				{
					fprintf(out, "%s", b[left]->code);//fprintf�������Խ�����д���ļ���
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
			code[i] = (char)fgetc(out);//out��Encode.txt��ָ��
		}
		for (int i = 0; i < 8; i++)
		{
			inch <<= 1;//��λ���λ��
			if (code[i] == '1')
			{
				inch |= 1;//λ���㣬��inch���һλΪ1
			}
		}
		fputc(inch, dat);
		inch = 0;
	}
	fclose(out);
	fclose(dat);
}

void RestoreFiles()//�������ļ�ת��Ϊtxt�ļ�
{
	FILE* En_dat = fopen("Encode.dat", "rb");//Encode.dat�ļ��ǽ�8λ�ġ�0���͡�1�����ַ�����ʽ���
	FILE* En_txt = fopen("Encode.txt", "w");//Encode.txt�ļ���ֻ���ַ���0���͡�1��
	int p;
	char ch1 = 0;
	while (!feof(En_dat))//�ļ��ǿ�
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
	fclose(En_dat);//En_dat��Encode.dat��ָ��
	fclose(En_txt);//En_txt��Encode.txt��ָ��
}

void Decoding(int front)//�������DecodeDoc.txt�ļ�
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
					fprintf(En_dat, "%c", b[left]->high);//��λ�ֽ�
					if (b[left]->high > 128)
					{
						fprintf(En_dat, "%c", b[left]->low);//���������
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

void DestroyTree(HufTree Tree)//���ٶ�����
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
	double sum = 0;//�ļ��ַ�����
	double k = 0;//���ļ���˳���ַ���ͬ��
	fp1 = fopen(filename, "r");
	fp2 = fopen("Decode.txt", "r");
	if (fp2 == NULL)
	{
		printf("Decode.txt��ʧ�ܣ�");
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
	printf("�����飬������ȷ��Ϊ%lf%%",100*(k-1)/(sum-1));
	return;
}

void Huffencode_put(HufTree *)
{
	for (int i = 0; i < b_length; i++)
	{
		if (b[i]->low != -1)//�����ַ�
			printf("�ַ���%c%c   ���������룺%s\n", b[i]->high, b[i]->low, b[i]->code);

		if (b[i]->low == -1)//�������ַ�
		{
			if ((char)b[i]->high == '\n')//���Ϊ�����ַ�
				printf("�ַ���\\n   ���������룺%s\n", b[i]->code);

			else 
				printf("�ַ���%c   ���������룺%s\n", b[i]->high,b[i]->code);
		}
	}
	return;
}