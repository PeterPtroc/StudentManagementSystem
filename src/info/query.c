#include <stdio.h>
#include "query.h"

void queryStudent(Student students[], int count)
{
    int num;
    printf("请输入要查询的学生学号：");
    scanf("%d", &num);
    for (int i = 0; i < count; i++)
    {
        if (students[i].num == num)
        {
            printf("姓名：%s\n", students[i].name);
            for (int j = 0; j < COURSE_NUM; j++)
            {
                printf("课程%d成绩：%d\n", j + 1, students[i].score[j]);
            }
            return;
        }
    }
    printf("未找到该学生。\n");
}