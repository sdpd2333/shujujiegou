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
	//特殊情况判断, 当i和j指针找完了所有的文章之后, 
	//会在最后一次循环重合并且误认为找到了单词, 其实是一个空字符串.
	if (strcmp(word, "") == 0)
	{
		return;
	}

	struct TreeNode* hroot = *root;

	if (hroot == NULL)
	{
		//如果树的根节点还是null, 则建立根节点
		hroot = (struct TreeNode*)malloc(sizeof(struct TreeNode));
		//根节点的初始化, 遇到的第一个单词
		hroot->count = 1;
		strcpy(hroot->word, word);

		hroot->left = NULL;
		hroot->right = NULL;

		*root = hroot;
	}
	else
	{
		struct TreeNode* temp = hroot;
		//当树存在根节点时
		while (1)
		{
			//给将要存储的单词找一个合适的位置
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
				//这是在找到了相同单词的情况, 无需新建节点
				break;
			}

		}
		if (strcmp(temp->word, word) == 0)
		{
			//这是在找到了相同单词的情况, 无需新建节点
			temp->count++;
		}
		else
		{
			//新建节点并存储到刚刚找到的合适的位置
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

void print_word(struct TreeNode* root)//递归打印单词信息
{
	if (root == NULL)
		return;
	else
	{
		print_word(root->left);

		strcpy(wordlist[wordlist_length++].word, root->word);

		printf("%s：%d      ", root->word, root->count);

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

	//打开文件
	fp = fopen(filename, "r");

	//判断文件非空
	if (!feof(fp))
	{
		fgets(buf, 1024, fp);
	}
	else
	{
		fclose(fp);
		exit(0);
	}

	//循环将文件全部读入
	while (fgets(temp, 1024, fp) != NULL)
	{
		strcat(buf, temp);
	}
	//关闭文件, 此时文章全部内容都在buf之中
	fclose(fp);

	//printf("%s\n", buf);

	//循环处理buf
	while (i < (strlen(buf) - 1))
	{
		//寻找第一个字母i的位置
		while (i < (strlen(buf) - 1) && !((buf[i] >= 'A' && buf[i] <= 'Z') || (buf[i] >= 'a' && buf[i] <= 'z')))
		{
			i++;
		}
		//从i的位置寻找单词的结尾j的位置
		j = i;
		while (i < (strlen(buf) - 1) && (buf[j] >= 'A' && buf[j] <= 'Z') || (buf[j] >= 'a' && buf[j] <= 'z'))
		{
			j++;
		}

		char str[50];

		//将i到j所包含的单词赋值给str
		while (i < j)
		{
			str[n] = buf[i];
			i++;
			n++;
		}
		str[n] = '\0';
		n = 0;

		//将str存入树中
		insert(&lxmroot, str);
	}

	//打印词频分析
	print_word(lxmroot);
}