
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

    Matrix A = id + W.multiply(C * (-p));

    Matrix L(W.rows(), W.cols());
    Matrix U(W.rows(), W.cols())

    Matrix y = forward_sub(L, e);
    Matrix x = backward_sub(U, y);

    /*
    std::cout << "C" << std::endl;
    std::cout << C << std::endl;
    std::cout << "W" << std::endl;
    std::cout << W << std::endl;

    Matrix A = id + W.multiply(C * (-p));

    std::cout << "A" << std::endl;
    std::cout << A << std::endl;


    Matrix L(W.rows(), W.cols());
    Matrix U(W.rows(), W.cols());
    std::tie(L, U) = gauss_elimination(A);

    std::cout << "L" << std::endl;
    std::cout << L << std::endl;
    std::cout << "U" << std::endl;
    std::cout << U << std::endl;

    Matrix y = forward_sub(L, e);
    Matrix x = backward_sub(U, y);

    std::cout << "y" << std::endl;
    std::cout << y << std::endl;
    std::cout << "x" << std::endl;
    std::cout << x << std::endl;
    */
    
    return x * normalization_coeff(x);

    /*
    auto res =  x * normalization_coeff(x);

    std::cout << A.multiply(res) + res * -1 << std::endl;

    return res
    */
}

double normalization_coeff(Matrix column) {
    assert((column.cols() == 1));

    double sum = 0;

    for(int i = 0; i < column.rows(); i++) {
        sum += column(i,0);
    }
    return 1 / sum;
}


Matrix colSumDiag(const Matrix& W){
    Matrix C(W.rows(), W.cols());
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