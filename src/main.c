#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
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
#ifdef _WIN32
#include <windows.h>
#include "resource.h"
#else
#include <unistd.h>
#endif

#define INITIAL_CAPACITY 10 // 初始容量

void waitForKeyPress()
{
    printf("\033[1;36m按任意键返回...\033[1;0m\n");
    clean_stdin();
    // getchar(); // 等待任意键
}

void sub_menu_course_total(Student students[], int count);
void sub_menu_course_class(Student students[], int count);
void sub_menu_data_io(Student students[], int count);

int main()
{
#ifdef _WIN32
    // 在win平台下设置控制台输出编码为UTF-8
    SetConsoleOutputCP(CP_UTF8);
#endif
    fake_process("正在初始化系统...", 2);
    Student *students = (Student *)malloc(INITIAL_CAPACITY * sizeof(Student));
    if (students == NULL)
    {
        fprintf(stderr, "\033[1;31m内存分配失败\033[1;0m\n");
        return 1;
    }
    int count = 0;
    char choice;

    importData_while_start(&students, &count, "data/export.ini");

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
        printf("*\033[1;34m\t7. 课程分数数据查询\t\033[0m*\n");
        printf("*\033[1;33m\t8. 班级课程分数数据查询\t\033[0m*\n");
        printf("*\033[1;32m\t9. 数据导入导出\t\t\033[0m*\n");
        printf("*\033[1;31m\t0. 退出\t\t\t\033[0m*\n");
        printf("*********************************\n");
        printf("\033[1;33m请输入您的选择(一个字符)：\033[0m");

        // 读取用户输入
        choice = getchar();

        clean_stdin();

        switch (choice)
        {
        case '1':
        {            
            inputStudent(&students[count]);
            count++;
            waitForKeyPress();
            break;
        }
        case '2':
        {
            queryStudent(students, count);
            waitForKeyPress();
            break;
        }
        case '3':
        {
            sortStudentsByTotalScore(students, count);
            waitForKeyPress();
            break;
        }
        case '4':
        {
            statisticsByCourse(students, count);
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
            sub_menu_course_total(students, count);
            break;
        }
        case '8':
        {
            sub_menu_course_class(students, count);
            break;
        }
        case '9':
        {
            sub_menu_data_io(students, count);
            break;
        }
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

void sub_menu_course_total(Student students[], int count)
{
    char choice;
    do
    {
        clearScreen();
        printf("*********************************\n");
        printf("*\033[1;34m\t1. 最高分查询\t\t\033[0m*\n");
        printf("*\033[1;34m\t2. 最低分查询\t\t\033[0m*\n");
        printf("*\033[1;34m\t3. 平均分计算\t\t\033[0m*\n");
        printf("*\033[1;31m\t0. 返回\t\t\t\033[0m*\n");
        printf("*********************************\n");
        printf("\033[1;33m请输入您的选择(一个字符)：\033[0m");

        choice = getchar();
        clean_stdin();

        switch (choice)
        {
            case '1':
            {
                findHighestScore(students, count);
                waitForKeyPress();
                break;
            }
            case '2':
            {
                findLowestScore(students, count);
                waitForKeyPress();
                break;
            }
            case '3':
            {
                calculateAverageScore(students, count);
                waitForKeyPress();
                break;
            }
            case '0':
                break;
            default:
            {
            printf("\033[1;31m无效的选择。\033[1;0m\n");
            waitForKeyPress();
            }
        
        }
    }while (choice != '0');
    return;
}

void sub_menu_course_class(Student students[], int count)
{
    char choice;
    do
    {
        clearScreen();
        printf("*********************************\n");
        printf("*\033[1;33m\t1. 班级最高分查询\t\033[0m*\n");
        printf("*\033[1;33m\t2. 班级最低分查询\t\033[0m*\n");
        printf("*\033[1;33m\t3. 班级平均分计算\t\033[0m*\n");
        printf("*\033[1;31m\t0. 返回\t\t\t\033[0m*\n");
        printf("*********************************\n");
        printf("\033[1;33m请输入您的选择(一个字符)：\033[0m");

        choice = getchar();
        clean_stdin();

        switch (choice)
        {
            case '1':
            {
                findClassHighestScore(students, count);
                waitForKeyPress();
                break;
            }
            case '2':
            {
                findClassLowestScore(students, count);
                waitForKeyPress();
                break;
            }
            case '3':
            {
                calculateClassAverageScore(students, count);
                waitForKeyPress();
                break;
            }
            case '0':
                break;
            default:
            {
            printf("\033[1;31m无效的选择。\033[1;0m\n");
            waitForKeyPress();
            }
        }
    }while (choice != '0');
    return;
}


void sub_menu_data_io(Student *students, int count)
{
    char choice;
    do
    {
        clearScreen();
        printf("*********************************\n");
        printf("*\033[1;32m\t1. 数据导入\t\t\033[0m*\n");
        printf("*\033[1;32m\t2. 数据导出\t\t\033[0m*\n");
        printf("*\033[1;31m\t0. 返回\t\t\t\033[0m*\n");
        printf("*********************************\n");
        printf("\033[1;33m请输入您的选择(一个字符)：\033[0m");

        choice = getchar();
        clean_stdin();

        switch (choice)
        {
            case '1':
            {
                importData(&students, &count, "data/export.ini");
                waitForKeyPress();
                break;
            }
            case '2':
            {
                exportData(students, count, "data/export.ini");
                waitForKeyPress();
                break;
            }
            case '0':
                break;
            default:
            {
            printf("\033[1;31m无效的选择。\033[1;0m\n");
            waitForKeyPress();
            }
        }
    }while (choice != '0');
    return;
}