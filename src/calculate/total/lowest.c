#include <stdio.h>
#include "lowest.h"

void findLowestScore(Student students[], int count, int courseNumber)
{
    int minScore = 101;
    for (int i = 0; i < count; i++)
    {
        if (students[i].score[courseNumber - 1] < minScore)
        {
            minScore = students[i].score[courseNumber - 1];
        }
    }
    printf("课程%d的最低分是%d，学生有：\n", courseNumber, minScore);
    for (int i = 0; i < count; i++)
    {
        if (students[i].score[courseNumber - 1] == minScore)
        {
            printf("学号：%d，姓名：%s，分数：%d\n", students[i].num, students[i].name, minScore);
        }
    }
}