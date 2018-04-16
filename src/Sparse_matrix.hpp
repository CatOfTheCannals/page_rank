#ifndef __SPARSE_MATRIX_HPP__
#define __SPARSE_MATRIX_HPP__

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <assert.h>
#include <tuple>
#include <map>




extern bool map_of_rows;
extern int contador;
extern double epsilon;

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
    Sparse_matrix operator=(const Sparse_matrix other ) ;
    void transpose();
    void swapRows(int i1, int i2);
    Sparse_matrix getRow(int index);
    void setRow (int index, map<int, double> row);

    static Sparse_matrix identity(int n);
    void multColByScalar(std::size_t col_idx, double scalar);
    void preMultiplyByDiagMatrix(const vector<double> v);
    
	Sparse_matrix subMatrix(int i1, int i2, int j1, int j2);
	std::tuple<int, int> shape() const;
	
	Sparse_matrix multiply(const Sparse_matrix b);
	void operator*(double scalar); //scalar multiplication
	 
//	std::tuple<int, int> maxCoeffAbs(const Sparse_matrix a);
//	Sparse_matrix abs(const Sparse_matrix a) {


/*   
    Sparse_matrix getRow(int index);
    bool operator==(const Sparse_matrix& other) const; 
    
    static Sparse_matrix identity(int rows, int cols);
    
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

s_matrix Sparse_matrix::matrix()const {
    return _matrix;
}

std::ostream& operator<<(std::ostream& o, const Sparse_matrix& a)
{
    for (std::size_t i = 1; i <= a.rows(); i++) {
		o<< endl << ' ';
        for (std::size_t j = 1; j <= a.cols(); j++) {
            o << a(i, j) << '\t';
        }
        if (!(i / a.rows())) {
            o << endl;
        }
		o<<endl;
    }
    return o;
}

double Sparse_matrix::operator()(std::size_t row_idx, std::size_t col_idx) const
{	
	double val = 0.0; //si el indice no está definido en la matriz, entonces valor es cero
	assert(1<= row_idx <= this->_rows && 1<= col_idx <= this->_cols);

	if(map_of_rows){
		
		it_s_matrix row_it = _matrix.find(row_idx);

		if (row_it != _matrix.end()){ //la fila row_idx está definida
			map<int, double>::const_iterator col_it = row_it->second.find(col_idx);
			if (col_it != row_it->second.end()){ //la col col_idx está definida
				val = col_it->second;
			}
		}
	}
	else{
		it_s_matrix col_it = _matrix.find(col_idx);

		if (col_it != _matrix.end()){ //la columna col_idx está definida
			map<int, double>::const_iterator row_it = col_it->second.find(row_idx);
			if (row_it != col_it->second.end()){ //la fila row_idx está definida
				val = row_it->second;
			}
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


Sparse_matrix Sparse_matrix::identity(int n){
    assert(0 < n);
    Sparse_matrix res= Sparse_matrix(n, n);
    for(int i = 1; i <= n; i++){
        res.setIndex(i, i, 1);
    }
    return res;
}

map<int, double> Sparse_matrix::column(std::size_t col_idx){
	assert(map_of_rows == false);
	map<int, double> empty_col;
	it_s_matrix col_it = this->_matrix.find(col_idx);
	if (col_it != this->_matrix.end()) { return col_it->second; }
	else{ return empty_col; }
}



void Sparse_matrix::preMultiplyByDiagMatrix(const vector<double> v){ 
	
	assert(map_of_rows == false);
	assert(this->_rows == v.size());
	for (int j = 1; j<= this->_cols; j++){
		this->multColByScalar( j, v[j-1]);
	}
	
}


void Sparse_matrix::multColByScalar(std::size_t j, double scalar){
	
	assert(1 <= j <= this->_cols);
	it_s_matrix it_col = _matrix.find(j);
	if (it_col != _matrix.end()){ //la columna j está definida		
		map<int, double>  colj= it_col->second;
		for(auto const &it_row : colj) {
			double new_val = it_row.second * scalar;
			this->setIndex( it_row.first, it_col->first, new_val);
		}		
	} // si j no esta definida, es cero y quiero que siga así
	//cout<<*this<<endl <<endl<<endl;
}

	
void Sparse_matrix::setIndex(int i, int j, double value){
	
	assert(1 <= i <= this->_rows && 1 <= j <= this->_cols);
    bool definir= fabs(value) > epsilon; 
    
    if (map_of_rows == true){
		
		it_s_matrix row_it = _matrix.find(i);
		if (definir){//si el valor es "distinto" de cero, quiero q este en la matriz
			if (row_it != _matrix.end() ){ //la fila i está definida
				_matrix.find(i)->second[j]= value;
			}
			else { //la fila i no está definida
				map<int, double> new_row;
				new_row[j]= value;
				this->_matrix[i] = new_row;
			}
		}else{
			if (row_it != _matrix.end() ){ // esta definido y quiero sacarlo de la matriz
				_matrix[i].erase(j);
			}
		}
	} else{
		
		it_s_matrix col_it = _matrix.find(j);
		if (definir){//si el valor es "distinto" de cero, quiero q este en la matriz
			if (col_it != _matrix.end() ){ //la columna j está definida
				_matrix.find(j)->second[i]= value;
			}
			else { //la columna j no está definida
				map<int, double> new_col;
				new_col[i]= value;
				this->_matrix[j] = new_col;
			}
		}else{
			if (col_it != _matrix.end() ){ // esta definido y quiero sacarlo de la matriz
				_matrix[j].erase(i);
			}
		}	
	}
};


//asumo que cuando se llama a esta función se tiene a la matriz guardada como map<idx_fila, map< idx_col, valor> >
//esto se obtiene transponiendo la matriz guardada como map<idx_col, map< idx_fila, valor> > (q es como se guarda cuando se levanta el archivo)
void Sparse_matrix::swapRows(int i1, int i2) {
	
	assert(1<= i1 <= this->_rows && 1<= i1 <= this->_rows);
	assert(map_of_rows== true ); //la matriz tiene q haberse transpuesto
	
    if(i1 != i2){
		map<int, double> fila_aux = this->_matrix[i1] ;		
		this->_matrix[i1] = this->_matrix[i2];
		this->_matrix[i2] = fila_aux;	
    }
}



Sparse_matrix Sparse_matrix::getRow(int index) { //la unica fila de la matriz q devuelvo tiene el mismo indice columna q la original
	assert(map_of_rows== true);
	assert(1<= index<= this->_rows);
    Sparse_matrix row (1, this->_cols);
    
    it_s_matrix it_row =  this->_matrix.find(index);
    if( it_row != this->_matrix.end() ){
		 row.setRow(1, it_row->second); //funca solo con uno 
	}
	return row;
}



void Sparse_matrix::setRow (int index, map<int, double> row){
	assert(map_of_rows== true);
	assert(1<= index<= this->_rows);
	this->_matrix[index] = row;
}



Sparse_matrix  Sparse_matrix::operator=(const Sparse_matrix  other ){   // overloading operator =
	
	assert(this->_cols == other.cols() && this->_rows == other.rows() );	
    if(this->_matrix != other.matrix() ){
		for(int i = 1 ; i<= this->_rows ; i++) {
			for(int j = 1 ; j<= this->_cols ; j++) {
			   this->setIndex(i, j, other(i,j) );
			}
		}
	}
	return *this;
}


Sparse_matrix Sparse_matrix::operator+(const Sparse_matrix matrix) const { // overloading operator +
	
    assert(this->_cols == matrix.cols() && this->_rows == matrix.rows());
	Sparse_matrix Res = Sparse_matrix(this->_rows, this->_cols);
    for(int i = 1 ; i<= this->_rows ; i++) {
		for(int j = 1 ; j<= this->_cols ; j++) {
			double res_ij = (*this)(i,j) + matrix(i,j);
			Res.setIndex(i, j, res_ij);
		}
	}
	return Res;
}




void Sparse_matrix::operator*(double scalar) {
	for(auto const &it_1 : this->matrix()) {
		for(auto const &it_2 : it_1.second) {
			this-> setIndex(it_1.first, it_2.first,  it_2.second * scalar);
		}
	}
}



void Sparse_matrix::transpose() {
	
	map_of_rows= !map_of_rows; 
	Sparse_matrix mt = Sparse_matrix(this->_cols, this->_rows);
	for(auto const &it_1 : this->matrix()) {
		for(auto const &it_2 : it_1.second) {
			mt.setIndex(it_1.first, it_2.first, it_2.second);
		}
	}
	this-> _matrix = mt._matrix;
}






/*
Sparse_matrix Sparse_matrix::getRow(int index) {
    Sparse_matrix row(1, _cols);
    for (int i= 0; i < _cols; ++i) {
        row._matrix[i] = _matrix[index * _cols + i];
    }
    return row;
}
*/
std::tuple<int, int> Sparse_matrix::shape() const {
    return std::make_tuple(this->_rows, this->_cols);
}
/*
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
*/
Sparse_matrix Sparse_matrix::subMatrix(int i1, int i2, int j1, int j2 ){
	
    assert(i1 <= i2 && j1 <= j2);
    assert(0 < i1 <= _rows &&  0 < j2<= _cols);
    int res_rows = i2 - i1 + 1;
    int res_cols = j2 - j1 + 1;
    Sparse_matrix res = Sparse_matrix(res_rows, res_cols); 
	for( it_s_matrix it_col = this->_matrix.begin(); it_col != this->_matrix.end(); it_col++){	
		if ( j1 <= it_col->first <= j2){//si la col q estoy iterando está en el rango de la submatriz		
			for( map<int, double>::const_iterator it_row = (it_col->second).begin(); it_row != (it_col->second).end(); it_row++){	
				if ( i1 <= it_row->first <= i2){ //si la fila q estoy iterando está en el rango de la submatriz			
				res.setIndex(it_col->first, it_row->first, fabs(it_row->second) ); //defino la posicion en la submatriz
				}
			}
		}
    }
    return res;
}




