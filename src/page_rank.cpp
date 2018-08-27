#include "page_rank.h"


Matrix page_rank(Matrix W, Matrix C, double p) {
    assert(W.rows() == W.cols());
    assert(W.rows() == C.rows());
    assert(W.cols() == C.cols());

    Matrix id = Matrix::identity(W.rows());

    Matrix e = onesVec(W.rows());

    auto begin = GET_TIME;
    Matrix W_mult_Cp = W.multiply(C * (-p));
    auto end = GET_TIME;
    std::cout << "matmul time: " << GET_TIME_DELTA(begin, end) << std::endl;

    begin = GET_TIME;
    Matrix A = id + W_mult_Cp;
    end = GET_TIME;
    std::cout << "matadd time: " << GET_TIME_DELTA(begin, end) << std::endl;

    Matrix L(W.rows(), W.cols());
    Matrix U(W.rows(), W.cols());

    begin = GET_TIME;
    Matrix y = forward_sub(L, e);
    end = GET_TIME;
    std::cout << "forward sub time: " << GET_TIME_DELTA(begin, end) << std::endl;

    begin = GET_TIME;
    Matrix x = backward_sub(U, y);
    end = GET_TIME;
    std::cout << "forward sub time: " << GET_TIME_DELTA(begin, end) << std::endl;

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
    assert(column.cols() == 1);
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

Matrix onesVec(const int n){
    Matrix e(n, 1);
    for(int i = 0; i < e.rows(); i++) { //llenar e de unos
        e.setIndex(i, 0, 1);
    }
    return e;
}
