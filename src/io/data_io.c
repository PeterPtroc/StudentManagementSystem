#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

#define INITIAL_CAPACITY 10

void importData_while_start(Student **students, int *count, const char *filename)
{
    importData(students, count, filename);
#ifdef _WIN32
    Sleep(1500);
#else
    sleep(2);
#endif
}

// 零信任读取文件
void importData(Student **students, int *count, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("\033[1;31m无法打开文件进行读取\033[1;0m");
        return;
    }

    // 处理旧数据逻辑
    if (*students != NULL)
    {
        free(*students);
        *students = NULL;
    }

    int capacity = INITIAL_CAPACITY;

    *count = 0;
    int lineNum = 0;
    Student tempStudent;
    char line[256];

    // 逐行验证
    while (fgets(line, sizeof(line), file))
    {
        lineNum++;
        int validRecord = 1;

        // 尝试解析，临时存储
        if (sscanf(line, "%d %s %s", &tempStudent.num, tempStudent.name, tempStudent.class) != 3)
        {
            printf("\033[1;33m警告: 第%d行基本信息格式不正确，已跳过\033[1;0m\n", lineNum);
            continue;
        }

        // 验证学号
        if (!validateStudentNumber(tempStudent.num))
        {
            printf("\033[1;33m警告: 第%d行学号 %d 无效，已跳过\033[1;0m\n", lineNum, tempStudent.num);
            continue;
        }

        // 验证姓名
        if (!validateName(tempStudent.name))
        {
            printf("\033[1;33m警告: 第%d行姓名 %s 无效，已跳过\033[1;0m\n", lineNum, tempStudent.name);
            continue;
        }

        // 验证班级
        if (!validateClass(tempStudent.class))
        {
            printf("\033[1;33m警告: 第%d行班级 %s 无效，已跳过\033[1;0m\n", lineNum, tempStudent.class);
            continue;
        }

        char *ptr = line;
        // 跳过已读取的学号、姓名和班级
        for (int i = 0; i < 3; i++)
        {
            ptr = strchr(ptr + 1, ' ');
            if (!ptr)
            {
                validRecord = 0;
                break;
            }
        }

        // 验证成绩和学分
        for (int i = 0; i < COURSE_NUM && validRecord; i++)
        {
            int score;
            float credit;

            if (sscanf(ptr, " %d %f", &score, &credit) != 2)
            {
                printf("\033[1;33m警告: 第%d行课程%d数据格式无效，已跳过\033[1;0m\n", lineNum, i + 1);
                validRecord = 0;
                break;
            }

            if (!validateScore(score))
            {
                printf("\033[1;33m警告: 第%d行课程%d成绩 %d 无效，已跳过\033[1;0m\n", lineNum, i + 1, score);
                validRecord = 0;
                break;
            }

            if (!validateCredit(credit))
            {
                printf("\033[1;33m警告: 第%d行课程%d学分 %.1f 无效，已跳过\033[1;0m\n", lineNum, i + 1, credit);
                validRecord = 0;
                break;
            }

            tempStudent.score[i] = score;
            tempStudent.credit[i] = credit;

            // 跳过到下一对成绩和学分
            ptr = strchr(ptr + 1, ' ');
            ptr = strchr(ptr + 1, ' ');
            if (!ptr && i < COURSE_NUM - 1)
            {
                printf("\033[1;33m警告: 第%d行数据不完整，已跳过\033[1;0m\n", lineNum);
                validRecord = 0;
                break;
            }
        }

        if (validRecord)
        {
            // 如果 *students 为 NULL，分配初始内存
            if (*students == NULL)
            {
                *students = (Student *)malloc(capacity * sizeof(Student));
                if (*students == NULL)
                {
                    perror("\033[1;31m内存分配失败\033[1;0m");
                    fclose(file);
                    return;
                }
            }

            (*students)[*count] = tempStudent;
            (*count)++;

            // 如果需要扩容
            if (*count >= capacity)
            {
                capacity *= 2;
                Student *temp = (Student *)realloc(*students, capacity * sizeof(Student));
                if (temp == NULL)
                {
                    perror("\033[1;31m内存重新分配失败\033[1;0m");
                    fclose(file);
                    return;
                }
                *students = temp;
            }
        }
    }

    fclose(file);
    printf("\033[1;32m从data/export.ini导入成功，共 %d 名学生。\033[1;0m\n", *count);
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