#include "sparse_page_rank.h"

Sparse_matrix_2 page_rank(Sparse_matrix_2 W, Sparse_matrix_2 C, double p) {
    assert(W.rows() == W.cols());
    assert(W.rows() == C.rows());
    assert(W.cols() == C.cols());

    Sparse_matrix_2 id = Sparse_matrix_2::identity(W.rows());

    Sparse_matrix_2 e = onesVec(W.rows());

    Sparse_matrix_2 A = id + W.multiply(C * (-p));

    Sparse_matrix_2 L(W.rows(), W.cols());
    Sparse_matrix_2 U(W.rows(), W.cols());

    Sparse_matrix_2 y = forward_sub(L, e);
    Sparse_matrix_2 x = backward_sub(U, y);

    /*
    std::cout << "C" << std::endl;
    std::cout << C << std::endl;
    std::cout << "W" << std::endl;
    std::cout << W << std::endl;

    Sparse_matrix_2 A = id + W.multiply(C * (-p));

    std::cout << "A" << std::endl;
    std::cout << A << std::endl;


    Sparse_matrix_2 L(W.rows(), W.cols());
    Sparse_matrix_2 U(W.rows(), W.cols());
    std::tie(L, U) = s_gauss_elimination(A);

    std::cout << "L" << std::endl;
    std::cout << L << std::endl;
    std::cout << "U" << std::endl;
    std::cout << U << std::endl;

    Sparse_matrix_2 y = forward_sub(L, e);
    Sparse_matrix_2 x = backward_sub(U, y);

    std::cout << "y" << std::endl;
    std::cout << y << std::endl;
    std::cout << "x" << std::endl;
    std::cout << x << std::endl;
     */

    return x * normalization_coeff(x);

    /*
    auto res =  x * normalization_coeff(x);

    // std::cout << A.multiply(res) + res * -1 << std::endl;

    return res
    */
}

double normalization_coeff(Sparse_matrix_2 column) {
    assert(column.cols() == 1);
    double sum = 0;
    for(int i = 0; i < column.rows(); i++) {
        sum += column(i,0);
    }
    return 1 / sum;
}


Sparse_matrix_2 colSumDiag(const Sparse_matrix_2& W){
    Sparse_matrix_2 C(W.rows(), W.cols());
    for(int j = 0; j < W.cols(); j ++){
        double sum = 0;
        for(int i = 0; i < W.rows(); i ++){
            sum += W(i,j);
        }
        if(sum != 0){
            C.setIndex(j,j,1/sum);
        }
    }
    return C;
}

Sparse_matrix_2 onesVec(const int n){
    Sparse_matrix_2 e(n, 1);
    for(int i = 0; i < e.rows(); i++) { //llenar e de unos
        e.setIndex(i, 0, 1);
    }
    return e;
}
