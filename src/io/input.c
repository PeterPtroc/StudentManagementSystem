// input.c
#include <stdio.h>
#include "input.h"

void inputStudent(Student *stu)
{
    printf("请输入学号：");
    scanf("%d", &stu->num);
    printf("请输入姓名：");
    scanf("%s", stu->name);
    printf("请输入班级：");
    scanf("%s", stu->class);
    for (int i = 0; i < COURSE_NUM; i++)
    {
        printf("请输入第%d门课程的成绩：", i + 1);
        scanf("%d", &stu->score[i]);
        printf("请输入第%d门课程的学分：", i + 1);
        scanf("%f", &stu->credit[i]);
    }
}