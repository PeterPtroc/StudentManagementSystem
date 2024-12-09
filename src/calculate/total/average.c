#include <stdio.h>
#include "average.h"

void calculateAverageScore(Student students[], int count)
{
    if (count == 0)
    {
        printf("\033[1;31m请先添加学生！\033[1;0m\n");
        return;
    }

    int courseNumber;
    inputCourseNumber(&courseNumber);

    int totalScore = 0;
    for (int i = 0; i < count; i++)
    {
        totalScore += students[i].score[courseNumber - 1];
    }
    float average = (float)totalScore / count;
    printf("\033[1;36m课程[%s]的平均分是%.2f\033[1;0m\n", courseNames[(courseNumber - 1) * 3], average);
}