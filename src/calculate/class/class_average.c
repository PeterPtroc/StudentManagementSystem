// class_average.c
#include <stdio.h>
#include <string.h>
#include "class_average.h"

void calculateClassAverageScore(Student students[], int count, const char *className, int courseNumber)
{
    int totalScore = 0;
    int classCount = 0;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].class, className) == 0)
        {
            totalScore += students[i].score[courseNumber - 1];
            classCount++;
        }
    }
    if (classCount > 0)
    {
        float average = (float)totalScore / classCount;
        printf("班级%s，课程%d的平均分是%.2f\n", className, courseNumber, average);
    }
    else
    {
        printf("未找到班级%s的学生。\n", className);
    }
}