#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#include "utils.h"
#include "gpa.h"

#define INITIAL_CAPACITY 1000

void waitForKeyPress()
{
    printf("按任意键返回...\n");
    clean_stdin();
    // getchar(); // 等待任意键
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
    Student *students = (Student *)malloc(INITIAL_CAPACITY * sizeof(Student));
    if (students == NULL)
    {
        fprintf(stderr, "内存分配失败\n");
        return 1;
    }
    int count = 0;
    char choice;
    do
    {
        clearScreen();
        printf("\n学生成绩管理系统\n");
        printf("*********************************\n");
        printf("*\t1. 成绩录入\t\t*\n");
        printf("*\t2. 成绩查询\t\t*\n");
        printf("*\t3. 成绩排序\t\t*\n");
        printf("*\t4. 成绩统计\t\t*\n");
        printf("*\t5. 绩点计算\t\t*\n");
        printf("*\t6. 绩点排名\t\t*\n");
        printf("*\t7. 最高分查询\t\t*\n");
        printf("*\t8. 最低分查询\t\t*\n");
        printf("*\t9. 平均分计算\t\t*\n");
        printf("*\tA. 班级最高分查询\t*\n");
        printf("*\tB. 班级最低分查询\t*\n");
        printf("*\tC. 班级平均分计算\t*\n");
        printf("*\tD. 数据导入\t\t*\n");
        printf("*\tE. 数据导出\t\t*\n");
        printf("*\t0. 退出\t\t\t*\n");
        printf("*********************************\n");
        printf("请输入您的选择：");

        // 读取用户输入
        choice = getchar();

        clean_stdin();

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
            int courseNumber;
            inputCourseNumber(&courseNumber);
            statisticsByCourse(students, count, (CourseNumber)courseNumber);
            waitForKeyPress();
            break;
        }
        case '5':
        {
            findAndPrintGPA(students, count);
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
            inputCourseNumber(&courseNumber);

            findHighestScore(students, count, (CourseNumber)courseNumber);
            waitForKeyPress();
            break;
        }
        case '8':
        {
            int courseNumber;
            inputCourseNumber(&courseNumber);

            findLowestScore(students, count, (CourseNumber)courseNumber);
            waitForKeyPress();
            break;
        }
        case '9':
        {
            int courseNumber;
            inputCourseNumber(&courseNumber);

            calculateAverageScore(students, count, (CourseNumber)courseNumber);
            waitForKeyPress();
            break;
        }
        case 'a':
        case 'A':
        {
            char className[20];
            int courseNumber;

            inputClass(className, sizeof(className));
            inputCourseNumber(&courseNumber);

            findClassHighestScore(students, count, className, (CourseNumber)courseNumber);
            waitForKeyPress();
            break;
        }
        case 'b':
        case 'B':
        {
            char className[20];
            int courseNumber;

            inputClass(className, sizeof(className));
            inputCourseNumber(&courseNumber);

            findClassLowestScore(students, count, className, (CourseNumber)courseNumber);
            waitForKeyPress();
            break;
        }
        case 'c':
        case 'C':
        {
            char className[20];
            int courseNumber;

            inputClass(className, sizeof(className));
            inputCourseNumber(&courseNumber);

            calculateClassAverageScore(students, count, className, (CourseNumber)courseNumber);
            waitForKeyPress();
            break;
        }
        case 'd':
        case 'D':
            importData(&students, &count, "data/export.ini");
            waitForKeyPress();
            break;
        case 'e':
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