// Matrix.cpp

#include "Matrix.h"
#include <stdexcept>

// Default constructor
Matrix::Matrix() : data({}, 0) {
    numCols = 0;
    numRows = 0;
}

// Constructor with rows and columns
// YOUR CODE HERE
Matrix::Matrix(int rows, int cols) : data(rows), numRows(rows), numCols(cols) {
    for (int i = 0; i < rows; ++i) {
        data[i] = Vector<uint8_t>(cols);
    }
}

// Copy constructor
// YOUR CODE HERE
Matrix::Matrix(const Matrix& other) : data(other.data), numRows(other.numRows), numCols(other.numCols) {}

// Assignment operator
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        data = other.data;
        numRows = other.numRows;
        numCols = other.numCols;
    }
    return *this;
}

// Destructor
Matrix::~Matrix() {}

// Number of rows
int Matrix::getRows() const {
    return data.getSize();
}

// Number of columns
int Matrix::getCols() const {
    return data.getSize() > 0 ? data[0].getSize() : 0;
}

// Input stream operator
std::istream& operator>>(std::istream& in, Matrix& mat) {
    for (int i = 0; i < mat.numRows; ++i) {
        for (int j = 0; j < mat.numCols; ++j) {
            int val;
            in >> val;
            if (val < 0 || val > 255) {
                throw std::out_of_range("Input value out of uint8_t range.");
            }
            mat.data[i][j] = static_cast<uint8_t>(val);
        }
    }
    return in;
}

// Output stream operator
std::ostream& operator<<(std::ostream& out, const Matrix& mat) {
    for (int i = 0; i < mat.numRows; ++i) {
        for (int j = 0; j < mat.numCols; ++j) {
            out << static_cast<int>(mat.data[i][j]) << ' ';
        }
        out << '\n';
    }
    return out;
}

// Arithmetic operators
Matrix Matrix::operator+(const Matrix& other) const {
    if (numRows != other.numRows || numCols != other.numCols) {
        throw std::invalid_argument("Matrix sizes do not match for addition.");
    }
    Matrix result(numRows, numCols);
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            result[i][j] = data[i][j] + other[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (numRows != other.numRows || numCols != other.numCols) {
        throw std::invalid_argument("Matrix sizes do not match for subtraction.");
    }
    Matrix result(numRows, numCols);
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            result[i][j] = data[i][j] - other[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (numCols != other.numRows)
        throw std::invalid_argument("Matrix sizes do not match for multiplication.");

    Matrix result(numRows, other.numCols);
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < other.numCols; ++j) {
            uint8_t sum = 0;
            for (int k = 0; k < numCols; ++k) {
                sum += data[i][k] * other.data[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}

// Subscript operator
Vector<uint8_t>& Matrix::operator[](int index) {
    if (index < 0 || index >= numRows) {
        throw std::out_of_range("Row index out of range.");
    }
    return data[index];
}

const Vector<uint8_t>& Matrix::operator[](int index) const {
    if (index < 0 || index >= numRows) {
        throw std::out_of_range("Row index out of range.");
    }
    return data[index];
}

// Transpose function (in-place)
void Matrix::transpose() {
    Vector<Vector<uint8_t>> transposed(numCols);
    for (int i = 0; i < numCols; ++i) {
        transposed[i] = Vector<uint8_t>(numRows);
        for (int j = 0; j < numRows; ++j) {
            transposed[i][j] = data[j][i];
        }
    }
    data = transposed;
    std::swap(numRows, numCols);
}

