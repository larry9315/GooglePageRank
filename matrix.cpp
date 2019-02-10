//
// Created by larry on 2019-01-29.
//

#include "matrix.hpp"

// default constructor that constructs 1 by 1 matrix of value 0
Matrix::Matrix() {
    row = 1;
    column = 1;

    myArr = new double[row];
    myArr[0] = 0.0;
}

// creates an n by n matrix with row and column size match to n
Matrix::Matrix(int n) {
    if (n <= 0) {
        cout << "exception thrown" << endl;
        throw "invalid n size";
    }

    row = n;
    column = n;

    myArr = new double[n * n];
    for (int i = 0; i < n * n; i++) {
        myArr[i] = 0.0;
    }
}

// consturcts matrix by r row size and c column size
Matrix::Matrix(int r, int c) {
    if (r <= 0 || c <= 0) {
        cout << "exception thrown" << endl;
        throw "invalid row or column size";
    }

    row = r;
    column = c;

    myArr = new double[r * c];
    for (int i = 0; i < r * c; i++) {
        myArr[i] = 0.0;
    }
}

// consturcts matrix based on array and parameter has to be perfect square
Matrix::Matrix(double arr[], int size) {

    double squaredVal = sqrt(size);
    if ((squaredVal - floor(squaredVal)) != 0) {
        cout << "exception thrown" << endl;
        throw "not a perfect square value";
    }

    row = squaredVal;
    column = squaredVal;

    myArr = new double[size];
    for (int i = 0; i < size; i++) {
        myArr[i] = arr[i];
    }

}

// copy constructor
Matrix::Matrix(const Matrix& other) {
    row = other.row;
    column = other.column;
    myArr = new double[row * column];
    for (int i = 0; i < row * column; i++) {
        myArr[i] = other.myArr[i];
    }
}

// sets the located indicies to new value
void Matrix::set_value(int r, int c, double newValue) {
    if (r >= row || r < 0 || c >= column || c < 0) {
        cout << "Exception thrown" << endl;
        throw "invalid row r";
    }
    myArr[column * r + c] = newValue;
}

// gets the located indicies value in matrix
double Matrix::get_value(int r, int c) {
    if (r >= row || r < 0 || c >= column || c < 0) {
        cout << "Exception thrown" << endl;
        throw new exception();
    }

    return myArr[column * r + c];
}

// sets all elements in array to 0
void Matrix::clear() {
    for (int i = 0; i < row * column; i++) {
        myArr[i] = 0.0;
    }
}

// prints the elements using flags to nicely align the elements
ostream& operator<<(ostream& os, const Matrix& obj) {
    int j = 0;
    for (int i = 0; i < obj.row * obj.column; i++) {
        os << setw(5) << obj.myArr[i] << " ";
        j++;
        if (j % obj.column == 0) {
            os << endl;
        }
    }
    return os;
}

// equals operator that checks every elements and returns false if dimension is incorrect.
bool operator==(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.row != rhs.row || lhs.column != rhs.column) {
        return false;
    }

    constexpr double EPSILON = 0.0001;

    // absolute value of the two minus value to handle tolerance calculation
    for (int i = 0; i < lhs.row * lhs.column; i++) {
        if (fabs(lhs.myArr[i] - rhs.myArr[i]) >= EPSILON) {
            return false;
        }
    }
    return true;
}

// not equals operator
bool operator!=(const Matrix& lhs, const Matrix& rhs) {
    return !operator==(lhs, rhs);
}

// increments all elements by 1
Matrix& Matrix::operator++() {
    for (int i = 0; i < row * column; i++) {
        myArr[i]++;
    }
    return *this;
}

// increments all elements by 1
Matrix Matrix::operator++(int) {
    Matrix temp(*this);
    operator++();
    return temp;
}

// decrements all elements by 1
Matrix& Matrix::operator--() {
    for (int i = 0; i < row * column; i++) {
        myArr[i]--;
    }
    return *this;
}

// decrements all elements by 1
Matrix Matrix::operator--(int) {
    Matrix temp(*this);
    operator--();
    return temp;
}

// copy and swap
Matrix& Matrix::operator=(Matrix rhs) {
    mySwap(*this, rhs);
    return *this;
}

Matrix operator+(Matrix lhs, const Matrix& rhs) {

    lhs += rhs;
    return lhs;
}

// adds matrix
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

// subtracts matrix
Matrix operator-(Matrix lhs, const Matrix& rhs) {
    lhs -= rhs;
    return lhs;
}

//subtracts matrix
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

// multiplier matrices
Matrix operator*(Matrix lhs, const Matrix& rhs) {
    lhs *= rhs;
    return lhs;
}

// multiplies matrices, resizes to size first matrix row and second matrix column
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

    // creating temp array two for matrix multiplication
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

    //matrix multiplication azlgorithm
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

// my swap method that swaps the object instance variables
void mySwap(Matrix &first, Matrix &second) {
    swap(first.row, second.row);
    swap(first.column, second.column);
    swap(first.myArr, second.myArr);
}

//deallocates the memory for dynamic allocation
Matrix::~Matrix() {
    delete[] myArr;
}

