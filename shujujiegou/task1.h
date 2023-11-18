#include <stdio.h>
#include <stdlib.h> // 基础头文件
#define TOTAL_CHARACTERS 65536 // Enough for GBK

typedef struct // 定义结构体
{
    int character;
    int frequency;
} CharFrequency;

typedef struct HuffmanTreeNode {
    CharFrequency data;
    struct HuffmanTreeNode *left, *right;
} HuffmanTreeNode;

typedef struct {
    HuffmanTreeNode* root;
    int size;
} HuffmanTree;

typedef struct {
    int character;
    char code[TOTAL_CHARACTERS];
} HuffmanCode;

int comparator(const void *p, const void *q) 
{
    return ((CharFrequency *)q)->frequency - ((CharFrequency *)p)->frequency;
}

HuffmanTreeNode* pop_min(HuffmanTree* tree) {
    HuffmanTreeNode* min_node = (tree->root)[0];  // tree->root 是一个 HuffmanTreeNode**

    // 把最后一个元素移动到根位置
    (tree->root)[0] = (tree->root)[--(tree->size)];

    // 从根开始向下调整堆
    int i = 0;
    while (i < tree->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        // 找到当前节点和它的子节点中最小的那个
        int smallest = i;
        if (left < tree->size && (tree->root)[left]->data.frequency < (tree->root)[smallest]->data.frequency) {
            smallest = left;
        }
        if (right < tree->size && (tree->root)[right]->data.frequency < (tree->root)[smallest]->data.frequency) {
            smallest = right;
        }

        // 如果当前节点不是最小的，那么就交换它和最小节点的位置，并继续向下调整
        if (smallest != i) {
            HuffmanTreeNode* temp = (tree->root)[i];
            (tree->root)[i] = (tree->root)[smallest];
            (tree->root)[smallest] = temp;
            i = smallest;
        } else {
            break;
        }
    }

    return min_node;
}

void push_node(HuffmanTree* tree, HuffmanTreeNode* node) {
    int i = tree->size++;

    // 把新节点放到数组的末尾
    tree->root[i] = node;

    // 从新节点开始向上调整堆
    while (i > 0) {
        int parent = (i - 1) / 2;

        // 如果新节点比它的父节点小，那么就交换它们的位置，然后继续向上调整
        if (tree->root[i]->data.frequency < tree->root[parent]->data.frequency) {
            HuffmanTreeNode* temp = tree->root[i];
            tree->root[i] = tree->root[parent];
            tree->root[parent] = temp;
            i = parent;
        } else {
            break;
        }
    }
}


HuffmanTreeNode* build_huffman_tree(CharFrequency* frequency, int size) {
    HuffmanTree tree;
    tree.root = malloc(sizeof(HuffmanTreeNode*) * size);
    tree.size = 0;

    for (int i = 0; i < size; ++i) {
        HuffmanTreeNode* node = malloc(sizeof(HuffmanTreeNode));
        node->data = frequency[i];
        node->left = NULL;
        node->right = NULL;
        push_node(&tree, node);
    }

    while (tree.size > 1) {
        HuffmanTreeNode* left = pop_min(&tree);
        HuffmanTreeNode* right = pop_min(&tree);

        HuffmanTreeNode* parent = malloc(sizeof(HuffmanTreeNode));
        parent->data.frequency = left->data.frequency + right->data.frequency;
        parent->left = left;
        parent->right = right;

        push_node(&tree, parent);
    }

    HuffmanTreeNode* root = pop_min(&tree);
    free(tree.root);
    return root;
}

void generate_huffman_codes(HuffmanTreeNode* node, char* code, int depth, HuffmanCode* huffman_codes) {
    if (node->left == NULL && node->right == NULL) {
        code[depth] = '\0';
        strcpy(huffman_codes[node->data.character].code, code);
        return;
    }

    if (node->left != NULL) {
        code[depth] = '0';
        generate_huffman_codes(node->left, code, depth + 1, huffman_codes);
    }

    if (node->right != NULL) {
        code[depth] = '1';
        generate_huffman_codes(node->right, code, depth + 1, huffman_codes);
    }
}

void count_frequency(char *input_filename, char *output_filename) 
{
    FILE *input_file, *output_file;
    int total = 0;
    CharFrequency frequency[TOTAL_CHARACTERS] = {0};

    // 初始化frequency数组
    for(int i = 0; i < TOTAL_CHARACTERS; i++) 
    {
        frequency[i].character = i;
    }

    HuffmanCode huffman_codes[TOTAL_CHARACTERS] = {0};
    for(int i = 0; i < TOTAL_CHARACTERS; i++) 
    {
        huffman_codes[i].character = i;
    }
  
    // 打开输入文件
    input_file = fopen(input_filename, "r");
    if (input_file == NULL) 
    {
        printf("无法打开输入文件\n");
        return;
    }

    int ch1, ch2;
    while ((ch1 = fgetc(input_file)) != EOF) {
        // 判断是否是GBK编码
        if((ch1 >= 0x81 && ch1 <= 0xFE)) 
        {
            // 读取下一个字符
            ch2 = fgetc(input_file);
            if(ch2 != EOF && (ch2 >= 0x40 && ch2 <= 0xFE))
            {
                // 计算整字符的编码
                int whole_ch = ch1 << 8 | ch2;
                // 更新频率
                frequency[whole_ch].frequency++;
                total += 2; 
            }
        } else {
            // 更新频率
            frequency[ch1].frequency++;
            total++;
        }
    }
    fclose(input_file);

    // 排序
    qsort(frequency, TOTAL_CHARACTERS, sizeof(CharFrequency), comparator);

    // 打开输出文件
    output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        printf("无法打开输出文件\n");
        return;
    }

    // 输出结果
    for (int i = 0; i < TOTAL_CHARACTERS; i++) {
        if (frequency[i].frequency > 0) {
            // 判断是否是GBK编码
            if(i >= 0x8140 && i <= 0xFEFE) 
            {
                fprintf(output_file, "字符 %c%c 的频度: %.4f 哈夫曼编码: %s\n", 
                        i>>8, i&0xFF, (float)frequency[i].frequency / total, huffman_codes[i].code);
            } 
            else 
            {
                fprintf(output_file, "字符 %c 的频度: %.4f 哈夫曼编码: %s\n", 
                        i, (float)frequency[i].frequency / total, huffman_codes[i].code);
            }
        }
    }

    fclose(output_file);
}
