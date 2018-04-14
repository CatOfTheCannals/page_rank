
#include "page_rank.h"


Matrix page_rank(Matrix W, Matrix C, double p) {
    assert(W.rows() == W.cols());
    assert(W.rows() == C.rows());
    assert(W.cols() == C.cols());

    Matrix id = Matrix::identity(W.rows());
    Matrix e(W.rows(), 1);
    for(int i = 0; i < e.rows(); i++) { //llenar e de unos
        e.setIndex(i, 0, 1);
    }

    Matrix A = id + W.multiply(C * (-p)) ;

    Matrix L(W.rows(), W.cols());
    Matrix U(W.rows(), W.cols());
    std::tie(L, U) = gauss_elimination(A);

    Matrix y = forward_sub(L, e);
    Matrix x = backward_sub(U, y);

    return x * normalization_coeff(x);

}

double normalization_coeff(Matrix column) {
    assert((column.cols() == 1));

    double sum = 0;

    for(int i = 0; i < column.rows(); i++) {
        sum += column(i,0);
    }
    return 1 / sum;
}