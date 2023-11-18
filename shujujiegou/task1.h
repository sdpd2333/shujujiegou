#include <stdio.h>
#include <stdlib.h> // 基础头文件
#define TOTAL_CHARACTERS 65536 // Enough for GBK

typedef struct // 定义结构体
{
    int character;
    int frequency;
} CharFrequency;

int comparator(const void *p, const void *q) 
{
    return ((CharFrequency *)q)->frequency - ((CharFrequency *)p)->frequency;
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
                fprintf(output_file, "字符 %c%c 的频度: %.4f\n", 
                        i>>8, i&0xFF, (float)frequency[i].frequency / total);
            } 
            else 
            {
                fprintf(output_file, "字符 %c 的频度: %.4f\n", 
                        i, (float)frequency[i].frequency / total);
            }
        }
    }

    fclose(output_file);
}