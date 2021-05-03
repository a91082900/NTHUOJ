#include "function.h"

std::ostream &operator<<(std::ostream &os, const Matrix &m) {
    for(int i = 0; i < m.size; i++) {
        for(int j = 0; j < m.size; j++)
            os << m.buf[i*m.size+j] << " \n"[j==m.size-1];
    }
    return os;
}
std::istream &operator>>(std::istream &is, Matrix &m) {
    for(int i = 0; i < m.size * m.size; i++) {
        is >> m.buf[i];
    }
    return is;
}
Matrix::Matrix(int s) {
    size = s;
    buf = new int[s*s];
}

Matrix::Matrix(const Matrix &m) {
    size = m.size;
    buf = new int[size*size];
    for(int i = 0; i < size * size; i++) {
        buf[i] = m.buf[i];
    }
}

Matrix::~Matrix() {
    delete buf;
}

Matrix& Matrix::operator=(const Matrix &a) {
    size = a.size;
    buf = new int[size*size];
    for(int i = 0; i < size * size; i++) {
        buf[i] = a.buf[i];
    }
    return *this;
}

Matrix& Matrix::clockwise90() {
    // 13 9 5 1
    // 14 10 6 2
    // 15 11 7 3
    // 16 12 8 4
    int *new_buf = new int[size*size];
    int idx = 0;
    for(int j = 0; j < size; j++) {
        for(int i = size-1; i >= 0; i--) {
            new_buf[idx++] = buf[i*size+j];
        }
    }
    buf = new_buf;
    return *this;
}
/*private:
    int **matrix;
    int *buf;   // 2D matrix stored in 1D raster scan order
    int size;
}; //end class Matrix
*/
