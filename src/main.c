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
#ifdef _WIN32
#include <windows.h>
#include "resource.h"
#else
#include <unistd.h>
#endif

#define INITIAL_CAPACITY 10

void waitForKeyPress()
{
    printf("\033[1;36m按任意键返回...\033[1;0m\n");
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
#ifdef _WIN32
    // 在win平台下设置控制台输出编码为UTF-8
    SetConsoleOutputCP(CP_UTF8);
#endif

    Student *students = (Student *)malloc(INITIAL_CAPACITY * sizeof(Student));
    if (students == NULL)
    {
        fprintf(stderr, "\033[1;31m内存分配失败\033[1;0m\n");
        return 1;
    }
    int count = 0;
    char choice;
    do
    {
        clearScreen();
        printf("\n\033[1;36m欢\033[1;35m迎\033[1;34m使\033[1;33m用\033[1;32m学\033[1;31m生\033[1;36m成\033[1;35m绩\033[1;34m管\033[1;33m理\033[1;32m系\033[1;31m统\033[1;0m\n");
        printf("*********************************\n");
        printf("*\033[1;36m\t1. 成绩录入\t\t\033[0m*\n");
        printf("*\033[1;36m\t2. 成绩查询\t\t\033[0m*\n");
        printf("*\033[1;36m\t3. 成绩排序\t\t\033[0m*\n");
        printf("*\033[1;36m\t4. 成绩统计\t\t\033[0m*\n");
        printf("*\033[1;35m\t5. 绩点计算\t\t\033[0m*\n");
        printf("*\033[1;35m\t6. 绩点排名\t\t\033[0m*\n");
        printf("*\033[1;34m\t7. 最高分查询\t\t\033[0m*\n");
        printf("*\033[1;34m\t8. 最低分查询\t\t\033[0m*\n");
        printf("*\033[1;34m\t9. 平均分计算\t\t\033[0m*\n");
        printf("*\033[1;33m\tA. 班级最高分查询\t\033[0m*\n");
        printf("*\033[1;33m\tB. 班级最低分查询\t\033[0m*\n");
        printf("*\033[1;33m\tC. 班级平均分计算\t\033[0m*\n");
        printf("*\033[1;32m\tD. 数据导入\t\t\033[0m*\n");
        printf("*\033[1;32m\tE. 数据导出\t\t\033[0m*\n");
        printf("*\033[1;31m\t0. 退出\t\t\t\033[0m*\n");
        printf("*********************************\n");
        printf("\033[1;33m请输入您的选择(一个字符)：\033[0m");

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
            printf("\033[1;31m正在退出系统\033[1;0m\n");
#ifdef _WIN32
            Sleep(2000);
#else
            sleep(2);
#endif
            break;
        default:
            printf("\033[1;31m无效的选择。\033[1;0m\n");
            waitForKeyPress();
        }
    } while (choice != '0');

    // 释放动态分配的内存
    free(students);

    return 0;
}