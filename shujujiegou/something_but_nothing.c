//首先是包含必要的库、结构体的定义和函数声明
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 256

typedef struct Node {
    unsigned char character; 
    int frequency;  
    char* code;  
    struct Node *left, *right;
} Node;

typedef struct Node* PriorityQueue[MAX_CHAR];  

int total_chars = 0;  

void enqueue(PriorityQueue, Node*);
Node* dequeue(PriorityQueue);
Node* newNode(unsigned char, int);
int compareNodes(const void*, const void*);
void buildHuffmanTree(PriorityQueue);
void generateHuffmanCodes(Node*, char*);
void charFrequency(char*, int*);

//接下来是main函数的部分，并且实现子函数charFrequency用于统计字符的频度
int main() {
    char source_file[20] = "SourceDoc.txt";
    int char_freq[MAX_CHAR] = {0};
    PriorityQueue pq;
    
    charFrequency(source_file, char_freq);
   
    for(int i=0; i<MAX_CHAR; i++) {
        if(char_freq[i] > 0) {
            Node *node = newNode((unsigned char)i, char_freq[i]);
            enqueue(pq, node);
        }
    }

    buildHuffmanTree(pq);
    char code[MAX_CHAR];
    memset(code, 0, sizeof(code));
    generateHuffmanCodes(pq[0], code);  

    return 0;
}

void charFrequency(char* file_name, int* freq) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Could not open file %s", file_name);
        return;
    }
    unsigned char ch;
    while ((ch = fgetc(file)) != EOF) {
        freq[ch]++;
        total_chars++;
    }
    fclose(file);
}
//👆这部分代码主要是打开源文档，读取每个字符，并更新对应字符的频度。然后，我们为频度大于零的每个字符创建一个新节点并将其添加到优先队列中

//接下来我们实现新节点创建newNode和优先队列操作函数enqueue 和 dequeue
Node* newNode(unsigned char character, int frequency) {
    Node* temp = (Node*) malloc(sizeof(Node));
    temp->left = temp->right = NULL;
    temp->character = character;
    temp->frequency = frequency;
    temp->code = (char*) malloc(MAX_CHAR*sizeof(char));
    return temp;
}

void enqueue(PriorityQueue pq, Node* node) {
    pq[total_chars] = node;
    total_chars++;
    qsort((void*)pq, total_chars, sizeof(Node*), compareNodes);
}

Node* dequeue(PriorityQueue pq) {
    Node* temp = pq[0];
    for(int i=0; i<total_chars-1; i++) {
        pq[i] = pq[i+1];
    }
    total_chars--;
    return temp;
}
//这里，newNode用于创建新的哈夫曼树节点，enqueue将新节点添加到优先队列中并排序，dequeue则从队列中弹出频率最小的节点


//接下来我们实现用于比较节点频率的函数compareNodes，建立哈夫曼树的函数buildHuffmanTree和生成哈夫曼编码的函数generateHuffmanCodes
int compareNodes(const void* p, const void* q) {
    int l = ((Node*)p)->frequency;
    int r = ((Node*)q)->frequency;
    if(l != r) {
        return (l - r);
    }
    else {
        unsigned char leftCh = ((Node*)p)->character;
        unsigned char rightCh = ((Node*)q)->character;
        return (leftCh - rightCh);
    }
}

void buildHuffmanTree(PriorityQueue pq) {
    while(total_chars > 1) {
        Node *left = dequeue(pq);
        Node *right = dequeue(pq);
        Node *temp = newNode('\0', left->frequency + right->frequency);
        temp->left = left;
        temp->right = right;
        enqueue(pq, temp);
    }
}

void generateHuffmanCodes(Node* root, char* code) {
    if(root->left) {
        strcat(code, "0");
        generateHuffmanCodes(root->left, code);
        code[strlen(code)-1] = '\0';  
    }
    
    if(root->right) {
        strcat(code, "1");
        generateHuffmanCodes(root->right, code);
        code[strlen(code)-1] = '\0';  
    }
    
    if(!(root->left) && !(root->right)) {
        printf("%s: %d (%.4f), Huffman code: %s\n", root->character, root->frequency, 
               (float)root->frequency/total_chars, code);
    }
}
//在这部分代码中，compareNodes函数用于比较两个节点的频率，buildHuffmanTree函数用于构建哈夫曼树，而generateHuffmanCodes则用于生成并打印字符及其对应的哈夫曼编码

//根据您的要求，我们应该将以上信息写入一个文件Statistic.txt中，而不是直接打印到控制台。为实现这一点，可以使用fprintf()函数代替最后一部分中的printf()函数
    FILE* statisticFile = fopen("Statistic.txt", "w");
    if(statisticFile == NULL) {
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }
    
    // 以下代码位于generateHuffmanCodes函数中
    if(!(root->left) && !(root->right)) {
        fprintf(statisticFile, "%s: %d (%.4f), Huffman code: %s\n", root->character, root->frequency, 
               (float)root->frequency/total_chars, code);
    }

    fclose(statisticFile);
