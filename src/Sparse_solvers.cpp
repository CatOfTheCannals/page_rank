#include "Sparse_solvers.hpp"
#include "Sparse_matrix_vom.hpp"

std::tuple<Sparse_matrix_vom, Sparse_matrix_vom> s_gauss_elimination(const Sparse_matrix_vom& a) {
    assert(a.cols() == a.rows());
    auto u = a;

    Sparse_matrix_vom l(a.rows(), a.cols());

    for (int i = 1; i < a.cols(); i++) { //n veces

        //find max coeff
        /*
        Sparse_matrix_vom current_col = u.subMatrix(i , a.rows(), i , i); // vector of size i
        int max_coeff = std::get<0>(current_col.abs().maxCoeff());

        if (current_col(max_coeff) != 1) { // O(1)
            //swap it
            u.swapRows(i, max_coeff + i - 1);
            l.swapRows(i, max_coeff + i - 1);
        } 
		*/
        for (int r = i + 1; r <= a.rows(); r++) { //n - i 
            if (u(r,i) != 0) {
                double rowMultiplicator = u(r,i) / u(i, i);
                l.setIndex(r, i, rowMultiplicator);
                for (int c = i; c <= a.cols(); c++) { // O(n)
                    u.setIndex(r, c, u(r, c) - (u(i, c) * rowMultiplicator));
                }
            }
        }

    }
    Sparse_matrix_vom id = Sparse_matrix_vom::identity(a.rows());
    l = l + id;
    return std::make_tuple(l, u);
}

Sparse_matrix_vom gauss_elimination_write_and_u(Sparse_matrix_vom& a, Sparse_matrix_vom& e) {
    assert(a.cols() == a.rows());

    //Sparse_matrix_vom l(a.rows(), a.cols());

    for (int i = 1; i < a.rows(); i++) { //n veces
        auto begin = GET_TIME;
        //find max coeff
        /*
        Sparse_matrix_vom current_col = u.subMatrix(i , a.rows(), i , i); // vector of size i
        int max_coeff = std::get<0>(current_col.abs().maxCoeff());

        if (current_col(max_coeff) != 1) { // O(1)
            //swap it
            u.swapRows(i, max_coeff + i - 1);
            l.swapRows(i, max_coeff + i - 1);
        }
		*/
        double diag = a(i, i);
        for (int r = i + 1; r <= a.rows(); r++) { //n - i
            double num = a(r,i);

            if ( a.is_significant(num) ) {
                double rowMultiplicator = num / diag;
                //l.setIndex(r, i, rowMultiplicator);
                for (int c = i; c <= a.cols(); c++) { // O(n)
                    a.substract(r, c, a(i, c) * rowMultiplicator);
                }
                double w = e(i)*rowMultiplicator;
                e.substract_vector(r, w);
            }

			}
        if(i%100 ==0){
        auto end = GET_TIME;
        cout << "'row_time': " << GET_TIME_DELTA(begin, end) << endl;
        cout << "i: "<< i <<endl;}

    }

    //Sparse_matrix_vom id = Sparse_matrix_vom::identity(a.rows());
    //l = l + id;
    return a;
}

Sparse_matrix_vom backward_sub(const Sparse_matrix_vom& a, const Sparse_matrix_vom& y) {
    assert(a.rows() == a.cols() && a.cols() == y.rows() && y.cols() == 1);
    Sparse_matrix_vom x(a.rows(), 1);

    for (int i = a.rows() ; i > 0; i--) {
        if(a(i,i) != 0) { // TODO: checkear si esta bien no hacer nada en este paso
            auto temp_row = a.subMatrix(i, i, i, a.cols()); // la complejidad depende de cuantos elementos no nulos hay aca
            // dificil relacionar los elementos no nulos de LU con m
            auto temp_col = x.subMatrix(i, y.rows() , 1, 1);
            double temp_coeff = temp_row.multiply(temp_col)(1,1);

            x.setIndex(i, 1, (y(i, 1) - temp_coeff) / a(i,i));
        }
    }

    return x;
}

Sparse_matrix_vom forward_sub(const Sparse_matrix_vom& a, const Sparse_matrix_vom& y) {
    assert(a.rows() == a.cols() && a.cols() == y.rows() && y.cols() == 1);
    Sparse_matrix_vom x(a.rows(), 1);

    for (int i = 1; i <= a.rows() ; i++) {
        if(a(i,i) != 0) { // TODO: checkear si esta bien no hacer nada en este paso
            auto temp_row = a.subMatrix(i, i, 1, i);
            auto temp_col = x.subMatrix(1, i, 1, 1);
            double temp_coeff = temp_row.multiply(temp_col)(1,1);
            x.setIndex(i, 1, (y(i, 1) - temp_coeff) / a(i,i));
        }

    }
    return x;
}

