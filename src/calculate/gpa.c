// gpa.c
#include <stdio.h>
#include "gpa.h"

void calculateGPA(Student *stu)
{
    float totalPoints = 0;
    float totalCredits = 0;
    for (int i = 0; i < COURSE_NUM; i++)
    {
        float gradePoint;
        int score = stu->score[i];
        if (score >= 90)
            gradePoint = 4.0;
        else if (score >= 80)
            gradePoint = 3.0;
        else if (score >= 70)
            gradePoint = 2.0;
        else if (score >= 60)
            gradePoint = 1.0;
        else
            gradePoint = 0.0;

        totalPoints += gradePoint * stu->credit[i];
        totalCredits += stu->credit[i];
    }
    stu->gpa = totalPoints / totalCredits;
}