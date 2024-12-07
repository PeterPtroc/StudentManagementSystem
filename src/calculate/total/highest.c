#include <stdio.h>
#include "highest.h"

void findHighestScore(Student students[], int count, CourseNumber course)
{
    if (count == 0)
    {
        printf("请先添加学生！\n");
        return;
    }
    int maxScore = -1;
    for (int i = 0; i < count; i++)
    {
        if (students[i].score[course - 1] > maxScore)
        {
            maxScore = students[i].score[course - 1];
        }
    }
    printf("课程%d的最高分是%d，学生有：\n", course, maxScore);
    for (int i = 0; i < count; i++)
    {
        if (students[i].score[course - 1] == maxScore)
        {
            printf("学号：%d，姓名：%s，分数：%d\n", students[i].num, students[i].name, maxScore);
        }
    }
}