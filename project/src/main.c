#include <stdio.h>
#include "matrix.h"

// just tests

int main(void) {
    Matrix* a = create_matrix_from_file("file.dat");
    size_t* val = (size_t*)malloc(sizeof(size_t));
    double* value = (double*)malloc(sizeof(double));
    get_elem(a, 0, 0, value);
    get_cols(a, val);
    get_rows(a, val);
    set_elem(a, 0, 0, 2);
    det(a, value);
    Matrix* b = transp(a);
    Matrix* c = sum(a, b);
    free(c);
    Matrix* d = sub(a, b);
    free(d);
    Matrix* e = mul(a, b);
    free(e);
    b = inv(a);
    free(val);
    free(value);
    free(b);
    free_matrix(a);
    return 0;
}
