#ifndef PROJECT_INCLUDE_FILE_OPEN_READ_CHECK_H_
#define PROJECT_INCLUDE_FILE_OPEN_READ_CHECK_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int Number;
    int Value;
} test_struct;

void write_to_file(const char* filename_, test_struct* data);
void read_from_file(const char* filename_, test_struct* data);
int file_methods_check(const char* filename_);

#endif  //  PROJECT_INCLUDE_FILE_OPEN_READ_CHECK_H_
