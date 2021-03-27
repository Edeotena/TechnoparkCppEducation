#include "matrix.h"

// Init/release operations

Matrix* create_matrix(size_t rows, size_t cols) {
    void* test_ptr_m = malloc(sizeof(struct Matrix));
    if (test_ptr_m == NULL) {
        return NULL;
    }

    Matrix* matrix = (Matrix*)test_ptr_m;
    matrix->rows = rows;
    matrix->cols = cols;

    void** test_ptr_1 = (void**)malloc(rows * sizeof(double));
    if (test_ptr_1 == NULL) {
        free(test_ptr_m);
        return NULL;
    }

    matrix->matrix_content = (double**)test_ptr_1;

    for (size_t i = 0; i < rows; ++i) {
        void* test_ptr_2 = malloc(cols * sizeof(double));
        if (test_ptr_2 == NULL) {
            return NULL;
        }
        matrix->matrix_content[i] = (double*)test_ptr_2;
    }

    return matrix;
}

Matrix* create_matrix_from_file(const char* path_file) {
    FILE* file_to_read = fopen(path_file, "r");

    void* test_ptr_m = malloc(sizeof(struct Matrix));
    if (test_ptr_m == NULL) {
        fclose(file_to_read);
        return NULL;
    }

    Matrix* matrix = (Matrix*)test_ptr_m;

    if (file_to_read == NULL) {
        free(test_ptr_m);
        return NULL;
    }

    if (fscanf(file_to_read, "%zu %zu", &matrix->rows, &matrix->cols) != 2) {
        fclose(file_to_read);
        free(test_ptr_m);
        return NULL;
    }

    void** test_ptr_1 = (void**)malloc(matrix->rows * sizeof(double));
    if (test_ptr_1 == NULL) {
        fclose(file_to_read);
        free(test_ptr_m);
        return NULL;
    }

    matrix->matrix_content = (double**)test_ptr_1;

    for (size_t i = 0; i < matrix->rows; ++i) {
        void* test_ptr_2 = malloc(matrix->cols * sizeof(double));
        if (test_ptr_2 == NULL) {
            fclose(file_to_read);
            return NULL;
        }
        matrix->matrix_content[i] = (double*)test_ptr_2;
        for (size_t j = 0; j <matrix->cols; ++j) {
            if (fscanf(file_to_read, "%lf", &matrix->matrix_content[i][j]) != 1) {
                fclose(file_to_read);
                return NULL;
            }
        }
    }
    if (fclose(file_to_read) != 0) {
        return NULL;
    }

    return matrix;
}


int free_matrix(Matrix* matrix) {
    for (size_t i = 0; i < matrix->rows; ++i) {
        free(matrix->matrix_content[i]);
    }

    free(matrix->matrix_content);

    free(matrix);

    return 0;
}

// Basic operations

int get_rows(const Matrix* matrix, size_t* rows) {
    *rows = matrix->rows;

    return 0;
}

int get_cols(const Matrix* matrix, size_t* cols) {
    *cols = matrix->cols;

    return 0;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    *val = matrix->matrix_content[row][col];

    return 0;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    matrix->matrix_content[row][col] = val;

    return 0;
}

// Math operations

Matrix* mul_scalar(const Matrix* matrix, double val) {
    Matrix* new_matrix = create_matrix(matrix->rows, matrix->cols);

    for (size_t i = 0; i < new_matrix->rows; ++i) {
        for (size_t j = 0; j < new_matrix->cols; ++j) {
            new_matrix->matrix_content[i][j] = matrix->matrix_content[i][j] * val;
        }
    }

    return new_matrix;
}

Matrix* transp(const Matrix* matrix) {
    Matrix* new_matrix = create_matrix(matrix->cols, matrix->rows);
    for (size_t i = 0; i < matrix->cols; ++i) {
        for (size_t j = 0; j < matrix->rows; ++j) {
            new_matrix->matrix_content[i][j] = matrix->matrix_content[j][i];
        }
    }

    return new_matrix;
}

Matrix* sum(const Matrix* l, const Matrix* r) {
    Matrix* new_matrix = create_matrix(l->rows, l->cols);

    for (size_t i = 0; i < l->rows; ++i) {
        for (size_t j = 0; j < l->cols; ++j) {
            new_matrix->matrix_content[i][j] = l->matrix_content[i][j] + r->matrix_content[i][j];
        }
    }

    return new_matrix;
}

