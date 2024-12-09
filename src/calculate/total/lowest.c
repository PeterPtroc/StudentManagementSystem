#include <stdio.h>
#include "lowest.h"

void findLowestScore(Student students[], int count)
{
    if (count == 0)
    {
        printf("\033[1;31m请先添加学生！\033[1;0m\n");
        return;
    }

    int courseNumber;
    inputCourseNumber(&courseNumber);

    int minScore = 101;
    for (int i = 0; i < count; i++)
    {
        if (students[i].score[courseNumber - 1] < minScore)
        {
            minScore = students[i].score[courseNumber - 1];
        }
    }
    printf("\033[1;36m课程[%s]的最低分是%d，学生有：\033[1;0m\n", courseNames[(courseNumber - 1) * 3], minScore);
    for (int i = 0; i < count; i++)
    {
        if (students[i].score[courseNumber - 1] == minScore)
        {
            printf("\033[1;36m学号：%d，姓名：%s，分数：%d\033[1;0m\n", students[i].num, students[i].name, minScore);
        }
    }
}