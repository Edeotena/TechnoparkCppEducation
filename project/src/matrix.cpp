#include "matrix.h"
#include "exceptions.h"

namespace prep {
    Matrix::Matrix(size_t rows, size_t cols):
    rows(rows), cols(cols) {
        this->matrix_content.resize(rows);

        for (auto& i : this->matrix_content) {
            i.resize(cols);
        }
    }

    Matrix::Matrix(std::istream& is) {
        if (!is) {
            throw InvalidMatrixStream();
        }

        if (!(is >> this->rows >> this->cols)) {
            throw InvalidMatrixStream();
        }

        this->matrix_content.resize(rows);

        for (auto& i : this->matrix_content) {
            i.resize(cols);

               for (auto& j : i) {
                    std::string string_to_transform;
                    is >> string_to_transform;

                try {
                       j = std::stod(string_to_transform);
                }
                catch (std::invalid_argument& stod_exception) {
                       throw InvalidMatrixStream();
                }
            }
        }
    }

    size_t Matrix::getRows() const {
        return this->rows;
    }

    size_t Matrix::getCols() const {
        return this->cols;
    }

    double Matrix::operator()(size_t i, size_t j) const {
        if (i >= this->rows || j >= this->cols) {
            throw OutOfRange(i, j, *this);
        }

        return this->matrix_content[i][j];
    }

    double& Matrix::operator()(size_t i, size_t j) {
        if (i >= this->rows || j >= this->cols) {
            throw OutOfRange(i, j, *this);
        }

        return this->matrix_content[i][j];
    }

    bool Matrix::operator==(const Matrix &rhs) const {
        if (this->rows != rhs.rows || this->cols != rhs.cols) {
            return false;
        }
        for (size_t i = 0; i < this->rows; ++i) {
            for (size_t j = 0; j < this->cols; ++j) {
                if (this->matrix_content[i][j] - rhs.matrix_content[i][j] > EPS || this->matrix_content[i][j] - rhs.matrix_content[i][j] < -EPS) {
                    return false;
                }
            }
        }

        return true;
    }

    bool Matrix::operator!=(const Matrix &rhs) const {
        return !(*this == rhs);
    }

    Matrix Matrix::operator+(const Matrix &rhs) const {
        if (this->rows != rhs.rows || this->cols != rhs.cols) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix ready_matrix(this->rows, this->cols);

        for (size_t i = 0; i < this->rows; ++i) {
            for (size_t j = 0; j < this->cols; ++j) {
                ready_matrix.matrix_content[i][j] = this->matrix_content[i][j] + rhs.matrix_content[i][j];
            }
        }

        return ready_matrix;
    }

    Matrix Matrix::operator-(const Matrix &rhs) const {
        if (this->rows != rhs.rows || this->cols != rhs.cols) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix ready_matrix(this->rows, this->cols);

        for (size_t i = 0; i < this->rows; ++i) {
            for (size_t j = 0; j < this->cols; ++j) {
                ready_matrix.matrix_content[i][j] = this->matrix_content[i][j] - rhs.matrix_content[i][j];
            }
        }

        return ready_matrix;
    }

    Matrix Matrix::operator*(const Matrix &rhs) const {
        if (this->cols != rhs.rows) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix ready_matrix(this->rows, rhs.cols);

        for (size_t i = 0; i < this->rows; ++i) {
            for (size_t j = 0; j < rhs.cols; ++j) {
                ready_matrix.matrix_content[i][j]= 0;

                for (size_t k = 0; k < this->cols; ++k)
                    ready_matrix.matrix_content[i][j] += this->matrix_content[i][k] * rhs.matrix_content[k][j];
            }
        }

        return ready_matrix;
    }

    Matrix Matrix::operator*(double val) const {
        Matrix ready_matrix(this->rows, this->cols);

        for (size_t i = 0; i < this->rows; ++i) {
            for (size_t j = 0; j < this->cols; ++j) {
                ready_matrix.matrix_content[i][j] = this->matrix_content[i][j] * val;
            }
        }

        return ready_matrix;
    }

