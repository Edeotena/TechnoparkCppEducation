#include "file_methods_check.h"

void write_to_file(const char* filename_, test_struct* data) {
    FILE* ptr;
    ptr = fopen(filename_, "w");

    if (ptr != NULL) {
        fprintf(ptr, "%-12d%-12d\n",
                data->Number,
                data->Value);
        fclose(ptr);
    }
}

void read_from_file(const char* filename_, test_struct* data) {
    FILE* ptr;
    ptr = fopen(filename_, "r");

    if (ptr != NULL) {
        fscanf(ptr, "%12d%12d\n",
            &data->Number,
            &data->Value);
        fclose(ptr);
    }
}

int file_methods_check(const char* filename_) {
    test_struct  expected_data = {11, -14};
    write_to_file(filename_, &expected_data);
    test_struct got_data;
    read_from_file(filename_, &got_data);

    if (expected_data.Number == got_data.Number &&
        expected_data.Value == got_data.Value) {
        return 1;
    }
    return 0;
}
