//
 // Created by juan on 24/03/18.
//
#include <iostream>
#include <vector>

using namespace std;

class Matrix {
public:
    Matrix(int rows, int columns);
    int rowSize() const;  //fixme: chequear si los getters van en public, creo que si
    int columnSize() const;
    int size() const;
    void printarray (int matrix[]);
    double getPosition(int i, int j);
    void setAt (Matrix matrix, int column, int row, double value); //fixme: completaro
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


void Matrix::printarray (int matrix[]) {
    for (int i = 0; i < this->size(); ++i) {
        cout << matrix[i] << " | ";
        if (i % this->rowSize() == 0) {
            cout << endl;
        }
    }
}
