#include <stdio.h>
#include "sort.h"

void sortStudentsByTotalScore(Student students[], int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            int totalScore1 = 0, totalScore2 = 0;
            for (int k = 0; k < COURSE_NUM; k++)
            {
                totalScore1 += students[j].score[k];
                totalScore2 += students[j + 1].score[k];
            }
            if (totalScore1 < totalScore2)
            {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    // 输出排序结果
    for (int i = 0; i < count; i++)
    {
        printf("名次：%d，学号：%d，姓名：%s，总成绩：", i+1, students[i].num, students[i].name);
        int total = 0;
        for (int j = 0; j < COURSE_NUM; j++)
        {
            total += students[i].score[j];
        }
        printf("%d\n", total);
    }
}