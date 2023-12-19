#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Huffman.h"

List InitList(int high, int low, int weight)//����������
{
	List tmp = (List)malloc(sizeof(struct node));//���ڴ�������һ���������ռ䣬����ָ��tmpָ����Ƭ�ռ�
	tmp->high = high;
	tmp->low = low;
	tmp->weight = weight;
	tmp->next = NULL;
	return tmp;
}

void InsertList(List head, List new_node)//��Ƶ�ȴӵ͵��߲�������,new_node��Ҫ�������
{
	List p = head;
	while (p->next)//��weight�ӵ͵���,�ҵ���Ҫ�������λ��,��p->next=NULLʱ����ѭ��
	{
		if (new_node->weight < p->next->weight)
			break;
		p = p->next;
	}
	//����
	new_node->next = p->next;
	p->next = new_node;
}

List new_or_old(List head, List new_node)//�ж��¶�����ַ�֮ǰ�Ƿ���ֹ���������ֹ���ɾ��ԭ��㣬���̳�Ȩֵ
{
	List p = head;
	while (p->next)
	{
		if (p->next->high == new_node->high)
		{
			//�����ַ���ͬ,ȡ���ý�㲢ɾ��ԭ���
			if (p->next->low != -1 && new_node->low != -1 && p->next->low == new_node->low)
			{
				List have_found = InitList(p->next->high, p->next->low, p->next->weight + 1);//Ȩֵ��һ
				p->next = p->next->next;//ɾ��ԭ���
				return have_found;
			}
			//�Ǻ����ַ���ͬ
			if (p->next->low == -1 && new_node->low == -1)
			{
				List have_found = InitList(p->next->high, p->next->low, p->next->weight + 1);
				p->next = p->next->next;//ɾ��ԭ���
				return have_found;
			}
		}
		p = p->next;
	}
	return new_node;//�����в�����tmp���洢���ַ�
}

void DispList(List head, double sum, int flag)//�����ַ�����Ƶ�ʣ�flag�����Ƿ�������������Ϣ
{
	List p = head->next;
	if (flag)
	{
		printf("�ַ� Ƶ�� Ƶ��\n");
	}
	while (p)
	{
		if ((char)p->high == '\n')//������ַ��ǻ���
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
			if (p->high > 128)//����������ַ�
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

void DestroyList(List head)//��������
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