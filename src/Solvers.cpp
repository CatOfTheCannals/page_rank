#include "Solvers.hpp"


std::tuple<Matrix, Matrix> gauss_elimination(const Matrix& a)
{
    assert(a.cols() == a.rows());
    auto u = a;
    Matrix l(a.rows(), a.cols());

    for (int i = 0; i < a.cols(); i++) {
        //find max coeff
        Matrix current_col = u.subMatrix(i, a.rows() - 1, i, i);
        int max_coeff = std::get<0>(current_col.abs().maxCoeff());

        if (current_col(max_coeff) != 0) {
            //swap it
            u.swapRows(i, max_coeff + i);
            l.swapRows(i, max_coeff + i);
            for (int r = i + 1; r < a.rows(); r++) {
                if (u(r,i) != 0){
                    double rowMultiplicator = u(r,i) / u(i, i);
                    l.setIndex(r, i, rowMultiplicator);
                    for (int c = i; c < a.cols(); c++) {
                        u.setIndex(r, c, u(r, c) - (u(i, c) * rowMultiplicator));
                    }
                }
            }

        }
    }
    Matrix id = Matrix::identity(a.rows());
    l = l + id;
    return std::make_tuple(l, u);
}

Matrix backward_sub(const Matrix& a, const Matrix& y)
{
    int rows_a, cols_a, rows_y, cols_y;
    std::tie(rows_a, cols_a) = a.shape();
    std::tie(rows_y, cols_y) = y.shape();
    assert(rows_a == cols_a && rows_a == rows_y && cols_y == 1);

    Matrix x(rows_a, 1);

    for (int i = rows_a - 1; i >= 0; i--) {

        if(a(i,i) != 0) { // TODO: checkear si esta bien no hacer nada en este paso
            auto temp_row = a.subMatrix(i, i, i, cols_a - 1);
            auto temp_col = x.subMatrix(i, rows_y - 1, 0, 0);
            double temp_coeff = temp_row.multiply(temp_col)(0,0);
            x.setIndex(i, 0, (y(i, 0) - temp_coeff) / a(i,i));
        }
    }

    return x;
}

Matrix forward_sub(const Matrix& a, const Matrix& y)
{
    int rows_a, cols_a, rows_y, cols_y;
    std::tie(rows_a, cols_a) = a.shape();
    std::tie(rows_y, cols_y) = y.shape();
    assert(rows_a == cols_a && rows_a == rows_y && cols_y == 1);

    Matrix x(rows_a, 1);

    for (int i = 0; i < rows_a ; i++) {
        if(a(i,i) != 0) { // TODO: checkear si esta bien no hacer nada en este paso
            auto temp_row = a.subMatrix(i, i, 0, i);
            auto temp_col = x.subMatrix(0, i, 0, 0);
            double temp_coeff = temp_row.multiply(temp_col)(0,0);
            x.setIndex(i, 0, (y(i, 0) - temp_coeff) / a(i,i));
        }

    }
    return x;
}