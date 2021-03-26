#include <stdio.h>
#include "matrix.h"

int main(void) {
    Matrix* a = create_matrix_from_file("file.dat");
    size_t*	 value = (size_t*)malloc(sizeof(size_t));
    get_cols(a, value);
    printf("%ld\n", *value);
    free(value);
    free_matrix(a);
    return 0;
}
