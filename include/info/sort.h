#ifndef SORT_H
#define SORT_H

#include "student.h"
void swap_in_total_sort(Student *a, Student *b);
int partition_in_total_sort(Student students[], int low, int high);
void quickSort_in_total_sort(Student students[], int low, int high);

void sortStudentsByTotalScore(Student students[], int count);

#endif