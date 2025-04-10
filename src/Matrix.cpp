// Matrix.cpp

#include "Matrix.h"
#include <stdexcept>

// Default constructor
Matrix::Matrix() {}

// Constructor with rows and columns
// YOUR CODE HERE

// Copy constructor
// YOUR CODE HERE

// Assignment operator
Matrix& Matrix::operator=(const Matrix& other) {
    // YOUR CODE HERE
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
    // YOUR CODE HERE
}

// Output stream operator
std::ostream& operator<<(std::ostream& out, const Matrix& mat) {
    // YOUR CODE HERE
}

// Arithmetic operators
Matrix Matrix::operator+(const Matrix& other) const {
    // YOUR CODE HERE
}

Matrix Matrix::operator-(const Matrix& other) const {
    // YOUR CODE HERE
}

Matrix Matrix::operator*(const Matrix& other) const {
    // YOUR CODE HERE
}

// Subscript operator
Vector<uint8_t>& Matrix::operator[](int index) {
   // YOUR CODE HERE
}

const Vector<uint8_t>& Matrix::operator[](int index) const {
   // YOUR CODE HERE
}

// Transpose function (in-place)
void Matrix::transpose() {
    // YOUR CODE HERE
}