    Matrix operator*(double val, const Matrix& matrix) {
        Matrix ready_matrix(matrix.rows, matrix.cols);

        for (size_t i = 0; i < matrix.rows; ++i) {
            for (size_t j = 0; j < matrix.cols; ++j) {
                ready_matrix.matrix_content[i][j] = matrix.matrix_content[i][j] * val;
            }
        }

        return ready_matrix;
    }

    std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        if (!os) {
            throw InvalidMatrixStream();
        }

        if (!(os << matrix.rows << " " << matrix.cols << std::endl).good()) {
            throw InvalidMatrixStream();
        }

        for (auto& i : matrix.matrix_content) {
            for (auto& j : i) {
                    auto maxdigitsdouble = std::numeric_limits<double>::digits10;
                    if (!(os << std::setprecision(maxdigitsdouble) << j << " ").good()) {
                        throw InvalidMatrixStream();
                    }
            }
            os << std::endl;
        }

        return os;
    }

    Matrix Matrix::transp() const {
        Matrix ready_matrix(this->cols, this->rows);

        for (size_t i = 0; i < this->cols; ++i) {
            for (size_t j = 0; j < this->rows; ++j) {
                ready_matrix.matrix_content[i][j] = this->matrix_content[j][i];
            }
        }
        return ready_matrix;
    }

    void less_matrix(const Matrix& matrix, Matrix& next_matrix, size_t row, size_t col) {
        size_t row_to_skip = 0;

        for (size_t i = 0; i < matrix.getRows() - 1; ++i) {
            if (i == row) {
                row_to_skip = 1;
            }

            size_t col_to_skip = 0;

            for (size_t j = 0; j < matrix.getRows() - 1; ++j) {
                if (j == col) {
                    col_to_skip = 1;
                }

                next_matrix(i, j) = matrix(i + row_to_skip, j + col_to_skip);
            }
        }
    }


    double get_det(Matrix& matrix) {
        double temp_det = 0;

        if (matrix.getRows() == 1) {
            temp_det = matrix(0, 0);
            return temp_det;
        }

        if (matrix.getRows() == 2) {
            temp_det = matrix(0, 0) * matrix(1, 1) - matrix(1, 0) * matrix(0, 1);
            return temp_det;
        }

        int det_power = DETPOWER;

        Matrix next_matrix(matrix.getRows() - 1, matrix.getCols() - 1);

        for (size_t i = 0; i < matrix.getRows(); ++i) {
            less_matrix(matrix, next_matrix, i, 0);
            temp_det = temp_det + det_power * matrix(i, 0) * get_det(next_matrix);
            det_power = -det_power;
        }

        return temp_det;
    }

    double Matrix::det() const {
        Matrix matrix_to_det(*this);
        if (this->rows != this->cols) {
            throw DimensionMismatch(matrix_to_det);
        }

        return get_det(matrix_to_det);
    }

    Matrix Matrix::adj() const {
        Matrix ready_matrix(this->rows, this->cols);
        Matrix main_matrix(*this);

        if (this->cols != this->rows) {
            throw DimensionMismatch(main_matrix);
        }

        int det_power = DETPOWER;

        for (size_t i = 0; i < this->rows; ++i) {
            for (size_t j = 0; j < this->cols; ++j) {
                Matrix additions_matrix(this->rows - 1, this->cols - 1);

                less_matrix(main_matrix, additions_matrix, j, i);
                if ((i + j) % 2 == 0) {
                    det_power = 1;
                } else {
                    det_power = -1;
                }

                ready_matrix(i, j) = det_power * get_det(additions_matrix);
            }
        }

        return ready_matrix;
    }

    Matrix Matrix::inv() const {
        if (this->det() == 0) {
            throw SingularMatrix();
        }


        if (this->rows == 1) {
            Matrix new_matrix(this->rows, this->cols);
            new_matrix(0, 0) = 1 / this->matrix_content[0][0];
            return new_matrix;
        }

        Matrix additional_matrix = this->adj();
        Matrix new_matrix = 1 / this->det() * additional_matrix;

        return new_matrix;
    }

}  // namespace prep
