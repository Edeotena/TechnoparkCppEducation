#include "matrix.h"

#define ERROR (-1)

// Init/release operations
Matrix* create_matrix(size_t rows, size_t cols) {
    if (rows < 1 || cols < 1) {
        return NULL;
    }

    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));

    if (matrix == NULL) {
        return NULL;
    }

    matrix->rows = rows;
    matrix->cols = cols;

    matrix->matrix_content = (double**)malloc(rows * sizeof(double*));

    if (matrix->matrix_content == NULL) {
        free(matrix);
        return NULL;
    }

    for (size_t i = 0; i < rows; ++i) {
        matrix->matrix_content[i] = (double*)malloc(cols * sizeof(double));
        if (matrix->matrix_content[i] == NULL) {
            for(size_t j = 0; j < i; ++j) {
                free(matrix->matrix_content[j]);
            }
            free(matrix->matrix_content);
            free(matrix);
            return NULL;
        }
    }

    return matrix;

}

Matrix* create_matrix_from_file(const char* path_file) {
    FILE* file_to_read = fopen(path_file, "r");
    if (file_to_read == NULL) {
        return NULL;
    }

    size_t rows, cols;

    fscanf(file_to_read, "%zu%zu", &rows, &cols);
    Matrix* matrix = create_matrix(rows, cols);
    if (matrix == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            fscanf(file_to_read, "%lf", &matrix->matrix_content[i][j]);
        }
    }

    fclose(file_to_read);
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
    if (row >= matrix->rows || col >= matrix->cols) {
        return ERROR;
    }

    *val = matrix->matrix_content[row - 1][col - 1];

    return 0;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    if (row >= matrix->rows || col >= matrix->cols) {
        return ERROR;
    }

    matrix->matrix_content[row - 1][col - 1] = val;

    return 0;
}

//Math operations
Matrix* mul_scalar(const Matrix* matrix, double val) {
    for (size_t i = 0; i < matrix->rows; ++i) {
        for (size_t j = 0; j < matrix->cols; ++j) {
            matrix->matrix_content[i][j] *= val;
        }
    }

    return NULL;
}

Matrix* transp(const Matrix* matrix) {
    Matrix* new_matrix = create_matrix(matrix->cols, matrix->rows);
    if(matrix == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < matrix->rows; ++i) {
        for (size_t j = 0; j < matrix->cols; ++j) {
            new_matrix->matrix_content[j][i] = matrix->matrix_content[i][j];
        }
    }

    return new_matrix;
}

Matrix* sum(const Matrix* l, const Matrix* r) {
    if (l->cols != r->rows) {
        return NULL;
    }
    Matrix* new_matrix = create_matrix(l->rows, r->cols);
    if (new_matrix == NULL) {
        return NULL;
    }

    return new_matrix;
}

Matrix* sub(const Matrix* l, const Matrix* r) {
    printf("%lf%lf",l->matrix_content[0][0], r->matrix_content[0][0]);
    return NULL;
}

Matrix* mul(const Matrix* l, const Matrix* r) {
    printf("%lf%lf",l->matrix_content[0][0], r->matrix_content[0][0]);
    return NULL;
}

// Extra operations
int det(const Matrix* matrix, double* val) {
    printf("%lf",matrix->matrix_content[0][0]);
    val--;
    return 0;
}

Matrix* adj(const Matrix* matrix) {
    printf("%lf",matrix->matrix_content[0][0]);
    return NULL;
}

Matrix* inv(const Matrix* matrix) {
    printf("%lf",matrix->matrix_content[0][0]);
    return NULL;
}
