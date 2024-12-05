// class_highest.c
#include <stdio.h>
#include <string.h>
#include "class_highest.h"

void findClassHighestScore(Student students[], int count, const char *className, int courseNumber)
{
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
    printf("班级%s，课程%d的最高分是%d，学生有：\n", className, courseNumber, maxScore);
    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].class, className) == 0)
        {
            if (students[i].score[courseNumber - 1] == maxScore)
            {
                printf("学号：%d，姓名：%s，分数：%d\n", students[i].num, students[i].name, maxScore);
            }
        }
    }
}