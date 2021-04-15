#include "matrix.h"

// Init/release operations

Matrix* create_matrix(size_t rows, size_t cols) {
    Matrix* matrix = (Matrix*)malloc(sizeof(struct Matrix));
    if (matrix == NULL) {
        return NULL;
    }

    matrix->rows = rows;
    matrix->cols = cols;

    matrix->matrix_content  = (double**)malloc(rows * sizeof(double*));
    if (matrix->matrix_content  == NULL) {
        free(matrix);
        return NULL;
    }

    for (size_t i = 0; i < rows; ++i) {
        matrix->matrix_content[i] = (double*)malloc(cols * sizeof(double*));
        if (matrix->matrix_content[i] == NULL) {
            for (size_t j = 0; j < i; ++j) {
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

    size_t rows_from_file, cols_from_file;

    if (fscanf(file_to_read, "%zu %zu", &rows_from_file, &cols_from_file) != 2) {
        fclose(file_to_read);
        return NULL;
    }

    Matrix* matrix = create_matrix(rows_from_file, cols_from_file);

    for (size_t i = 0; i < matrix->rows; ++i) {
        for (size_t j = 0; j <matrix->cols; ++j) {
            if (fscanf(file_to_read, "%lf", &matrix->matrix_content[i][j]) != 1) {
                fclose(file_to_read);
                free_matrix(matrix);
                return NULL;
            }
        }
    }

    if (fclose(file_to_read) != 0) {
        free_matrix(matrix);
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

    if (new_matrix == NULL) {
        return NULL;
    }

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

    if (new_matrix == NULL) {
        return NULL;
    }

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

double get_det(double **matrix, size_t size) {
    int det_power = 1;

    double ret = 0;

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

    double** matrix_2 = (double**)malloc(sizeof(double) * size);

    for (size_t i = 0; i < size; ++i) {
        matrix_2[i] = (double*)malloc(sizeof(double) * size);
    }

    for (size_t i = 0; i < size; ++i) {
        less_double_arr(matrix, matrix_2, i, 0, size);
        ret = ret + det_power * matrix[i][0] * get_det(matrix_2, size - 1);
        det_power = -det_power;
    }

    for (size_t i = 0; i < size; ++i) {
        free(matrix_2[i]);
    }
    free(matrix_2);

    return(ret);
}

int det(const Matrix* matrix, double* val) {
    if (matrix->rows != matrix->cols) {
        return (-1);
    }

    *val = get_det(matrix->matrix_content, matrix->rows);

    return 0;
}

Matrix* adj(const Matrix* matrix) {
    Matrix* new_matrix = create_matrix(matrix->rows, matrix->cols);

    if (new_matrix == NULL) {
            return NULL;
    }

    int det_power;
    for (size_t i = 0; i < new_matrix->rows; ++i) {
        for (size_t j = 0; j < new_matrix->cols; ++j) {
            Matrix* additional_matrix = create_matrix(new_matrix->rows - 1, new_matrix->cols - 1);
            less_double_arr(matrix->matrix_content, additional_matrix->matrix_content, j, i, matrix->rows);
            if ((i + j) % 2 == 0) {
                det_power = 1;
            } else {
                det_power = -1;
            }
            new_matrix->matrix_content[i][j] =
            det_power * get_det(additional_matrix->matrix_content, additional_matrix->rows);
            free_matrix(additional_matrix);
        }
    }

    return new_matrix;
}

Matrix* inv(const Matrix* matrix) {
    if (matrix->rows == 1) {
        Matrix* new_matrix = create_matrix(matrix->rows, matrix->cols);

        if (new_matrix == NULL) {
            return NULL;
        }

        if (matrix->matrix_content[0][0] == 0) {
            free_matrix(new_matrix);
            return NULL;
        }

        new_matrix->matrix_content[0][0] = 1 / matrix->matrix_content[0][0];
        return new_matrix;
    }

    Matrix* additional_matrix = adj(matrix);

    if (additional_matrix == NULL) {
        return NULL;
    }

    double matrix_det = get_det(matrix->matrix_content, matrix->rows);
    if (matrix_det == 0) {
        free_matrix(additional_matrix);
        return NULL;
    }

    Matrix* new_matrix = mul_scalar(additional_matrix, 1 / matrix_det);

    free_matrix(additional_matrix);

    return new_matrix;
}
