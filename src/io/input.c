#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "input.h"

#define BUFFER_SIZE 100

int validateStudentNumber(int num)
{
    return num >= 20240000 && num <= 20249999;
}

int validateName(const char *name)
{
    // 本来想用正则直接匹配中文的，但是好像实现不太对，就改成直接判断长度了
    size_t len = strlen(name);
    if (len == 0 || len > 10)
    {
        return 0;
    }

    return 1;
}

// 为了windows的兼容性放弃使用regex.h库，改为直接逻辑实现
int validateClass(const char *class)
{
    // 检查长度是否为4
    if (strlen(class) != 4)
        return 0;

    // 检查前3位是否为"240"或"241"
    if (strncmp(class, "240", 3) == 0)
    {
        char c = class[3];
        // 第4位是否在'1'到'9'之间
        if (c >= '1' && c <= '9')
            return 1;
        else
            return 0;
    }
    else if (strncmp(class, "241", 3) == 0)
    {
        char c = class[3];
        // 第4位是否在'0'到'5'之间
        if (c >= '0' && c <= '5')
            return 1;
        else
            return 0;
    }
    else
        return 0;
}

int validateScore(int score)
{
    return score >= 0 && score <= 100;
}

int validateCredit(float credit)
{
    return credit >= 0.5 && credit <= 5.0;
}

int validateCourseNumber(int num)
{
    return num >= 1 && num <= 10;
}

void inputStudentNumber(int *num)
{
    char buffer[BUFFER_SIZE];
    do
    {
        printf("\033[1;33m请输入学号：\033[1;0m");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", num) != 1 || !validateStudentNumber(*num))
        {
            fprintf(stderr, "\033[1;31m输入错误，请输入一个有效的学号。\033[1;0m\n");
        }
        else
        {
            break;
        }
    } while (1);
}

void inputCourseNumber(int *num)
{
    char buffer[BUFFER_SIZE];
    do
    {
        printf("\033[1;33m请输入课程序号（1-10）：\033[1;0m");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", num) != 1 || !validateCourseNumber(*num))
        {
            fprintf(stderr, "\033[1;31m输入错误，请输入一个有效的课程序号。\033[1;0m\n");
        }
        else
        {
            break;
        }
    } while (1);
}

void inputName(char *name, size_t size)
{
    do
    {
        printf("\033[1;33m请输入姓名：\033[1;0m");
        if (fgets(name, size, stdin) == NULL)
        {
            fprintf(stderr, "\033[1;31m输入错误，请输入一个有效的姓名。\033[1;0m\n");
            continue;
        }
        // 移除额外读入的换行符
#ifdef _WIN32
        name[strcspn(name, "\r\n")] = '\0';
#else
        name[strcspn(name, "\n")] = '\0';
#endif
        if (!validateName(name))
        {
            fprintf(stderr, "\033[1;31m输入错误，请输入一个有效的姓名。\033[1;0m\n");
        }
        else
        {
            break;
        }
    } while (1);
}

void inputClass(char *class, size_t size)
{
    do
    {
        printf("\033[1;33m请输入班级：\033[1;0m");
        if (fgets(class, size, stdin) == NULL)
        {
            fprintf(stderr, "\033[1;31m输入错误，请输入一个有效的班级。\033[1;0m\n");
            continue;
        }
        // 移除额外读入的换行符
#ifdef _WIN32
        class[strcspn(class, "\r\n")] = '\0';
#else
        class[strcspn(class, "\n")] = '\0';
#endif
        if (!validateClass(class))
        {
            fprintf(stderr, "\033[1;31m输入错误，请输入一个有效的班级。\033[1;0m\n");
        }
        else
        {
            break;
        }
    } while (1);
}

void inputScore(int *score)
{
    char buffer[BUFFER_SIZE];
    do
    {
        printf("\033[1;33m请输入成绩：\033[1;0m");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", score) != 1 || !validateScore(*score))
        {
            fprintf(stderr, "\033[1;31m输入错误，请输入一个有效的成绩。\033[1;0m\n");
        }
        else
        {
            break;
        }
    } while (1);
}

void inputCredit(float *credit)
{
    char buffer[BUFFER_SIZE];
    do
    {
        printf("\033[1;33m请输入学分：\033[1;0m");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%f", credit) != 1 || !validateCredit(*credit))
        {
            fprintf(stderr, "\033[1;31m输入错误，请输入一个有效的学分。\033[1;0m\n");
        }
        else
        {
            break;
        }
    } while (1);
}

void inputStudent(Student *stu)
{
    inputStudentNumber(&stu->num);
    inputName(stu->name, sizeof(stu->name));
    inputClass(stu->class, sizeof(stu->class));

    for (int i = 0; i < COURSE_NUM; i++)
    {
        printf("\033[1;33m请输入第%d门课程的信息:\033[1;0m\n", i + 1);
        inputScore(&stu->score[i]);
        inputCredit(&stu->credit[i]);
    }
}