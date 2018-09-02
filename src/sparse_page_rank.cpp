#include "sparse_page_rank.h"

Sparse_matrix_vom page_rank(Sparse_matrix_vom &W, Sparse_matrix_vom &C, double p) {
    assert(W.rows() == W.cols());
    assert(W.rows() == C.rows());
    assert(W.cols() == C.cols());

    Sparse_matrix_vom id = Sparse_matrix_vom::identity(W.rows()); // O(n)

    Sparse_matrix_vom e = onesVec(W.rows()); // O(n)

    /*
    Sparse_matrix_vom W_mult_Cp = W.multiply(C * (-p));

    Sparse_matrix_vom A = id + W_mult_Cp;

    Sparse_matrix_vom L(W.rows(), W.cols());
    Sparse_matrix_vom U(W.rows(), W.cols());

    std::tie(L, U) = s_gauss_elimination(A);

    Sparse_matrix_vom y = forward_sub(L, e);

    Sparse_matrix_vom x = backward_sub(U, y);

    return x * normalization_coeff(x); // O(n)

*/
    auto begin = GET_TIME;
    Sparse_matrix_vom W_mult_Cp = W.multiply(C * (-p));
    auto end = GET_TIME;
    std::cout << "'matmul_time': " << GET_TIME_DELTA(begin, end) << std::endl;


    begin = GET_TIME;
    Sparse_matrix_vom A = id + W_mult_Cp;
    end = GET_TIME;
    std::cout << "'matadd_time': " << GET_TIME_DELTA(begin, end) << std::endl;

    //Sparse_matrix_vom L(W.rows(), W.cols());
    Sparse_matrix_vom U(W.rows(), W.cols());
    /*
    begin = GET_TIME;
    std::tie(L, U) = s_gauss_elimination(A);
    end = GET_TIME;
    std::cout << "'gauss_elim_time': " << GET_TIME_DELTA(begin, end) << std::endl;

    begin = GET_TIME;
    Sparse_matrix_vom y = forward_sub(L, e);
    end = GET_TIME;
    std::cout << "'forward_sub_time': " << GET_TIME_DELTA(begin, end) << std::endl;
    */
    U = gauss_elimination_write_and_u(A, e);
    begin = GET_TIME;
    Sparse_matrix_vom x = backward_sub(U, e);
    end = GET_TIME;
    std::cout << "'backward_back_time': " << GET_TIME_DELTA(begin, end) << std::endl;

    return x * normalization_coeff(x); // O(n)
/*
    std::cout << "C" << std::endl;
    std::cout << C << std::endl;
    std::cout << "W" << std::endl;
    std::cout << W << std::endl;

    Sparse_matrix_vom A = id + W.multiply(C * (-p));

    std::cout << "A" << std::endl;
    std::cout << A << std::endl;

    Sparse_matrix_vom L(W.rows(), W.cols());
    Sparse_matrix_vom U(W.rows(), W.cols());
    std::tie(L, U) = s_gauss_elimination(A);

    std::cout << "L" << std::endl;
    std::cout << L << std::endl;
    std::cout << "U" << std::endl;
    std::cout << U << std::endl;

    Sparse_matrix_vom y = forward_sub(L, e);
    Sparse_matrix_vom x = backward_sub(U, y);

    std::cout << "y" << std::endl;
    std::cout << y << std::endl;
    std::cout << "x" << std::endl;
    std::cout << x << std::endl;

    return x * normalization_coeff(x); // O(n)


    auto res =  x * normalization_coeff(x);

    std::cout << "res " << res << std::endl;

    //std::cout << "solution: " << A.multiply(res) + res * -1 << std::endl;

    return res; */
}

double normalization_coeff(Sparse_matrix_vom &column) {
    assert(column.cols() == 1);
    double sum = 0;
    for(int i = 1; i <= column.rows(); i++) {
        sum += column(i,1);
    }
    return 1 / sum;
}


Sparse_matrix_vom colSumDiag(const Sparse_matrix_vom &W){ //O(n^2)
    Sparse_matrix_vom C(W.rows(), W.cols());
    for(int j = 1; j <= W.cols(); j ++){
        double sum = 0;
        for(int i = 1; i <= W.rows(); i ++){
            sum += W(i,j);
        }
        if(sum != 0){
            C.setIndex(j,j,1/sum);
        }
    }

    return C;
}

Sparse_matrix_vom onesVec(const int n){
    Sparse_matrix_vom e(n, 1);
    for(int i = 1; i <= e.rows(); i++) { //llenar e de unos
        e.setIndex(i, 1, 1);
    }
    return e;
}
