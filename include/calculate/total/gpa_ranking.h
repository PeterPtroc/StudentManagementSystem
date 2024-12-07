#ifndef GPA_RANKING_H
#define GPA_RANKING_H

#include "student.h"
void swap_in_gpa_sort(Student *a, Student *b);
int partition_in_gpa_sort(Student students[], int low, int high);
void quickSort_in_gpa_sort(Student students[], int low, int high);
void sortStudentsByGPA(Student students[], int count);

#endif