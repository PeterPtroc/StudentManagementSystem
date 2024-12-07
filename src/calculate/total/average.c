#include <stdio.h>
#include "average.h"

void calculateAverageScore(Student students[], int count, int courseNumber)
{
    if(count == 0)
    {
        printf("请先添加学生！\n");
        return;
    }
    int totalScore = 0;
    for (int i = 0; i < count; i++)
    {
        totalScore += students[i].score[courseNumber - 1];
    }
    float average = (float)totalScore / count;
    printf("课程%d的平均分是%.2f\n", courseNumber, average);
}