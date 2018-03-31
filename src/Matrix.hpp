#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Matrix {
public:
    Matrix(int rows, int columns);
    int rowSize() const;  //fixme: chequear si los getters van en public, creo que si
    int columnSize() const;
    int size() const;
    bool isTransposed() const;
    double operator()(std::size_t row_idx, std::size_t col_idx) const;
    double getPosition(int i, int j) const;
    void setIndex(int i, int j, double value); //fixme: completaro
    void operator+(Matrix matrix);
    //void operator=(Matrix matrix); //TODO: este operador es dificil de hacer porque las matrices están hechas con arrays y va a costar modificar los tamaños.
    void transpose();



private:
    int _rows;
    int _cols;
    int _size; //it's convenient to have the size stored appart for different operations.
    double *_matrix; //pointer of type int to the location of the matrix.
    bool _transposed;
};

// Constructor of Matrix Class initallized with 0 on every position.
Matrix::Matrix(int rows, int columns) : _rows(rows), _cols(columns){ //fixme: no se para que hago lo que hago dps de los dos puntos, creo que con las sgtes dos líneas,  no es necesario.
    _rows = rows;
    _cols = columns;
    int size = rows * columns; //fixme: ver si se puede juntar todo en la siguiente línea.
    _size = size;
    _transposed = false;
    _matrix = new double[size]();  // dynamically allocates memory using new
    for (int i= 0; i < size; ++i) {
        _matrix[i] = 0;
    }
}

int Matrix::rowSize() const{
    if (!this->_transposed) {
        return _rows;
    } else {
        return _cols;
    }
}
int Matrix::columnSize() const {
    if (this->_transposed) {
        return _rows;
    } else {
        return _cols;
    }
}

int Matrix::size() const {
    return _size;
}

bool Matrix::isTransposed() const {
    return _transposed;
}
std::ostream& operator<<(std::ostream& o, const Matrix& a)
{
    for (std::size_t i = 1; i <= a.rowSize(); i++) {
        for (std::size_t j = 1; j <= a.columnSize(); j++) {
            o << a.getPosition(i, j) << ' ';
        }
        if (!(i / a.rowSize())) {
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


void Matrix::setIndex(int i, int j, double value){
    if(0 <= i < this->_rows && 0 <= j < this->_cols){
        int position = this->_cols * i + j;
        this->_matrix[position] = (int) value; //TODO: no deja agregar un float, creo que tiene que ver con el private _matrix.
    }
}

void Matrix::operator+(Matrix matrix) { //takes two matrices of the same size and makes the summ and stores it on the first one //todo: chequear comentario.
    if(this->_cols !=  matrix.columnSize() || this->_rows != matrix.rowSize()){ //TODO: may be it would be more interesting if the sum isn't stored on the first matrix.
        cout << "the sum is not possible" << endl; //fixme: check the cout message.
    } else {
        for(int i=1; i <= this->rowSize(); ++i){
            for(int j=1; j <= this->_cols; ++j){
                this->setIndex(i, j, this->getPosition(i, j) + matrix.getPosition(i, j));
            }
        }
    }
}


void Matrix::transpose() {
    this->_transposed  = true;
};


#endif //__DYN_MATRIX_HPP__}

