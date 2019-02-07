//
// Created by larry on 2019-01-29.
//

#include "matrix.hpp"

Matrix::Matrix() {
    row = 1;
    column = 1;

    myArr = new double[row];
    myArr[0] = 0.0;
}

Matrix::Matrix(int n) {
    if (n <= 0) {
        cout << "exception thrown" << endl;
        throw new exception();
    }

    row = n;
    column = n;

    myArr = new double[n * n];
    for (int i = 0; i < n * n; i++) {
        myArr[i] = 0.0;
    }
}

Matrix::Matrix(int r, int c) {
    if (r <= 0 || c <= 0) {
        cout << "exception thrown" << endl;
        throw new exception();
    }

    row = r;
    column = c;

    myArr = new double[r * c];
    for (int i = 0; i < r * c; i++) {
        myArr[i] = 0.0;
    }
}

Matrix::Matrix(double arr[], int size) {

    double squaredVal = sqrt(size);
    if ((squaredVal - floor(squaredVal)) != 0) {
        cout << "exception thrown" << endl;
        throw new exception();
    }

    row = squaredVal;
    column = squaredVal;

    myArr = new double[size];
    for (int i = 0; i < size; i++) {
        myArr[i] = arr[i];
    }

}

Matrix::Matrix(const Matrix& other) {
    row = other.row;
    column = other.column;
    myArr = new double[row * column];
    for (int i = 0; i < row * column; i++) {
        myArr[i] = other.myArr[i];
    }
}

void Matrix::set_value(int r, int c, double newValue) {
    if (r >= row || r < 0 || c >= column || c < 0) {
        cout << "Exception thrown" << endl;
        throw new exception();
    }
    myArr[column * r + c] = newValue;
}

double Matrix::get_value(int r, int c) {
    if (r >= row || r < 0 || c >= column || c < 0) {
        cout << "Exception thrown" << endl;
        throw new exception();
    }

    return myArr[column * r + c];
}

void Matrix::clear() {
    for (int i = 0; i < row * column; i++) {
        myArr[i] = 0.0;
    }
}

ostream& operator<<(ostream& os, const Matrix& obj) {
    int j = 0;
    for (int i = 0; i < obj.row * obj.column; i++) {
        os << setw(5) << obj.myArr[i] << " ";
        j++;
        if (j % obj.column == 0) {
            os << endl;
        }
    }
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.row != rhs.row || lhs.column != rhs.column) {
        return false;
    }

    // absolute value of the two minus value to handle tolerance calculatrion
    for (int i = 0; i < lhs.row * lhs.column; i++) {
        if (fabs(lhs.myArr[i] - rhs.myArr[i]) >= EPSILON) {
            return false;
        }
    }
    return true;
}

bool operator!=(const Matrix& lhs, const Matrix& rhs) {
    return !operator==(lhs, rhs);
}

Matrix& Matrix::operator++() {
    for (int i = 0; i < row * column; i++) {
        myArr[i]++;
    }
    return *this;
}

Matrix Matrix::operator++(int) {
    Matrix temp(*this);
    operator++();
    return temp;
}

Matrix& Matrix::operator--() {
    for (int i = 0; i < row * column; i++) {
        myArr[i]--;
    }
    return *this;
}

Matrix Matrix::operator--(int) {
    Matrix temp(*this);
    operator--();
    return temp;
}

Matrix& Matrix::operator=(Matrix rhs) {
    mySwap(*this, rhs);
    return *this;
}

// is if condition necessary
Matrix operator+(Matrix lhs, const Matrix& rhs) {

    lhs += rhs;
    return lhs;
}

Matrix& Matrix::operator+=(const Matrix& rhs) {
    if (row != rhs.row || column != rhs.column) {
        cout << "exception thrown" << endl;
        throw new exception();
    }

    for (int i = 0; i < row * column; i++) {
        myArr[i] += rhs.myArr[i];
    }

    return *this;
}

Matrix operator-(Matrix lhs, const Matrix& rhs) {
    lhs -= rhs;
    return lhs;
}

Matrix& Matrix::operator-=(const Matrix& rhs) {
    if (row != rhs.row || column != rhs.column) {
        cout << "exception thrown" << endl;
        throw new exception();
    }

    for (int i = 0; i < row * column; i++) {
        myArr[i] -= rhs.myArr[i];
    }

    return *this;
}

Matrix operator*(Matrix lhs, const Matrix& rhs) {
    lhs *= rhs;
    return lhs;
}

Matrix& Matrix::operator*=(const Matrix& rhs) {
    if (column != rhs.row) {
        cout << "row column doesnt match" << endl;
        throw new exception();
    }

    double tempArr[row][column];
    double tempArr2[rhs.row][rhs.column];

    // creating temp array one for matrix multiplication
    int k = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            tempArr[i][j] = myArr[k];
            k++;
        }
    }

    // creating temp array one for matrix multiplication
    k = 0;
    for (int i = 0; i < rhs.row; i++) {
        for (int j = 0; j < rhs.column; j++) {
            tempArr2[i][j] = rhs.myArr[k];
            k++;
        }
    }

    k = 0;
    int t;
    int j;
    delete[] myArr;
    myArr = new double[row * rhs.column];

    for (int i = 0; i < row * rhs.column; i++) {
        myArr[i] = 0.0;
    }

    //matrix multiplication algorithm
    for (int i = 0; i < row; i++) {
        for (t = 0; t < rhs.column; t++) {
            for (j = 0; j < column; j++) {
                myArr[k] += tempArr[i][j] * tempArr2[j][t];
            }
            k++;
        }
    }

    column = rhs.column;
    return *this;

}

void mySwap(Matrix &first, Matrix &second) {
    swap(first.row, second.row);
    swap(first.column, second.column);
    swap(first.myArr, second.myArr);
}

Matrix::~Matrix() {
    delete[] myArr;
}

