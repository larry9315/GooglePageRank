//
// Created by larry on 2019-02-06.
//


#include "googleRank.hpp"

GoogleRank::GoogleRank() {
    read("connectivity.txt");
    // getting n dimension of square matrix

//    build_s_matrix();
//    build_m_matrix();
//    build_rank_matrix();


}

void GoogleRank::read(string fileName) {
    // reads from the file
    ifstream file{fileName};
    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        exit(1);
    } else {
        //create vector for extracting the connectivity matrix

        double element;
        // information extraction
        while (file >> element) {
            myVec.push_back(element);
        }
        dimension = sqrt(myVec.size());
    }
}

Matrix GoogleRank::get_s_matrix() {
    // create first stage of s matrix

    Matrix s_matrix(dimension);

    int k = 0;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            s_matrix.set_value(i, j, myVec[k]);
            k++;
        }
    }

    // divide the s matrix by the sum of the columns and set 0 column sum column to 1/n
    double sum;
    for (int j = 0; j < dimension; j++) {
        sum = 0;
        for (int i = 0; i < dimension; i++) {
            sum += s_matrix.get_value(i, j);
        }
        if (sum == 0) {
            for (int i = 0; i < dimension; i++) {
                s_matrix.set_value(i, j, (double) 1 / dimension);
            }
        } else {
            for (int i = 0; i < dimension; i++) {
                double val = s_matrix.get_value(i, j);

                if (s_matrix.get_value(i, j) != 0) {
                    s_matrix.set_value(i, j, val / sum);
                }
            }
        }
    }
    return s_matrix;
}

Matrix GoogleRank::get_m_matrix(const Matrix& s_matrix) {
    Matrix matrix1(dimension);
    Matrix matrix2(dimension);
    Matrix q_matrix(dimension);

    // making identity matrix for p_value, 1-p_value and Q matrix
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (i == j) {
                matrix1.set_value(i, j, P_VALUE);
                matrix2.set_value(i, j, 1 - P_VALUE);
            }
            q_matrix.set_value(i, j, (double) 1 / dimension);
        }
    }

    // formula input
    Matrix m_matrix = (matrix1 * s_matrix) + (matrix2 * q_matrix);
    return m_matrix;
}

Matrix GoogleRank::get_rank_matrix(const Matrix& m_matrix) {
    Matrix rank_matrix = Matrix(dimension, 1);

    //making rank matrix first setting the values to 1
    for (int i = 0; i < dimension; i++) {
        rank_matrix.set_value(i, 0, 1);
    }


    //store the first new rank matrix value and old rank matrix value
    Matrix temp_matrix = rank_matrix;
    rank_matrix = m_matrix * rank_matrix;

    //continue to update the rank matrix until the values converge
    while (rank_matrix != temp_matrix) {
        temp_matrix = rank_matrix;
        rank_matrix = m_matrix * rank_matrix;
    }

    //getting the final sum to divide
    double final_sum = 0;
    for (int i = 0; i < dimension; i++) {
        final_sum += rank_matrix.get_value(i, 0);
    }

    // divide rank matrix by final sum
    Matrix matrix_sum(dimension);
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (i == j) {
                matrix_sum.set_value(i, j, (double) 1 / final_sum);
            }
        }
    }

    rank_matrix = matrix_sum * rank_matrix;

    return rank_matrix;
}


void GoogleRank::printResult(Matrix& rank_matrix) {
    // print the percentage of each element in rank matrix
    for (int i = 0; i < dimension; i++) {
        cout << "Page " << (char)(INT_CONVERTER_VAL + i) << ": ";
        cout << setw(7) << setprecision(2) << fixed << rank_matrix.get_value(i, 0) * 100 << "%" << endl;
    }
}

