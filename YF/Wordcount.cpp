#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"Huffman.h"

TreeNode* lxmroot = NULL;
TreeNode wordlist[2000];
int wordlist_length = 0;

void insert(struct TreeNode** root, char* word)
{
	//��������ж�, ��i��jָ�����������е�����֮��, 
	//�������һ��ѭ���غϲ�������Ϊ�ҵ��˵���, ��ʵ��һ�����ַ���.
	if (strcmp(word, "") == 0)
	{
		return;
	}

	struct TreeNode* hroot = *root;

	if (hroot == NULL)
	{
		//������ĸ��ڵ㻹��null, �������ڵ�
		hroot = (struct TreeNode*)malloc(sizeof(struct TreeNode));
		//���ڵ�ĳ�ʼ��, �����ĵ�һ������
		hroot->count = 1;
		strcpy(hroot->word, word);

		hroot->left = NULL;
		hroot->right = NULL;

		*root = hroot;
	}
	else
	{
		struct TreeNode* temp = hroot;
		//�������ڸ��ڵ�ʱ
		while (1)
		{
			//����Ҫ�洢�ĵ�����һ�����ʵ�λ��
			if (strcmp(temp->word, word) > 0)
			{
				if (temp->left == NULL)
					break;
				temp = temp->left;
			}
			else if (strcmp(temp->word, word) < 0)
			{
				if (temp->right == NULL)
					break;
				temp = temp->right;
			}
			else
			{
				//�������ҵ�����ͬ���ʵ����, �����½��ڵ�
				break;
			}

		}
		if (strcmp(temp->word, word) == 0)
		{
			//�������ҵ�����ͬ���ʵ����, �����½��ڵ�
			temp->count++;
		}
		else
		{
			//�½��ڵ㲢�洢���ո��ҵ��ĺ��ʵ�λ��
			TreeNode* newtree = (TreeNode*)malloc(sizeof(TreeNode));

			newtree->count = 1;
			strcpy(newtree->word, word);

			newtree->left = NULL;
			newtree->right = NULL;

			if (strcmp(temp->word, word) > 0)
			{
				temp->left = newtree;
			}
			else if (strcmp(temp->word, word) < 0)
			{
				temp->right = newtree;
			}
		}
	}
}

void print_word(struct TreeNode* root)//�ݹ��ӡ������Ϣ
{
	if (root == NULL)
		return;
	else
	{
		print_word(root->left);

		strcpy(wordlist[wordlist_length++].word, root->word);

		printf("%s��%d      ", root->word, root->count);

		if (wordlist_length % 5 == 0)
		{
			printf("\n");
		}

		print_word(root->right);

		return;
	}
}

TreeNode* wordFx(char filename[])
{
	FILE* fp = NULL;
	char buf[1024 * 100];
	char temp[1024];
	int i = 0;
	int j = 0;
	int n = 0;

	//���ļ�
	fp = fopen(filename, "r");

	//�ж��ļ��ǿ�
	if (!feof(fp))
	{
		fgets(buf, 1024, fp);
	}
	else
	{
		fclose(fp);
		exit(0);
	}

	//ѭ�����ļ�ȫ������
	while (fgets(temp, 1024, fp) != NULL)
	{
		strcat(buf, temp);
	}
	//�ر��ļ�, ��ʱ����ȫ�����ݶ���buf֮��
	fclose(fp);

	//printf("%s\n", buf);

	//ѭ������buf
	while (i < (strlen(buf) - 1))
	{
		//Ѱ�ҵ�һ����ĸi��λ��
		while (i < (strlen(buf) - 1) && !((buf[i] >= 'A' && buf[i] <= 'Z') || (buf[i] >= 'a' && buf[i] <= 'z')))
		{
			i++;
		}
		//��i��λ��Ѱ�ҵ��ʵĽ�βj��λ��
		j = i;
		while (i < (strlen(buf) - 1) && (buf[j] >= 'A' && buf[j] <= 'Z') || (buf[j] >= 'a' && buf[j] <= 'z'))
		{
			j++;
		}

		char str[50];

		//��i��j�������ĵ��ʸ�ֵ��str
		while (i < j)
		{
			str[n] = buf[i];
			i++;
			n++;
		}
		str[n] = '\0';
		n = 0;

		//��str��������
		insert(&lxmroot, str);
	}

	//��ӡ��Ƶ����
	print_word(lxmroot);
}