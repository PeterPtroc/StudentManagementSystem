#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "input.h"
#include "query.h"
#include "sort.h"
#include "statistics.h"
#include "gpa.h"
#include "gpa_ranking.h"
#include "highest.h"
#include "lowest.h"
#include "average.h"
#include "class_highest.h"
#include "class_lowest.h"
#include "class_average.h"
#include "data_io.h"

#define INITIAL_CAPACITY 1000

void waitForKeyPress()
{
    printf("按任意键返回...\n");
    while (getchar() != '\n')
        ;
    getchar(); // 等待任意键
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main()
{
    Student *students = NULL;
    int count = 0;
    char choice;
    do
    {
        clearScreen();
        printf("\n学生成绩管理系统\n");
        printf("1. 成绩录入\n");
        printf("2. 成绩查询\n");
        printf("3. 成绩排序\n");
        printf("4. 成绩统计\n");
        printf("5. 绩点计算\n");
        printf("6. 绩点排名\n");
        printf("7. 最高分查询\n");
        printf("8. 最低分查询\n");
        printf("9. 平均分计算\n");
        printf("A. 班级最高分查询\n");
        printf("B. 班级最低分查询\n");
        printf("C. 班级平均分计算\n");
        printf("D. 数据导入\n");
        printf("E. 数据导出\n");
        printf("0. 退出\n");
        printf("请输入您的选择：");

        // 读取用户输入
        choice = getchar();
        // // 清除缓冲区（fflush 无法在linux下使用）
        // while (getchar() != '\n')
        //     ;

        switch (choice)
        {
        case '1':
            inputStudent(&students[count]);
            count++;
            waitForKeyPress();
            break;
        case '2':
            queryStudent(students, count);
            waitForKeyPress();
            break;
        case '3':
            sortStudentsByTotalScore(students, count);
            waitForKeyPress();
            break;
        case '4':
        {
            int courseIndex;
            printf("请输入课程序号（1-10）：");
            scanf("%d", &courseIndex);
            statisticsByCourse(students, count, courseIndex - 1);
            waitForKeyPress();
            break;
        }
        case '5':
        {
            int num;
            printf("请输入要计算绩点的学生学号：");
            scanf("%d", &num);
            for (int i = 0; i < count; i++)
            {
                if (students[i].num == num)
                {
                    calculateGPA(&students[i]);
                    printf("学生 %s 的 GPA 为 %.2f\n", students[i].name, students[i].gpa);
                    break;
                }
            }
            waitForKeyPress();
            break;
        }
        case '6':
            sortStudentsByGPA(students, count);
            waitForKeyPress();
            break;
        case '7':
        {
            int courseNumber;
            printf("请输入课程序号（1-10）：");
            scanf("%d", &courseNumber);
            findHighestScore(students, count, (CourseNumber)courseNumber);
            waitForKeyPress();
            break;
        }
        case '8':
        {
            int courseNumber;
            printf("请输入课程序号（1-10）：");
            scanf("%d", &courseNumber);
            findLowestScore(students, count, (CourseNumber)courseNumber);
            waitForKeyPress();
            break;
        }
        case '9':
        {
            int courseNumber;
            printf("请输入课程序号（1-10）：");
            scanf("%d", &courseNumber);
            calculateAverageScore(students, count, (CourseNumber)courseNumber);
            waitForKeyPress();
            break;
        }
        case 'A':
        {
            char className[20];
            int courseNumber;
            printf("请输入班级：");
            scanf("%s", className);
            printf("请输入课程序号（1-10）：");
            scanf("%d", &courseNumber);
            findClassHighestScore(students, count, className, (CourseNumber)courseNumber);
            waitForKeyPress();
            break;
        }
        case 'B':
        {
            char className[20];
            int courseNumber;
            printf("请输入班级：");
            scanf("%s", className);
            printf("请输入课程序号（1-10）：");
            scanf("%d", &courseNumber);
            findClassLowestScore(students, count, className, (CourseNumber)courseNumber);
            waitForKeyPress();
            break;
        }
        case 'C':
        {
            char className[20];
            int courseNumber;
            printf("请输入班级：");
            scanf("%s", className);
            printf("请输入课程序号（1-10）：");
            scanf("%d", &courseNumber);
            calculateClassAverageScore(students, count, className, (CourseNumber)courseNumber);
            waitForKeyPress();
            break;
        }
        case 'D':
            importData(&students, &count, "data/export.ini");
            waitForKeyPress();
            break;
        case 'E':
            exportData(students, count, "data/export.ini");
            waitForKeyPress();
            break;
        case '0':
            printf("退出系统。\n");
            break;
        default:
            printf("无效的选择。\n");
            waitForKeyPress();
        }
    } while (choice != '0');

    // 释放动态分配的内存
    free(students);

    return 0;
}