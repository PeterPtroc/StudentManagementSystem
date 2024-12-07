#include <stdio.h>
#include "gpa_ranking.h"
#include "gpa.h"

void swap_in_gpa_sort(Student *a, Student *b)
{
    Student temp = *a;
    *a = *b;
    *b = temp;
}

int partition_in_gpa_sort(Student students[], int low, int high)
{
    float pivot = students[high].gpa;
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (students[j].gpa > pivot)
        {
            i++;
            swap_in_gpa_sort(&students[i], &students[j]);
        }
    }
    swap_in_gpa_sort(&students[i + 1], &students[high]);
    return i + 1;
}

void quickSort_in_gpa_sort(Student students[], int low, int high)
{
    if (low < high)
    {
        int pi = partition_in_gpa_sort(students, low, high);
        quickSort_in_gpa_sort(students, low, pi - 1);
        quickSort_in_gpa_sort(students, pi + 1, high);
    }
}

void sortStudentsByGPA(Student students[], int count)
{
    // 计算每个学生的绩点
    for (int i = 0; i < count; i++)
    {
        calculateGPA(&students[i]);
    }

    // 按绩点降序排序
    quickSort_in_gpa_sort(students, 0, count - 1);

    printf("\033[1;36m绩点排名如下：\033[1;0m\n");
    for (int i = 0; i < count; i++)
    {
        printf("\033[1;36m名次：%d，学号：%d，姓名：%s，绩点：%.2f\033[1;0m\n", i + 1, students[i].num, students[i].name, students[i].gpa);
    }
}