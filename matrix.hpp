//
// Created by larry on 2019-01-29.
//

#ifndef ASSIGNMENT1_MATRIX_HPP
#define ASSIGNMENT1_MATRIX_HPP

#endif //ASSIGNMENT1_MATRIX_HPP

#include <vector>
#include <iostream>
#include <math.h>
#include <iomanip>


using namespace std;

constexpr double EPSILON = 0.0001;
constexpr double P_VALUE = 0.85;
constexpr int INT_CONVERTER_VAL = 65;

class Matrix {
private:
    int row;
    int column;
    double * myArr;

public:
    Matrix();

    Matrix(int n);

    Matrix(int r, int c);

    Matrix(double arr[], int size);

    Matrix(const Matrix& other);

    void set_value(int r, int c, double newValue);

    double get_value(int r, int c);

    void clear();

    friend ostream& operator<<(ostream& os, const Matrix& obj);

    friend bool operator==(const Matrix& lhs, const Matrix& rhs);

    friend bool operator!=(const Matrix& lhs, const Matrix& rhs);

    Matrix& operator++();

    Matrix operator++(int);

    Matrix& operator--();

    Matrix operator--(int);

    Matrix& operator=(Matrix rhs);

    friend Matrix operator+(Matrix lhs, const Matrix& rhs);

    Matrix& operator+=(const Matrix& rhs);

    friend Matrix operator-(Matrix lhs, const Matrix& rhs);

    Matrix& operator-=(const Matrix& rhs);

    friend Matrix operator*(Matrix lhs, const Matrix& rhs);

    Matrix& operator*=(const Matrix& rhs);

    friend void mySwap(Matrix& first, Matrix& second);

    ~Matrix();




};
