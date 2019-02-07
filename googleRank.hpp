//
// Created by larry on 2019-02-06.
//

#ifndef ASSIGNMENT1_GOOGLERANK_HPP
#define ASSIGNMENT1_GOOGLERANK_HPP

#endif //ASSIGNMENT1_GOOGLERANK_HPP

#include "matrix.hpp"
#include <string.h>
#include <fstream>

class GoogleRank {


    vector<double> myVec;
    int dimension;
public:
    GoogleRank();

    void read(string fileName);

    Matrix get_s_matrix();

    Matrix get_m_matrix(const Matrix& s_matrix);

    Matrix get_rank_matrix(const Matrix& m_matrix);

    void printResult(Matrix& rank_matrix);
};