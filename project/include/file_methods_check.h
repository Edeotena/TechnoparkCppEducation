#ifndef PROJECT_INCLUDE_FILE_METHODS_CHECK_H_
#define PROJECT_INCLUDE_FILE_METHODS_CHECK_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"

void write_to_file(const char* fprintf_check_file, test_struct* data);
void read_from_file(const char* fscanf_check_file, test_struct* data);
int file_methods_check(const char* file_to_check_file_methods);

#endif  //  PROJECT_INCLUDE_FILE_METHODS_CHECK_H_