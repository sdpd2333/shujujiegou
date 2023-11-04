#include <stdio.h>
#define TOTAL_CHARACTERS 128 // ASCII字符数量

void count_frequency(char *input_filename, char *output_filename) 
{
    FILE *input_file, *output_file;
    int character, total = 0;
    int frequency[TOTAL_CHARACTERS] = {0};

    input_file = fopen(input_filename, "r");
    if (input_file == NULL) 
    {
        printf("无法打开输入文件\n");
        return;
    }

    while ((character = fgetc(input_file)) != EOF) 
    {
        frequency[character]++;
        total++;
    }
    fclose(input_file);

    output_file = fopen(output_filename, "w");
    if (output_file == NULL) 
    {
        printf("无法打开输出文件\n");
        return;
    }

    for (int i = 0; i < TOTAL_CHARACTERS; i++) 
    {
        if (frequency[i] > 0) 
        {
            fprintf(output_file, "字符 %c 的频度: %.4f\n", i, (float)frequency[i] / total);
        }
    }

    fclose(output_file);
}