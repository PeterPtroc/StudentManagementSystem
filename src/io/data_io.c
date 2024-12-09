#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#define mkdir _mkdir
#else
#include <unistd.h>
#endif
#include "data_io.h"

#define INITIAL_CAPACITY 100

void importData_while_start(Student **students, int *count, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        // 文件打不开
        return;
    }

    int capacity = INITIAL_CAPACITY;
    *students = (Student *)malloc(capacity * sizeof(Student));
    if (*students == NULL)
    {
        // 内存分配失败
        fclose(file);
        return;
    }

    *count = 0;
    while (fscanf(file, "%d %s %s", &(*students)[*count].num, (*students)[*count].name, (*students)[*count].class) != EOF)
    {
        for (int i = 0; i < COURSE_NUM; i++)
        {
            fscanf(file, "%d %f", &(*students)[*count].score[i], &(*students)[*count].credit[i]);
        }
        (*count)++;

        // 如果超过当前容量，重新分配内存
        if (*count >= capacity)
        {
            capacity *= 2;
            *students = (Student *)realloc(*students, capacity * sizeof(Student));
            if (*students == NULL)
            {
                // 内存重新分配失败
                fclose(file);
                return;
            }
        }
    }

    fclose(file);
    printf("\033[1;36m从data/export.ini导入成功，共导入 %d 名学生的信息。\033[1;0m\n", *count);
#ifdef _WIN32
    Sleep(1500);
#else
    sleep(2);
#endif
}

void importData(Student **students, int *count, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("\033[1;31m无法打开文件进行读取\033[1;0m");
        return;
    }

    int capacity = INITIAL_CAPACITY;
    *students = (Student *)malloc(capacity * sizeof(Student));
    if (*students == NULL)
    {
        perror("\033[1;31m内存分配失败\033[1;0m");
        fclose(file);
        return;
    }

    *count = 0;
    while (fscanf(file, "%d %s %s", &(*students)[*count].num, (*students)[*count].name, (*students)[*count].class) != EOF)
    {
        for (int i = 0; i < COURSE_NUM; i++)
        {
            fscanf(file, "%d %f", &(*students)[*count].score[i], &(*students)[*count].credit[i]);
        }
        (*count)++;

        // 如果超过当前容量，重新分配内存
        if (*count >= capacity)
        {
            capacity *= 2;
            *students = (Student *)realloc(*students, capacity * sizeof(Student));
            if (*students == NULL)
            {
                perror("\033[1;31m内存重新分配失败\033[1;0m");
                fclose(file);
                return;
            }
        }
    }

    fclose(file);
    printf("\033[1;36m数据导入成功，共导入 %d 名学生的信息。\033[1;0m\n", *count);
}

void exportData(Student *students, int count, const char *filename)
{
    struct stat buffer;
    if (stat(filename, &buffer) == 0)
    {
        char choice;
        printf("\033[1;31m文件 %s 已存在。是否覆盖？(y/n): \033[1;0m", filename);
        scanf(" %c", &choice);
        if (choice != 'y' && choice != 'Y')
        {
            printf("\033[1;36m已取消导出。\033[1;0m\n");
            return;
        }
    }

    // 检查并创建data文件夹
    if (stat("data", &buffer) == -1)
    {
#ifdef _WIN32
        mkdir("data");
#else
        mkdir("data", 0700);
#endif
    }

    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("\033[1;31m无法打开文件进行写入\033[1;0m");
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
    printf("\033[1;36m数据导出成功，共导出 %d 名学生的信息。\033[1;0m\n", count);
}