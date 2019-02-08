

#include "googleRank.hpp"

using namespace std;

int main() {


    Matrix s_matrix;
    Matrix m_matrix;
    Matrix rank_matrix;

    GoogleRank googleRank;


    s_matrix = googleRank.get_s_matrix();

    m_matrix = googleRank.get_m_matrix(s_matrix);

    rank_matrix = googleRank.get_rank_matrix(m_matrix);



    googleRank.printResult(rank_matrix);




    return 0;
}