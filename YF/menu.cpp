#include<stdio.h>
#include"Huffman.h"

void menu(void)
{
	//输出菜单
	printf("\t\t\t\t\t********************************\n");

	printf("\t\t\t\t\t*       哈夫曼编解码器         *\n");

	printf("\t\t\t\t\t********************************\n");

	printf("\t\t\t\t\t* 1.输出字符频度               *\n");

	printf("\t\t\t\t\t* 2.输出哈夫曼编码表           *\n");

	printf("\t\t\t\t\t* 3.根据编码查找字符串         *\n");

	printf("\t\t\t\t\t* 4.统计英文单词词频           *\n");

	printf("\t\t\t\t\t* 5.解码                       *\n");

	printf("\t\t\t\t\t* 6.检验编解码正确性           *\n");

	printf("\t\t\t\t\t* 7.退出程序                   *\n");

	printf("\t\t\t\t\t********************************\n");

	printf("编码已完成，请输入你想要进行的操作（1-7）：");

}