Matrix* sub(const Matrix* l, const Matrix* r) {
    Matrix* new_matrix = create_matrix(l->rows, l->cols);

    for (size_t i = 0; i < l->rows; ++i) {
        for (size_t j = 0; j < l->cols; ++j) {
            new_matrix->matrix_content[i][j] = l->matrix_content[i][j] - r->matrix_content[i][j];
        }
    }

    return new_matrix;
}

Matrix* mul(const Matrix* l, const Matrix* r) {
    if (l->cols != r->rows) {
        return NULL;
    }

    Matrix* new_matrix = create_matrix(l->rows, r->cols);

    for (size_t i = 0; i < l->rows; ++i) {
        for (size_t j = 0; j < r->cols; ++j) {
            new_matrix->matrix_content[i][j]= 0;
            for (size_t k = 0; k < l->cols; ++k)
                new_matrix->matrix_content[i][j] += l->matrix_content[i][k] * r->matrix_content[k][j];
        }
    }

    return new_matrix;
}

// Extra operations

void less_double_arr(double **matrix, double **new_matrix, size_t row, size_t col, size_t size) {
    size_t skip_i = 0;
    for (size_t i = 0; i < size - 1; ++i) {
        if (i == row) {
            skip_i = 1;
        }
        size_t skip_j = 0;
        for (size_t j = 0; j < size - 1; ++j) {
            if (j == col) {
                skip_j = 1;
            }
            new_matrix[i][j] = matrix[i + skip_i][j + skip_j];
        }
    }
}

void less_matrix(const Matrix* matrix, Matrix* new_matrix, size_t row, size_t col) {
    size_t skip_i = 0;
    for (size_t i = 0; i < new_matrix->rows; ++i) {
        if (i == row) {
            skip_i = 1;
        }
        size_t skip_j = 0;
        for (size_t j = 0; j < new_matrix->cols; ++j) {
            if (j == col) {
                skip_j = 1;
            }
            new_matrix->matrix_content[i][j] = matrix->matrix_content[i + skip_i][j + skip_j];
        }
    }
}

double get_det(double **matrix, size_t size) {
    int det_power = 1;

    double** matrix_2 = (double**)malloc(sizeof(double) * size), ret = 0;

    for (size_t i = 0; i < size; ++i) {
        matrix_2[i] = (double*)malloc(sizeof(double) * size);
    }

    if (size < 1) {
        return ERROR;
    }

    if (size == 1) {
        ret = matrix[0][0];
        return(ret);
    }

    if (size == 2) {
        ret = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
        return(ret);
    }

    for (size_t i = 0; i < size; ++i) {
        less_double_arr(matrix, matrix_2, i, 0, size);
        ret = ret + det_power * matrix[i][0] * get_det(matrix_2, size - 1);
        det_power = -det_power;
    }

    return(ret);
}

int det(const Matrix* matrix, double* val) {
    *val = get_det(matrix->matrix_content, matrix->rows);

    return 0;
}

Matrix* adj(const Matrix* matrix) {
    Matrix* new_matrix = create_matrix(matrix->rows, matrix->cols);
    int det_power;
    for (size_t i = 0; i < new_matrix->rows; ++i) {
        for (size_t j = 0; j < new_matrix->cols; ++j) {
            Matrix* additional_matrix = create_matrix(new_matrix->rows - 1, new_matrix->cols - 1);
            less_matrix(matrix, additional_matrix, j, i);
            if ((i + j) % 2 == 0) {
                det_power = 1;
            } else {
                det_power = -1;
            }
            new_matrix->matrix_content[i][j] =
            det_power * get_det(additional_matrix->matrix_content, additional_matrix->rows);
        }
    }

    return new_matrix;
}

Matrix* inv(const Matrix* matrix) {
    if (matrix->rows == 1) {
        Matrix* new_matrix = create_matrix(matrix->rows, matrix->cols);
        new_matrix->matrix_content[0][0] = 1 / matrix->matrix_content[0][0];
        return new_matrix;
    }

    Matrix* additional_matrix = adj(matrix);
    Matrix* new_matrix = mul_scalar(additional_matrix, 1 / get_det(matrix->matrix_content, matrix->rows));

    return new_matrix;
}
