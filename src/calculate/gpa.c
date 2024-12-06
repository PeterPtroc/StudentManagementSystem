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
        if (score < 60)
            gradePoint = 0.0;
        else
            gradePoint = (score - 50) / 10.0;

        totalPoints += gradePoint * stu->credit[i];
        totalCredits += stu->credit[i];
    }
    stu->gpa = totalPoints / totalCredits;
}