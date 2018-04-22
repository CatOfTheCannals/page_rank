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

typedef map<int, double>::const_iterator it_s_vec;
typedef map<int, double> vec;
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

	Sparse_matrix(const Sparse_matrix & other) = default;
	/*
	Sparse_matrix(const Sparse_matrix & other) : _rows(other._rows), _cols(other._cols) {
		std::cout << "copying:" << std::endl;
		s_matrix _matrix(other._matrix);
		for (it_s_matrix row_it= other._matrix.begin(); row_it!=other._matrix.end(); ++row_it){
			//_matrix[row_it->first] = row_it->second;
			vec current_row;
			for (it_s_vec vec_it=(row_it->second).begin(); vec_it!=(row_it->second).end(); ++vec_it) {
				std::cout << vec_it->second << " ";
				current_row[vec_it->first] = vec_it->second;
			}
			_matrix[row_it->first] = current_row;
			std::cout << std::endl;
			// std::cout << row_it->first << std::endl;
			// std::cout << _matrix[row_it->first][0] << std::endl;

		}
	}
	*/

    int rows() const;
    int cols() const;
    int size() const;
	s_matrix matrix() const;
    double operator()(std::size_t row_idx, std::size_t col_idx) const;
    double operator()(std::size_t idx) const;
    void setIndex(int i, int j, double value);
    map<int, double> column( std::size_t col_idx); //devuelve la columna/fila  col_idx si está definida 
    
    Sparse_matrix operator+(const Sparse_matrix matrix) const;
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

	tuple<int, int> maxCoeff(const Sparse_matrix a);

    Sparse_matrix abs() const;

    bool isApproximate(const Sparse_matrix b, double epsilon) const;

private:

    bool map_of_rows;
    double epsilon;

    int _rows;
    int _cols;
    s_matrix _matrix;
};

#endif //__DYN_MATRIX_HPP__}

