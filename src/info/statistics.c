#include <stdio.h>
#include <stdlib.h>
#include "statistics.h"
#include "utils.h"

#define ITEMS_PER_PAGE 20

typedef struct Node
{
    Student student;
    struct Node *next;
} Node;

void displayPage(Node *range[], int counts[], const char *labels[], int page, int totalPages)
{
    clearScreen(); // 清屏
    printf("\n==== 统计结果 (第 %d/%d 页) ====\n\n", page + 1, totalPages);

    // 显示所有分数段的统计信息
    for (int i = 0; i < 5; i++)
    {
        printf("\033[1;33m分数段%s，共有%d人\033[1;0m\n", labels[i], counts[i]);
    }
    printf("\n");

    // 计算当前页应该显示的起始位置
    int startIdx = page * ITEMS_PER_PAGE;
    int currentItem = 0;

    // 遍历所有分数段
    for (int i = 0; i < 5; i++)
    {
        Node *p = range[i];
        while (p)
        {
            if (currentItem >= startIdx && currentItem < startIdx + ITEMS_PER_PAGE)
            {
                printf("\033[1;36m[%s] 学号：%d，姓名：%s\033[1;0m\n",
                       labels[i], p->student.num, p->student.name);
            }
            currentItem++;
            p = p->next;
        }
    }

    printf("\n--------------------------------\n");
    printf("按 'n' 查看下一页, 'p' 查看上一页, 'q' 退出\n");
}

void statisticsByCourse(Student students[], int count)
{
    int courseIndex;
    inputCourseNumber(&courseIndex);

    Node *range[5] = {NULL, NULL, NULL, NULL, NULL};
    int counts[5] = {0};

    // 这就是链表
    for (int i = 0; i < count; i++)
    {
        int score = students[i].score[courseIndex - 1];
        int index;
        if (score >= 90)
            index = 0;
        else if (score >= 80)
            index = 1;
        else if (score >= 70)
            index = 2;
        else if (score >= 60)
            index = 3;
        else
            index = 4;

        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->student = students[i];
        newNode->next = range[index];
        range[index] = newNode;
        counts[index]++;
    }

    // 计算总学生数和总页数
    int totalStudents = 0;
    for (int i = 0; i < 5; i++)
    {
        totalStudents += counts[i];
    }
    int totalPages = (totalStudents + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;

    const char *labels[] = {"90~100", "80~89", "70~79", "60~69", "0~59"};
    int currentPage = 0;
    char choice;

    fake_process("正在统计，请稍后", 1.3);

    do
    {
        displayPage(range, counts, labels, currentPage, totalPages);
        choice = getchar();
        clean_stdin(); // 清除输入缓冲

        switch (choice)
        {
        case '\n':
        case 'n': // 下一页
            if (currentPage < totalPages - 1)
                currentPage++;
            else
            {
                printf("已经是最后一页了(按回车继续)\n");
                getchar();
            }
            break;
        case 'p': // 上一页
            if (currentPage > 0)
                currentPage--;
            else
            {
                printf("已经是第一页了(按回车继续)\n");
                getchar();
            }
            break;
        }
    } while (choice != 'q');

    // 释放链表
    for (int i = 0; i < 5; i++)
    {
        Node *p = range[i];
        while (p)
        {
            Node *temp = p;
            p = p->next;
            free(temp);
        }
    }
}