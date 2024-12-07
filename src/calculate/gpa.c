#include <stdio.h>
#include "gpa.h"
#include "input.h"

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

void findAndPrintGPA(Student *students, int count)
{
    if (count == 0)
    {
        printf("\033[1;31m请先添加学生！\033[1;0m\n");
        return;
    }

    int num;
    inputStudentNumber(&num);

    for (int i = 0; i < count; i++)
    {
        if (students[i].num == num)
        {
            calculateGPA(&students[i]);
            printf("\033[1;36m学生 %s 的 GPA 为 %.2f\033[1;0m\n", students[i].name, students[i].gpa);
            break;
        }
        else if (i == count - 1)
        {
            printf("\033[1;31m未找到学号为 %d 的学生。\033[1;0m\n", num);
        }
    }
}