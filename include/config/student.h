#ifndef STUDENT_H
#define STUDENT_H

#define COURSE_NUM 10

typedef struct
{
    int num;                  // 学号
    char name[50];            // 姓名
    char class[20];           // 班级
    int score[COURSE_NUM];    // 课程成绩，共有10门课程
    float credit[COURSE_NUM]; // 课程学分，对应10门课程
    float gpa;                // 绩点
} Student;

#endif