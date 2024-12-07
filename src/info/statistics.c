#include <stdio.h>
#include <stdlib.h>
#include "statistics.h"

typedef struct Node
{
    Student student;
    struct Node *next;
} Node;

void statisticsByCourse(Student students[], int count)
{
    int courseIndex;
    inputCourseNumber(&courseIndex);

    Node *range[5] = {NULL, NULL, NULL, NULL, NULL};
    int counts[5] = {0};
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
    const char *labels[] = {"90~100", "80~89", "70~79", "60~69", "0~59"};
    for (int i = 0; i < 5; i++)
    {
        printf("\033[1;36m分数段%s，共有%d人：\033[1;0m\n", labels[i], counts[i]);
        Node *p = range[i];
        while (p)
        {
            printf("\033[1;36m学号：%d，姓名：%s，成绩：%d\033[1;0m\n", p->student.num, p->student.name, p->student.score[courseIndex - 1]);
            p = p->next;
        }
    }
    // 最后输出总结
    for (int i = 0; i < 5; i++)
    {
        printf("\033[1;33m分数段%s，共有%d人：\033[1;0m\n", labels[i], counts[i]);
    }

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