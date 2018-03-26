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
    void printarray (int matrix[]);
    double getPosition(int i, int j) const;
    void setAt (int i, int j, double value); //fixme: completaro
    void addMatrix (Matrix matrix);

private:
    int _rows;
    int _columns;
    int _size; //it's convenient to have the size stored appart for different operations.
    int *_matrix; //pointer of type int to the location of the matrix.
};

// Constructor of Matrix Class initallized with 0 on every position.
Matrix::Matrix(int rows, int columns) : _rows(rows), _columns(columns){ //fixme: no se para que hago lo que hago dps de los dos puntos, creo que con las sgtes dos líneas,  no es necesario.
    _rows = rows;
    _columns = columns;
    int size = rows * columns; //fixme: ver si se puede juntar todo en la siguiente línea.
    _size = size;
    _matrix = new int[size]();  // dynamically allocates memory using new
    for (int i= 0; i < size; ++i) {
        _matrix[i] = 0;
    }
}

int Matrix::rowSize() const{
    return _rows;
}
int Matrix::columnSize() const {
    return _columns;
}
int Matrix::size() const {
    return _size;
}

std::ostream& operator<<(std::ostream& o, const Matrix& a)
{
    for (std::size_t i = 1; i <= a.rowSize(); i++) {
        for (std::size_t j = 1; j <= a.columnSize(); j++) {
            o << a.getPosition(i, j);
        }
        if( !(i / a.rowSize()) )
        {
            o << endl;
        }
    }
    return o;
}


double Matrix::getPosition(int i, int j) const { // TODO: pasar las condiciones del if a un assert
    int row = i - 1;
    int column = j - 1;
    int position = this->_columns * row + column; //TODO: esta función se va a usar muchas veces, considerar si tiene sentido hacer que sea un método.
    if(i <= this->_rows && j <= this->_columns && i*j <= this->_size) //TODO: creo que no es necesario preguntar que i*j sea menor a size. Creo que es necesario que i y j sean menores o Iguales, esto cuando las matrices tengan como posicion inicial el (1,1).
    {
        return this->_matrix[position];
    } else {
        cout << "position out of range" <<endl;
        return 0; //TODO: este cero queda feo.
    }
}

void Matrix::setAt (int i, int j, double value){
    int row = i - 1;
    if(0 < i < this->_rows && 0 < j < this->_columns){
        int position = this->_columns * (row) + j;
        _matrix[position] = (int) value; //TODO: no deja agregar un float, creo que tiene que ver con el private _matrix.
    }
}


#endif //__DYN_MATRIX_HPP__}
