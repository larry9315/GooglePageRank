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
    Matrix s_matrix;
    Matrix m_matrix;
    Matrix rank_matrix;

    vector<double> myVec;
    int dimension;

    void read(string fileName);

    void build_s_matrix();

    void build_m_matrix();

    void build_rank_matrix();

public:
    GoogleRank();

    void printResult();
};