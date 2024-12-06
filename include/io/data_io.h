#ifndef DATA_IO_H
#define DATA_IO_H

#include "student.h"

void importData(Student **students, int *count, const char *filename);
void exportData(Student *students, int count, const char *filename);

#endif