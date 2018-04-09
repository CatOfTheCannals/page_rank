#ifndef __SPARSE_MATRIX_HPP__
#define __SPARSE_MATRIX_HPP__

#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include <tuple>
#include <map>


extern bool map_of_rows;

using namespace std;

typedef map<int, map<int, double> >::const_iterator it_s_matrix;
typedef map<int, map<int, double> > s_matrix;

class Sparse_matrix {
public:
    // Constructor of Sparse Sparse_matrix Class
    Sparse_matrix(int websiteCount) {

	_rows = websiteCount;
	_cols = websiteCount;
	s_matrix m;
	_matrix = m;
    }

    int rows() const;
    int cols() const;
    int size() const;
    double operator()(std::size_t row_idx, std::size_t col_idx) const;
    double operator()(std::size_t idx) const;
    void setIndex(int i, int j, double value);
    map<int, double>& operator[] ( std::size_t col_idx);
    void transpose();
    void swapRows(int i1, int i2);
/*    void operator+(Sparse_matrix matrix);
    void operator*(double scalar); //scalar multiplication
    Sparse_matrix getRow(int index);
    std::tuple<int, int> shape() const;
    bool operator==(const Sparse_matrix& other) const;
    Sparse_matrix subMatrix(int i1, int i2, int j1, int j2);
    Sparse_matrix multiply(const Sparse_matrix b);
    static Sparse_matrix identity(int rows, int cols);
    std::tuple<int, int> maxCoeff(const Sparse_matrix a);
*/

private:
    int _rows;
    int _cols;
    s_matrix _matrix;
};



int Sparse_matrix::rows() const{
        return _rows;
}

int Sparse_matrix::cols() const {
        return _cols;
}

int Sparse_matrix::size() const {
    return _rows * _cols;
}

std::ostream& operator<<(std::ostream& o, const Sparse_matrix& a)
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

double Sparse_matrix::operator()(std::size_t row_idx, std::size_t col_idx) const
{	
	double val = 0.0; //si el indice no está definido en la matriz, entonces valor es cero
	assert(row_idx < this->_rows && col_idx < this->_cols);
	it_s_matrix col_it = _matrix.find(col_idx);

	if (col_it != _matrix.end()){
	
		map<int, double> requested_col =  _matrix.find(col_idx)->second;
		map<int, double>::iterator 	row_it = (requested_col).find(row_idx);
		if (row_it != requested_col.end()){

			val = requested_col.find(row_idx)->second;
		}
	}
	return val;
}


double Sparse_matrix::operator()(std::size_t idx) const
{//solo si mi matriz es un vector fila o columna
    assert(this->_rows == 1 || this->_cols == 1);
    assert(idx < std::max(this->_rows, this->_cols));
    //si tengo una sola fila, idx es el indice columna
    if (this->_rows == 1 ){return this->_matrix.find(idx)->second.find(1)->second;}
    //si tengo una sola columna, idx es el indice fila
    if (this->_cols == 1 ){return this->_matrix.find(1)->second.find(idx)->second;}
}


void Sparse_matrix::setIndex(int i, int j, double value){
	
	assert(0 <= i < this->_rows && 0 <= j < this->_cols);
    it_s_matrix col_it = _matrix.find(j);

	if (col_it != _matrix.end()){ //la columna j está definida
    
		map<int, double> requested_col =  _matrix.find(j)->second;
		map<int, double>::iterator row_it = (requested_col).find(i);
		if (row_it != requested_col.end()){ //si la fila i esta definida

			requested_col.find(i)->second= value; //seteo el valor
		}
		else{ // la fila i no está definida
			  requested_col[i]= value;
		}
	}
	else { //la columna j no está definida
		map<int, double> new_col;
		new_col[i]= value;
		_matrix[j] = new_col;
	}
}


map<int, double>& Sparse_matrix::operator[] (std::size_t col_idx){
	
	return this->_matrix.find(col_idx)->second;
	
	}

/*
void Sparse_matrix::operator+(Sparse_matrix matrix) {
	
    assert(this->_cols == matrix.cols() && this->_rows == matrix.rows());

    for(int i=0; i < this->rows(); ++i){
        for(int j=0; j < this->_cols; ++j){
            this->setIndex(i, j, (*this)(i, j) + matrix(i, j));
        }
    }
}
*/

