#include "file_methods_check.h"

void write_to_file(const char* fprintf_check_file, test_struct* data) {
    FILE* test_file = fopen(fprintf_check_file, "w");

    if (test_file != NULL) {
        fprintf(test_file,
                "%-12d%-12d\n",
                data->number,
                data->value);
        fclose(test_file);
    }
}

void read_from_file(const char* fscanf_check_file, test_struct* data) {
    FILE* test_file = fopen(fscanf_check_file, "r");

    if (test_file != NULL) {
        fscanf(test_file,
               "%12d%12d\n",
               &data->number,
               &data->value);
        fclose(test_file);
    }
}

int file_methods_check(const char* file_to_check_file_methods) {
    test_struct  expected_data = {11, -14};
    write_to_file(file_to_check_file_methods, &expected_data);
    test_struct got_data;
    read_from_file(file_to_check_file_methods, &got_data);

    if (expected_data.number == got_data.number &&
        expected_data.value == got_data.value) {
        return 1;
    }
    return 0;
}
