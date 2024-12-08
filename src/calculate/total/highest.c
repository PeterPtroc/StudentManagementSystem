#include <stdio.h>
#include "highest.h"

void findHighestScore(Student students[], int count)
{
    if (count == 0)
    {
        printf("\033[1;31m请先添加学生！\033[1;0m\n");
        return;
    }

    int courseNumber;
    inputCourseNumber(&courseNumber);

    int maxScore = -1;
    for (int i = 0; i < count; i++)
    {
        if (students[i].score[courseNumber - 1] > maxScore)
        {
            maxScore = students[i].score[courseNumber - 1];
        }
    }
    printf("\033[1;36m课程%d的最高分是%d，学生有：\033[1;0m\n", courseNumber, maxScore);
    for (int i = 0; i < count; i++)
    {
        if (students[i].score[courseNumber - 1] == maxScore)
        {
            printf("\033[1;36m学号：%d，姓名：%s，分数：%d\033[1;0m\n", students[i].num, students[i].name, maxScore);
        }
    }
}