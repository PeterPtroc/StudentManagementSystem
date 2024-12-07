#include <stdio.h>
#include "gpa_ranking.h"
#include "gpa.h"

void sortStudentsByGPA(Student students[], int count)
{
    // 计算每个学生的绩点
    for (int i = 0; i < count; i++)
    {
        calculateGPA(&students[i]);
    }

    // 按绩点降序排序
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (students[j].gpa < students[j + 1].gpa)
            {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("绩点排名如下：\n");
    for (int i = 0; i < count; i++)
    {
        printf("名次：%d，学号：%d，姓名：%s，绩点：%.2f\n", i + 1, students[i].num, students[i].name, students[i].gpa);
    }
}