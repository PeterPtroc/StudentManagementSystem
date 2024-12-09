#include <stdio.h>
#include <string.h>
#include "class_lowest.h"

void findClassLowestScore(Student students[], int count)
{
    char className[20];
    int courseNumber;

    inputClass(className, sizeof(className));
    inputCourseNumber(&courseNumber);

    int minScore = 101;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].class, className) == 0)
        {
            if (students[i].score[courseNumber - 1] < minScore)
            {
                minScore = students[i].score[courseNumber - 1];
            }
        }
    }
    if (minScore == 101)
    {
        printf("\033[1;31m班级%s还没有添加学生！\033[1;0m\n", className);
        return;
    }
    printf("\033[1;36m班级%s，课程[%s]的最低分是%d，学生有：\033[1;0m\n", className, courseNames[(courseNumber - 1) * 3], minScore);
    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].class, className) == 0)
        {
            if (students[i].score[courseNumber - 1] == minScore)
            {
                printf("\033[1;36m学号：%d，姓名：%s，分数：%d\033[1;0m\n", students[i].num, students[i].name, minScore);
            }
        }
    }
}