/*

void Sparse_matrix::operator*(double scalar) {
    for(int i=0; i < this->rows(); ++i){
        for(int j=0; j < this->_cols; ++j){
            this->setIndex(i, j, (*this)(i, j) * scalar);
        }
    }

}
*/


void Sparse_matrix::transpose() {
	
	Sparse_matrix mt = Sparse_matrix(this->_rows);
	for( map<int, map<int, double> >::const_iterator it_col = this->_matrix.begin(); it_col != this->_matrix.end(); it_col++){
		for( map<int, double>::const_iterator it_row = (it_col->second).begin(); it_row != (it_col->second).end(); it_row++){
			mt.setIndex(it_col->first, it_row->first, it_row->second);
		}
	}
	this-> _matrix = mt._matrix;
}



//asumo que cuando se llama a esta función se tiene a la matriz guardada como map<idx_fila, map< idx_col, valor> >
//esto se obtiene transponiendo la matriz guardada como map<idx_col, map< idx_fila, valor> > (q es como se guarda cuando se levanta el archivo)
void Sparse_matrix::swapRows(int i1, int i2) {
	
	if(map_of_rows == 1){ 
		printf ("%s \n", "Esta función interpreta la matriz por filas, ahora están guardadas por columnas :O"); 
		assert( map_of_rows == 0);
	}
	
    assert(i1 < _rows && i2 < _rows);
    if(i1 != i2){
		
		map<int, double> fila_aux = this->_matrix[i1] ;
		
		this->_matrix[i1] = this->_matrix[i2];
		this->_matrix[i2] = fila_aux;
		
    }
}


/*
Sparse_matrix Sparse_matrix::getRow(int index) {
    Sparse_matrix row(1, _cols);
    for (int i= 0; i < _cols; ++i) {
        row._matrix[i] = _matrix[index * _cols + i];
    }
    return row;
}

std::tuple<int, int> Sparse_matrix::shape() const {
    return std::make_tuple(this->_rows, this->_cols);
}

bool Sparse_matrix::operator==(const Sparse_matrix& other) const{
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

Sparse_matrix Sparse_matrix::subMatrix(int i1, int i2, int j1, int j2 ){
    assert(i1 <= i2 && j1 <= j2);
    assert(-1 < i1 && -1 < j2);
    assert(i2 < _rows && j2 < _cols);

    int res_rows = i2 - i1 + 1;
    int res_cols = j2 - j1 + 1;

    int index;

    Sparse_matrix res(res_rows, res_cols);
    for(int i = 0; i < res_rows ; i++){
        for(int j = 0; j < res_cols ; j++){
            index = (i + i1) * _cols + j1 + j;
            res._matrix[i * res_cols + j] = _matrix[index];
        }
    }

    return res;
}

Sparse_matrix Sparse_matrix::multiply(const Sparse_matrix b) { //TODO: add error handling (case: the sizes don't match)
    assert(this->_cols == b.rows());
    Sparse_matrix result = Sparse_matrix(this->_rows, b.cols());
    for (int i = 0; i < this->rows(); ++i) {
        for (int j = 0; j < b.cols(); ++j) {
            double temp = 0;
            for (int k = 0; k < this->_cols; ++k) {
                temp = temp + (*this)(i, k) * b(k, j);
            }
            result.setIndex(i, j, temp);
            temp = 0;
        }
    }
    return result;
}

Sparse_matrix Sparse_matrix::identity(int rows, int cols){
    assert(rows == cols);
    assert(0 < rows);
    Sparse_matrix res(rows, cols);
    for(int i = 0; i < rows; i++){
        res.setIndex(i, i, 1);
    }
    return res;
}

std::tuple<int, int> maxCoeff(const Sparse_matrix a) {
    int res_x, res_y;
    double max = a(0,0);
    for (int i = 0; i < a.rows(); ++i) {
        for (int j = 0; j < a.cols(); ++j) {
            if(a(i,j) >= max){
                max = a(i,j);
                res_x = i;
                res_y = j;
            }
        }
    }
    return std::make_tuple(res_x, res_y);
};

Sparse_matrix abs(const Sparse_matrix a) {
    Sparse_matrix res(a.rows(), a.cols());

    for (int i = 0; i < a.rows(); ++i) {
        for (int j = 0; j < a.cols(); ++j) {
            double val = a(i,j);
            if(a(i,j) < 0){
                res.setIndex(i, j, val * -1);
            } else {
                res.setIndex(i, j, val);
            }
        }
    }

    return res;
}
*/
#endif //__DYN_MATRIX_HPP__}