Sparse_matrix Sparse_matrix::multiply(const Sparse_matrix b) { //TODO: add error handling (case: the sizes don't match)
    
    assert(this->_cols == b.rows());
    Sparse_matrix result = Sparse_matrix(this->_rows, b.cols());
    for (int i = 1; i <= this->rows(); ++i) {
        for (int j = 1; j <= b.cols(); ++j) {
            double temp = 0.0;
            for (int k = 1; k <= this->_cols; ++k) {
                temp = temp + (*this)(i, k) * b(k, j);
            }
            result.setIndex(i, j, temp);
        }
    }
    return result;    
}




tuple<int, int> maxCoeff(const Sparse_matrix a) {
	int res_x = 1;
	int res_y = 1;
    double max = a(1,1);
	s_matrix aux_mat = a.matrix();
	for( it_s_matrix it_1 = aux_mat.begin(); it_1 != aux_mat.end(); it_1++){
		for( map<int, double>::const_iterator it_2 = (it_1->second).begin(); it_2 != (it_1->second).end(); it_2++){
			if (it_2->second > max ){
				max= it_2->second;
				res_x = it_1->first;
				res_y = it_2->first;
			}
		}
	}
	tuple<int, int> res;
	if(map_of_rows){ res = make_tuple(res_x, res_y); } else{ res = make_tuple(res_y, res_x); }
    return res;
}



Sparse_matrix abs(const Sparse_matrix a) {

	Sparse_matrix mabs = Sparse_matrix(a.rows(), a.cols());
	
	for(auto const &it_1 : a.matrix()) {
		for(auto const &it_2 : it_1.second) {
			mabs.setIndex(it_1.first, it_2.first, fabs(it_2.second) );
		}
	}
	return mabs;
}


#endif //__DYN_MATRIX_HPP__}

