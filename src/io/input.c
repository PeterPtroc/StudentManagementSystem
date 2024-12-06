#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
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

int validateClass(const char *class)
{
    regex_t regex;
    int reti;

    // Compile regular expression
    reti = regcomp(&regex, "^240[1-9]|241[0-5]$", REG_EXTENDED);
    if (reti)
    {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    // Execute regular expression
    reti = regexec(&regex, class, 0, NULL, 0);
    regfree(&regex);

    return !reti;
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
        printf("请输入学号：");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", num) != 1 || !validateStudentNumber(*num))
        {
            fprintf(stderr, "输入错误，请输入一个有效的学号。\n");
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
        printf("请输入课程序号（1-10）：");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", num) != 1 || !validateCourseNumber(*num))
        {
            fprintf(stderr, "输入错误，请输入一个有效的课程序号。\n");
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
        printf("请输入姓名：");
        if (fgets(name, size, stdin) == NULL || !validateName(name))
        {
            fprintf(stderr, "输入错误，请输入一个有效的姓名。\n");
        }
        else
        {
            name[strcspn(name, "\n")] = '\0'; // 移除额外读入的换行符
            break;
        }
    } while (1);
}

void inputClass(char *class, size_t size)
{
    do
    {
        printf("请输入班级：");
        if (fgets(class, size, stdin) == NULL || !validateClass(class))
        {
            fprintf(stderr, "输入错误，请输入一个有效的班级。\n");
        }
        else
        {
            class[strcspn(class, "\n")] = '\0'; // 移除额外读入的换行符
            break;
        }
    } while (1);
}

void inputScore(int *score)
{
    char buffer[BUFFER_SIZE];
    do
    {
        printf("请输入成绩：");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", score) != 1 || !validateScore(*score))
        {
            fprintf(stderr, "输入错误，请输入一个有效的成绩。\n");
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
        printf("请输入学分：");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%f", credit) != 1 || !validateCredit(*credit))
        {
            fprintf(stderr, "输入错误，请输入一个有效的学分。\n");
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
        printf("请输入第%d门课程的信息:\n", i + 1);
        inputScore(&stu->score[i]);
        inputCredit(&stu->credit[i]);
    }
}