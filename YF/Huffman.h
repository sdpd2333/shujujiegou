#pragma once 


typedef struct node* List;
typedef struct node* HufTree;

 struct node
{
	 int high;//第一位，存储非汉字字符或汉字第一位
	 int low;//第二位,非汉字字符赋为-1，或存储汉字第二位
	 int weight;//权重，即字符出现次数
	 List next;//指向下一个元素的指针
	 double p;//字符出现频率,等于 weight/sum
	 char code[100];//字符编码，code是仅由字符'0'和字符'1'组成的字符串
	 int start;//strat代表code的最后一位的下标
	 HufTree lchild;//左孩子
	 HufTree rchild;//右孩子
	 
};

 //词频统计
 typedef struct TreeNode
 {
	 int count;
	 char word[25];
	 struct TreeNode* left;
	 struct TreeNode* right;
 }TreeNode;

 //全局变量
 extern HufTree b[750];
 extern int b_length;
 extern char T[600];
 extern int next[600];
 extern TreeNode wordlist[2000];
 extern int wordlist_length;

//菜单选项
void menu(void);//菜单选项

//链表函数
List InitList(int high, int low, int weight);//初始化链表结点信息,字符和其出现次数
void InsertList(List head, List tmp);//按大小插入结点
List new_or_old(List head, List tmp);//判断新读入的字符之前是否出现过，以决定插入位置
void DispList(List head,double sum,int flag);//存入字符出现频率，flag决定是否遍历输出链表信息
void DestroyList(List head);//销毁链表

//哈夫曼树和编解码函数
HufTree InitTree(int high, int low, double p);//初始化二叉树结点信息，字符和其频度
HufTree CreaTree(List head);//根据链表第一步建立二叉树
void BuildHufTree(HufTree Tree);//建立哈夫曼树
void coding(int right);//编码
void Encoding(HufTree Tree);//编码和转码同时进行，生成码流文件Encode.dat
void DispTreePre(HufTree Tree,int flag);//将叶子结点存到队列中，flag控制是否输出statistic文件
void RestoreFiles();//二进制文件转换为txt文件
void Decoding(int front);//解码输出DecodeDoc.txt文件
void DestroyTree(HufTree Tree);//销毁二叉树
void Check(char filename[]);//检验编解码正确性

//字符串匹配函数
void Translate(char str[],int flag);//字符串匹配
int Kmp(char pra[]);//查找字符串是否在该段落出现，出现则返回1，未出现返回0
void Getnext(void);//得到模式串next数组
void Search(char str[]);//分段进行匹配
int Min_in_three(int a, int b, int c);//三个数求最小

//单词频度统计函数
void insert(struct TreeNode** root, char* word);
void print_word(struct TreeNode* root);
TreeNode* wordFx(char filename[]);
void Huffencode_put(HufTree *);