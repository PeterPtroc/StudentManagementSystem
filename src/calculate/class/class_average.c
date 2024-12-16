#include <stdio.h>
#include <string.h>
#include "class_average.h"

void calculateClassAverageScore(Student students[], int count)
{
    char className[20];
    int courseNumber;

    inputClass(className, sizeof(className));
    inputCourseNumber(&courseNumber);

    int totalScore = 0;
    int classCount = 0;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].class_name, className) == 0)
        {
            totalScore += students[i].score[courseNumber - 1];
            classCount++;
        }
    }
    if (classCount > 0)
    {
        float average = (float)totalScore / classCount;
        printf("\033[1;36m班级%s，课程[%s]的平均分是%.2f\033[1;0m\n", className, courseNames[(courseNumber - 1) * 3], average);
    }
    else
    {
        printf("\033[1;31m班级%s还未添加学生！\033[1;0m\n", className);
    }
}