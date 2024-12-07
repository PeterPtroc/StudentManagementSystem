#include <stdio.h>
#include "sort.h"

void swap_in_total_sort(Student *a, Student *b)
{
    Student temp = *a;
    *a = *b;
    *b = temp;
}

int partition_in_total_sort(Student students[], int low, int high)
{
    int pivot = 0;
    for (int k = 0; k < COURSE_NUM; k++)
    {
        pivot += students[high].score[k];
    }
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        int totalScore = 0;
        for (int k = 0; k < COURSE_NUM; k++)
        {
            totalScore += students[j].score[k];
        }
        if (totalScore > pivot)
        {
            i++;
            swap_in_total_sort(&students[i], &students[j]);
        }
    }
    swap_in_total_sort(&students[i + 1], &students[high]);
    return i + 1;
}

void quickSort_in_total_sort(Student students[], int low, int high)
{
    if (low < high)
    {
        int pi = partition_in_total_sort(students, low, high);
        quickSort_in_total_sort(students, low, pi - 1);
        quickSort_in_total_sort(students, pi + 1, high);
    }
}

void sortStudentsByTotalScore(Student students[], int count)
{
    quickSort_in_total_sort(students, 0, count - 1);

    // 输出排序结果
    for (int i = 0; i < count; i++)
    {
        printf("\033[1;36m名次：%d，学号：%d，姓名：%s，总成绩：\033[1;0m", i + 1, students[i].num, students[i].name);
        int total = 0;
        for (int j = 0; j < COURSE_NUM; j++)
        {
            total += students[i].score[j];
        }
        printf("\033[1;36m%d\033[1;0m\n", total);
    }
}