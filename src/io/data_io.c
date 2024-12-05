#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "data_io.h"

void importData(Student students[], int *count, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("无法打开文件进行读取");
        return;
    }

    *count = 0;
    while (fscanf(file, "%d %s %s", &students[*count].num, students[*count].name, students[*count].class) != EOF)
    {
        for (int i = 0; i < COURSE_NUM; i++)
        {
            fscanf(file, "%d %f", &students[*count].score[i], &students[*count].credit[i]);
        }
        (*count)++;
    }

    fclose(file);
    printf("数据导入成功，共导入 %d 名学生的信息。\n", *count);
}

void exportData(Student students[], int count, const char *filename)
{
    // 检查并创建 data 目录
    struct stat st = {0};
    if (stat("data", &st) == -1)
    {
        if (mkdir("data", 0700) == -1)
        {
            perror("无法创建 data 目录");
            return;
        }
    }

    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("无法打开文件进行写入");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d %s %s", students[i].num, students[i].name, students[i].class);
        for (int j = 0; j < COURSE_NUM; j++)
        {
            fprintf(file, " %d %f", students[i].score[j], students[i].credit[j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("数据导出成功，共导出 %d 名学生的信息。\n", count);
}