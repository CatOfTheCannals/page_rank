#ifndef __SPARSE_MATRIX_HPP__
#define __SPARSE_MATRIX_HPP__

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <assert.h>
#include <tuple>
#include <map>

using namespace std;

typedef map<int, map<int, double> >::const_iterator it_s_matrix;
typedef map<int, map<int, double> > s_matrix;

class Sparse_matrix { // la primer posicion de la matriz es el 1,1
public:
    // Constructor of Sparse Sparse_matrix Class
    Sparse_matrix(int rows, int cols) {

	_rows = rows;
	_cols = cols;
	s_matrix _matrix;
    }

    int rows() const;
    int cols() const;
    int size() const;
	s_matrix matrix() const;
    double operator()(std::size_t row_idx, std::size_t col_idx) const;
    double operator()(std::size_t idx) const;
    void setIndex(int i, int j, double value);
    map<int, double> column( std::size_t col_idx); //devuelve la columna/fila  col_idx si está definida 
    
    Sparse_matrix operator+(const Sparse_matrix matrix) const;
    Sparse_matrix operator=(const Sparse_matrix other );
	Sparse_matrix operator*(const double& scalar) const; //scalar multiplication
    Sparse_matrix transpose() const;
    void swapRows(int i1, int i2);
    Sparse_matrix getRow(int index);
    void setRow (int index, map<int, double> row);

    static Sparse_matrix identity(int n);
    void multColByScalar(std::size_t col_idx, double scalar);
    void preMultiplyByDiagMatrix(const vector<double> v);
    
	Sparse_matrix subMatrix(int i1, int i2, int j1, int j2);
	std::tuple<int, int> shape() const;
	
	Sparse_matrix multiply(const Sparse_matrix b);

    friend std::ostream& operator<<(std::ostream& o, const Sparse_matrix& a);

    bool operator==(const Sparse_matrix& other) const;

	tuple<int, int> maxCoeff(const Sparse_matrix a) ;

private:

    bool map_of_rows;
    double epsilon;

    int _rows;
    int _cols;
    s_matrix _matrix;
};

#endif //__DYN_MATRIX_HPP__}

