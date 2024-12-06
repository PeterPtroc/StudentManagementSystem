#include <stdio.h>
#include <string.h>
#include "input.h"

# define BUFFER_SIZE 100

void inputStudent(Student *stu)
{
    char buffer[BUFFER_SIZE];

    printf("请输入学号：");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", &stu->num) != 1) {
        fprintf(stderr, "输入错误，请输入一个有效的学号。\n");
        return;
    }

    printf("请输入姓名：");
    if (fgets(stu->name, sizeof(stu->name), stdin) == NULL) {
        fprintf(stderr, "输入错误，请输入一个有效的姓名。\n");
        return;
    }
    stu->name[strcspn(stu->name, "\n")] = '\0'; // 移除额外读入的换行符

    printf("请输入班级：");
    if (fgets(stu->class, sizeof(stu->class), stdin) == NULL) {
        fprintf(stderr, "输入错误，请输入一个有效的班级。\n");
        return;
    }
    stu->class[strcspn(stu->class, "\n")] = '\0'; // 移除额外读入的换行符

    for (int i = 0; i < COURSE_NUM; i++)
    {
        printf("请输入第%d门课程的成绩：", i + 1);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", &stu->score[i]) != 1) {
            fprintf(stderr, "输入错误，请输入一个有效的成绩。\n");
            return;
        }

        printf("请输入第%d门课程的学分：", i + 1);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%f", &stu->credit[i]) != 1) {
            fprintf(stderr, "输入错误，请输入一个有效的学分。\n");
            return;
        }
    }
}