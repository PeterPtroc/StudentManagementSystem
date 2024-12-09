#include <stdio.h>
#include <string.h>
#include "class_highest.h"

void findClassHighestScore(Student students[], int count)
{
    char className[20];
    int courseNumber;

    inputClass(className, sizeof(className));
    inputCourseNumber(&courseNumber);

    int maxScore = -1;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].class, className) == 0)
        {
            if (students[i].score[courseNumber - 1] > maxScore)
            {
                maxScore = students[i].score[courseNumber - 1];
            }
        }
    }
    if (maxScore == -1)
    {
        printf("\033[1;31m班级%s还没有添加学生！\033[1;0m\n", className);
        return;
    }
    printf("\033[1;36m班级%s，课程[%s]的最高分是%d，学生有：\033[1;0m\n", className, courseNames[(courseNumber - 1) * 3], maxScore);
    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].class, className) == 0)
        {
            if (students[i].score[courseNumber - 1] == maxScore)
            {
                printf("\033[1;36m学号：%d，姓名：%s，分数：%d\033[1;0m\n", students[i].num, students[i].name, maxScore);
            }
        }
    }
}