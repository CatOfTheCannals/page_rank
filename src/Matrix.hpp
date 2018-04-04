#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include <tuple>

using namespace std;

class Matrix {
public:
    // Constructor of Matrix Class initallized with 0 on every position.
    Matrix(int rows, int columns) : _rows(rows), _cols(columns){ //fixme: no se para que hago lo que hago dps de los dos puntos, creo que con las sgtes dos líneas,  no es necesario.
        _rows = rows;
        _cols = columns;
        _matrix = new double[_rows*_cols]();  // dynamically allocates memory using new
        for (int i= 0; i < _rows*_cols; ++i) {
            _matrix[i] = 0;
        }
    }

    Matrix(const Matrix & other) : _rows(other._rows), _cols(other._cols)
    {
        const int arr_size = _rows * _cols;
        _matrix = new double[arr_size];
        std::copy(other._matrix, other._matrix + arr_size, _matrix);
    }

    int rows() const;
    int cols() const;
    int size() const;
    double operator()(std::size_t row_idx, std::size_t col_idx) const;
    double operator()(std::size_t idx) const;
    void setIndex(int i, int j, double value); //fixme: completaro
    void operator+(Matrix matrix);
    void operator*(double scalar); //scalar multiplication
    void transpose();
    void swapRows(int i1, int i2);
    Matrix getRow(int index);
    std::tuple<int, int> shape() const;
    bool operator==(const Matrix& other) const;
    Matrix subMatrix(int i1, int i2, int j1, int j2);



private:
    int _rows;
    int _cols;
    double *_matrix; //pointer of type int to the location of the matrix.
};



int Matrix::rows() const{
        return _rows;
}

int Matrix::cols() const {
        return _cols;
}

int Matrix::size() const {
    return _rows * _cols;
}

std::ostream& operator<<(std::ostream& o, const Matrix& a)
{
    for (std::size_t i = 0; i < a.rows(); i++) {
        for (std::size_t j = 0; j < a.cols(); j++) {
            o << a(i, j) << ' ';
        }
        if (!(i / a.rows())) {
            o << endl;
        }
    }
    return o;

}

double Matrix::operator()(std::size_t row_idx, std::size_t col_idx) const
{
    assert(row_idx < this->_rows && col_idx < this->_cols);
    std::size_t idx = row_idx * this->_cols + col_idx;
    return this->_matrix[idx];
}

double Matrix::operator()(std::size_t idx) const
{
    assert(this->_rows == 1 || this->_cols == 1);
    assert(idx < std::max(this->_rows, this->_cols));
    return this->_matrix[idx];
}


void Matrix::setIndex(int i, int j, double value){
    if(0 <= i < this->_rows && 0 <= j < this->_cols){
        int position = this->_cols * i + j;
        this->_matrix[position] = value;
    }
}

void Matrix::operator+(Matrix matrix) {
    assert(this->_cols == matrix.cols() && this->_rows == matrix.rows());

    for(int i=0; i < this->rows(); ++i){
        for(int j=0; j < this->_cols; ++j){
            this->setIndex(i, j, (*this)(i, j) + matrix(i, j));
        }
    }

}

void Matrix::operator*(double scalar) {
    for(int i=0; i < this->rows(); ++i){
        for(int j=0; j < this->_cols; ++j){
            this->setIndex(i, j, (*this)(i, j) * scalar);
        }
    }

}


void Matrix::transpose() {
}

void Matrix::swapRows(int i1, int i2) {
    assert(i1 < _rows && i2 < _rows);
    if(i1 != i2){
        double  *tempRow = new double[_cols];
        double *start_index_1 = _matrix + i1 * _cols;
        double *end_index_1 = start_index_1 + _cols;
        double *start_index_2 = _matrix + i2 * _cols;
        double *end_index_2 = start_index_2 + _cols;

        std::copy(start_index_1, end_index_1, tempRow);
        std::cout << "tempRow:" << std::endl;
        std::cout << tempRow[0] << "\n" << std::endl;
        std::copy(start_index_2, end_index_2, start_index_1);
        std::copy(tempRow, tempRow + _cols, start_index_2);
    }
}

Matrix Matrix::getRow(int index) {
    Matrix row(1, _cols);
    for (int i= 0; i < _cols; ++i) {
        row._matrix[i] = _matrix[index * _cols + i];
    }
    return row;
}

std::tuple<int, int> Matrix::shape() const {
    return std::make_tuple(this->_rows, this->_cols);
}

bool Matrix::operator==(const Matrix& other) const{
    if (this->_rows != other.rows() || this->_cols != other.cols()) {
        return false;
    }
    else {
        for(int i = 0; i < _rows * _cols; i++){
            if(this->_matrix[i] != other._matrix[i]){
                return false;
            }
        }
    }
    return true;
}

Matrix Matrix::subMatrix(int i1, int i2, int j1, int j2 ){
    assert(i1 <= i2 && j1 <= j2);
    assert(-1 < i1 && -1 < j2);
    assert(i2 < _rows && j2 < _cols);

    int res_rows = i2 - i1 + 1;
    int res_cols = j2 - j1 + 1;

    int index;

    Matrix res(res_rows, res_cols);
    for(int i = 0; i < res_rows ; i++){
        for(int j = 0; j < res_cols ; j++){
            index = (i + i1) * _cols + j1 + j;
            res._matrix[i * res_cols + j] = _matrix[index];
        }
    }

    return res;
}

#endif //__DYN_MATRIX_HPP__}

