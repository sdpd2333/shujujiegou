#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Huffman.h"

List InitList(int high, int low, int weight)//创建链表结点
{
	List tmp = (List)malloc(sizeof(struct node));//在内存中申请一个结点所需空间，并用指针tmp指向这片空间
	tmp->high = high;
	tmp->low = low;
	tmp->weight = weight;
	tmp->next = NULL;
	return tmp;
}

void InsertList(List head, List new_node)//按频度从低到高插入链表,new_node是要被插入的
{
	List p = head;
	while (p->next)//按weight从低到高,找到所要插入结点的位置,当p->next=NULL时跳出循环
	{
		if (new_node->weight < p->next->weight)
			break;
		p = p->next;
	}
	//插入
	new_node->next = p->next;
	p->next = new_node;
}

List new_or_old(List head, List new_node)//判断新读入的字符之前是否出现过，如果出现过就删除原结点，并继承权值
{
	List p = head;
	while (p->next)
	{
		if (p->next->high == new_node->high)
		{
			//汉字字符相同,取出该结点并删除原结点
			if (p->next->low != -1 && new_node->low != -1 && p->next->low == new_node->low)
			{
				List have_found = InitList(p->next->high, p->next->low, p->next->weight + 1);//权值加一
				p->next = p->next->next;//删除原结点
				return have_found;
			}
			//非汉字字符相同
			if (p->next->low == -1 && new_node->low == -1)
			{
				List have_found = InitList(p->next->high, p->next->low, p->next->weight + 1);
				p->next = p->next->next;//删除原结点
				return have_found;
			}
		}
		p = p->next;
	}
	return new_node;//链表中不含有tmp所存储的字符
}

void DispList(List head, double sum, int flag)//存入字符出现频率，flag决定是否遍历输出链表信息
{
	List p = head->next;
	if (flag)
	{
		printf("字符 频数 频率\n");
	}
	while (p)
	{
		if ((char)p->high == '\n')//如果该字符是换行
		{
			p->p = (double)p->weight / sum;
			if (flag)
			{
				printf("\\n  %d  %lf\n", p->weight, p->p);
			}
			p = p->next;
			continue;
		}
		if (flag)
		{
			putchar(p->high);
			if (p->high > 128)//如果是中文字符
			{
				putchar(p->low);
			}
		}
		p->p = (double)p->weight / sum;
		if (flag)
		{
			printf("   %d  %lf\n", p->weight, p->p);
		}
		p = p->next;
	}
}

void DestroyList(List head)//销毁链表
{
	List p = head;
	while (head->next != NULL)
	{
		p = head->next;
		head->next = head->next->next;
		free(p);
	}
	free(head);
	return;
}