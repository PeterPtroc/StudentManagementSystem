#include <stdio.h>
#include "query.h"
#include "input.h"

void queryStudent(Student students[], int count)
{
    int num;
    inputStudentNumber(&num);
    for (int i = 0; i < count; i++)
    {
        if (students[i].num == num)
        {
            printf("\033[1;36m姓名：%s\033[1;0m\n", students[i].name);
            for (int j = 0; j < COURSE_NUM; j++)
            {
                printf("\033[1;36m课程%d成绩：%d\033[1;0m\n", j + 1, students[i].score[j]);
            }
            return;
        }
    }
    printf("\033[1;31m未找到该学生。\033[1;0m\n");
}