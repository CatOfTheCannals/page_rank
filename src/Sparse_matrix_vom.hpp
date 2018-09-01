#ifndef TP1_METODOS_SPARSE_MATRIX_vom_H
#define TP1_METODOS_SPARSE_MATRIX_vom_H

#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include <tuple>
#include <map>
#include <math.h>

#include "chrono"

#define GET_TIME std::chrono::high_resolution_clock::now()
#define GET_TIME_DELTA(begin, end) \
     std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()

using namespace std;

typedef map<int, double>::const_iterator it_s_vec;
typedef map<int, double> s_vec;
typedef vector<map<int, double> >::iterator it_s_matrix;
typedef vector<map<int, double>> s_matrix;

class Sparse_matrix_vom {
public:
    // Constructor of Sparse_matrix_vom Class initallized with 0 on every position.
    Sparse_matrix_vom(int rows, int cols) {
        _rows = rows;
        _cols = cols;
        _matrix = s_matrix(_rows);
    }

    Sparse_matrix_vom(int rows, int cols, s_matrix matrix) {
        _rows = rows;
        _cols = cols;
        _matrix = matrix;
    }

    Sparse_matrix_vom(const Sparse_matrix_vom & other) = default;

    int rows() const;
    int cols() const;
    double operator()(int row_idx, int col_idx) const;
    double operator()(int idx) const;
    void setIndex(int i, int j, double value);
    Sparse_matrix_vom operator+(const Sparse_matrix_vom& m) const;
    Sparse_matrix_vom operator*(const double& scalar) const; //scalar multiplication
    bool operator==(const Sparse_matrix_vom& other) const;
    void swapRows(int i1, int i2);
    Sparse_matrix_vom getRow(int index) const;
    friend std::ostream& operator<<(std::ostream& o, const Sparse_matrix_vom& a);
    Sparse_matrix_vom subMatrix(int i1, int i2, int j1, int j2) const;
    Sparse_matrix_vom multiply(const Sparse_matrix_vom& b) const;
    Sparse_matrix_vom transpose() const;
    friend double dotProd(const Sparse_matrix_vom& u, const Sparse_matrix_vom& w);
    static Sparse_matrix_vom identity(int n);
    std::tuple<int, int> maxCoeff();
    Sparse_matrix_vom abs();
    bool isApproximate(const Sparse_matrix_vom b) const;
    bool is_significant(double value);

    static Sparse_matrix_vom random_matrix(int height, int width);

    /*
    std::tuple<int, int> shape() const;
    Sparse_matrix_vom multiply(const Sparse_matrix_vom b);
    static Sparse_matrix_vom identity(int n);

    std::tuple<int, int> maxCoeff();
    friend std::ostream& operator<<(std::ostream& o, const Sparse_matrix_vom& a);
    bool isApproximate(const Sparse_matrix_vom b, double epsilon) const;
     */



private:
    int _rows;
    int _cols;
    s_matrix _matrix; //pointer of type int to the location of the Sparse_matrix_vom.
    double _epsilon = 0.000001;

};



#endif //TP1_METODOS_SPARSE_MATRIX_vom_H
