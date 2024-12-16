#ifndef INPUT_H
#define INPUT_H

#include "student.h"
#include "course.h"

int validateStudentNumber(int num);
int validateName(const char *name);
int validateClass(const char *class_name);
int validateScore(int score);
int validateCredit(float credit);
int validateCourseNumber(int num);

void inputStudent(Student *stu);
void inputStudentNumber(int *num);
void inputName(char *name, size_t size);
void inputClass(char *class_name, size_t size);
void inputScore(int *score);
void inputCredit(float *credit);
void inputCourseNumber(int *courseNumber);

#endif