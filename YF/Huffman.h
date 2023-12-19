#pragma once 


typedef struct node* List;
typedef struct node* HufTree;

 struct node
{
	 int high;//��һλ���洢�Ǻ����ַ����ֵ�һλ
	 int low;//�ڶ�λ,�Ǻ����ַ���Ϊ-1����洢���ֵڶ�λ
	 int weight;//Ȩ�أ����ַ����ִ���
	 List next;//ָ����һ��Ԫ�ص�ָ��
	 double p;//�ַ�����Ƶ��,���� weight/sum
	 char code[100];//�ַ����룬code�ǽ����ַ�'0'���ַ�'1'��ɵ��ַ���
	 int start;//strat����code�����һλ���±�
	 HufTree lchild;//����
	 HufTree rchild;//�Һ���
	 
};

 //��Ƶͳ��
 typedef struct TreeNode
 {
	 int count;
	 char word[25];
	 struct TreeNode* left;
	 struct TreeNode* right;
 }TreeNode;

 //ȫ�ֱ���
 extern HufTree b[750];
 extern int b_length;
 extern char T[600];
 extern int next[600];
 extern TreeNode wordlist[2000];
 extern int wordlist_length;

//�˵�ѡ��
void menu(void);//�˵�ѡ��

//������
List InitList(int high, int low, int weight);//��ʼ����������Ϣ,�ַ�������ִ���
void InsertList(List head, List tmp);//����С������
List new_or_old(List head, List tmp);//�ж��¶�����ַ�֮ǰ�Ƿ���ֹ����Ծ�������λ��
void DispList(List head,double sum,int flag);//�����ַ�����Ƶ�ʣ�flag�����Ƿ�������������Ϣ
void DestroyList(List head);//��������

//���������ͱ���뺯��
HufTree InitTree(int high, int low, double p);//��ʼ�������������Ϣ���ַ�����Ƶ��
HufTree CreaTree(List head);//���������һ������������
void BuildHufTree(HufTree Tree);//������������
void coding(int right);//����
void Encoding(HufTree Tree);//�����ת��ͬʱ���У����������ļ�Encode.dat
void DispTreePre(HufTree Tree,int flag);//��Ҷ�ӽ��浽�����У�flag�����Ƿ����statistic�ļ�
void RestoreFiles();//�������ļ�ת��Ϊtxt�ļ�
void Decoding(int front);//�������DecodeDoc.txt�ļ�
void DestroyTree(HufTree Tree);//���ٶ�����
void Check(char filename[]);//����������ȷ��

//�ַ���ƥ�亯��
void Translate(char str[],int flag);//�ַ���ƥ��
int Kmp(char pra[]);//�����ַ����Ƿ��ڸö�����֣������򷵻�1��δ���ַ���0
void Getnext(void);//�õ�ģʽ��next����
void Search(char str[]);//�ֶν���ƥ��
int Min_in_three(int a, int b, int c);//����������С

//����Ƶ��ͳ�ƺ���
void insert(struct TreeNode** root, char* word);
void print_word(struct TreeNode* root);
TreeNode* wordFx(char filename[]);
void Huffencode_put(HufTree *);