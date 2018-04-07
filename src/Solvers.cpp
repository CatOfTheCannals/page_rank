#include "Solvers.hpp"


Matrix gauss_elimination(const Matrix& a)
{
    int rows_a, cols_a;
    std::tie(rows_a, cols_a) = a.shape();
    auto x = a;
    for (int i = 0; i < a.rows(); i++) {
        //find max coeff
        Matrix current_col = x.subMatrix(i, rows_a - 1, i, i);
        int max_coeff = std::get<0>(current_col.abs().maxCoeff());

        if (current_col(max_coeff) != 0) {
            //swap it
            x.swapRows(i, max_coeff + i);

            //divide current row and lower rows by their "principal" component
            for (int r = i; r < rows_a; r++) {
                if (x(r,i) != 0){
                    double coef = x(r, i);
                    for (int c = i; c < cols_a; c++) {
                        x.setIndex(r, c, x(r, c) / coef);
                    }
                }
            }

            //subtract current row to every lower row
            for (int r = i + 1; r < rows_a; r++) {
                if (x(r,i) != 0){
                    for (int c = i; c < cols_a; c++) {
                        x.setIndex(r, c, x(r, c) - x(i, c));
                    }
                }
            }

        }

    }
    return x;
    //return x.subMatrix(0, 0, rows_a - 1, rows_a -1);
}