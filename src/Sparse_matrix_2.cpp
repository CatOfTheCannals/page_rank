#include "Sparse_matrix_2.hpp"

int Sparse_matrix_2::rows() const {
    return _rows;
}

int Sparse_matrix_2::cols() const {
    return _cols;
}

double Sparse_matrix_2::operator()(int row_idx, int col_idx) const {
    assert(1<= row_idx <= this->_rows && 1<= col_idx <= this->_cols);
    auto it = _matrix.find(row_idx);
    if (it == _matrix.end()){
        return 0;
    } else {
        auto vec_it = it->second.find(col_idx);
        if (vec_it == it->second.end()){
            return 0;
        } else {
            return vec_it->second;
        }
    }
}

void Sparse_matrix_2::setIndex(int i, int j, double value) {
    assert(1<= i <= this->_rows && 1<= j <= this->_cols);
    if(_epsilon < fabs(value)) {
        _matrix[i][j] = value;
    } else {
        if((*this)(i,j) != 0) {
            //borrar el numero de la fila
            auto it = _matrix.find(i);
            auto vec_it = it->second.find(j);
            it->second.erase(vec_it);
            // ver si la fila quedo vacia, en caso afirmativo hacerla PIJA
            if(it->second.size() == 0) {
                _matrix.erase(it);
            }
        }

    }
}

Sparse_matrix_2 Sparse_matrix_2::operator+(const Sparse_matrix_2& m) const { // overloading operator +
    assert(this->_cols == m.cols() && this->_rows == m.rows());
    Sparse_matrix_2 res = Sparse_matrix_2(this->_rows, this->_cols);
    for(int i = 1 ; i<= this->_rows ; i++) {
        for(int j = 1 ; j <= this->_cols ; j++) {
            double value = (*this)(i,j) + m(i,j);
            res.setIndex(i, j, value);
        }
    }
    return res;
}

Sparse_matrix_2 Sparse_matrix_2::operator*(const double& scalar) const{
    Sparse_matrix_2 res = Sparse_matrix_2(_rows, _cols);
    for(auto const &it_1 : _matrix) {
        for(auto const &it_2 : it_1.second) {
            res.setIndex(it_1.first, it_2.first, (*this)(it_1.first, it_2.first) * scalar);
        }
    }
    return res;
}

bool Sparse_matrix_2::operator==(const Sparse_matrix_2& other) const {
    if (this->_rows != other.rows() || this->_cols != other.cols()) {
        return false;
    }
    else {
        for (int i = 0; i < this->rows(); ++i) {
            for (int j = 0; j < this->cols(); ++j) {
                if((*this)(i,j) != other(i,j)) {
                    return false;
                }
            }
        }
    }
    return true;
}

Sparse_matrix_2 Sparse_matrix_2::getRow(int index) const{
    assert(1<= index<= this->_rows);
    Sparse_matrix_2 row (1, this->_cols);

    auto it_row =  this->_matrix.find(index);
    if( it_row != this->_matrix.end() ){
        auto row = it_row->second;
    }
    return row;
}


void Sparse_matrix_2::swapRows(int i1, int i2) {
    _matrix[i1].swap(_matrix[i2]);
}

Sparse_matrix_2 Sparse_matrix_2::subMatrix(int i1, int i2, int j1, int j2) const {
    assert(i1 <= i2 && j1 <= j2);
    assert(0 < i1  &&  i2 <= _rows);
    assert(0 < j1  &&  j2 <= _cols);
    int res_rows = i2 - i1 + 1;
    int res_cols = j2 - j1 + 1;
    Sparse_matrix_2 res = Sparse_matrix_2(res_rows, res_cols);

    for( auto it_row = this->_matrix.begin(); it_row != this->_matrix.end(); it_row++){
        if(i1 <= it_row->first && it_row->first <= i2){
            for( auto it_col = (it_row->second).begin(); it_col != (it_row->second).end(); it_col++){
                if (j1 <= it_col->first && it_col->first <= j2){
                    // std::cout << "i: " << it_row->first << " j: " << it_col->first << std::endl;
                    // std::cout << "proposed i: " << it_row->first - i1 << " proposed j: " << it_col->first - j1 << std::endl;
                    res.setIndex(it_row->first - i1 + 1, it_col->first - j1 + 1, it_col->second);
                }
            }
        }

    }

    return res;
}

std::ostream& operator<<(std::ostream& o, const Sparse_matrix_2& a) {
    for (std::size_t i = 1; i <= a.rows(); i++) {
        for (std::size_t j = 1; j <= a.cols(); j++) {
            o << a(i, j) << '\t';
        }
        o<<endl;
    }
    o<<endl;
    return o;
}

Sparse_matrix_2 Sparse_matrix_2::multiply(const Sparse_matrix_2 b) const{

    Sparse_matrix_2 res(this->rows(), b.cols());
    if(this->_matrix.size() == 0 || b._matrix.size() == 0) { // alguno de los inputs es matriz de ceros?
        return res;
    }

    Sparse_matrix_2 bt = b.transpose(); //esto me sirve para tener las columnas de b almazenadas en las filas de bt

    double val;
    for (int i = 1; i <= res.rows(); ++i) {
        for (int j = 1; j <= res.cols(); ++j) {

            Sparse_matrix_2 row(1,this->cols());
            Sparse_matrix_2 col(1,bt.cols());
            if(this->_matrix.find(i) != this->_matrix.end() && bt._matrix.find(j) != bt._matrix.end()) {
                row._matrix[1] = this->_matrix.find(i)->second;
                col._matrix[1] = bt._matrix.find(j)->second;
                val = dotProd(row, col);
            } else {
                val = 0;
            }
            res.setIndex(i, j, val);
        }
    }
    return res;
}

double dotProd(const Sparse_matrix_2 u, const Sparse_matrix_2 w) {
    assert(u.rows()== 1 && w.rows()== 1);
    assert(u._matrix.size()== 1 && w._matrix.size()== 1);

    double sum = 0;
    s_vec u_map = u._matrix.find(1)->second; // quiero la fila de u
    for(auto &iv : u_map) { // itero los pares indice valor de u
        auto w_map = w._matrix.find(1)->second; // quiero la fila de w
        auto w_map_it = w_map.find(iv.first);// si w tiene valores en el mismo indice que estoy viendo de u
        if(w_map_it != w_map.end()) {
            sum += iv.second * w_map_it->second;
        }
    }
    return sum;
}
Sparse_matrix_2 Sparse_matrix_2::transpose() const{
    s_matrix b_col;
    for( auto it_row = this->_matrix.begin(); it_row != this->_matrix.end(); it_row++){
        for( auto it_col = (it_row->second).begin(); it_col != (it_row->second).end(); it_col++){
            b_col[it_col->first][it_row->first] = it_col->second;
        }
    }
    Sparse_matrix_2 bt(this->cols(), this->rows());
    bt._matrix = b_col;
    return bt;
}

Sparse_matrix_2 Sparse_matrix_2::identity(int n) {
    Sparse_matrix_2 id(n,n);
    for(int i = 1; i <= n ; i++) {
        id.setIndex(i,i,1);
    }
    return id;
}

std::tuple<int, int> Sparse_matrix_2::maxCoeff() {
    int res_y = 1;
    int res_x = 1;
    double maxVal = (*this)(1,1);
    for( auto it_row = this->_matrix.begin(); it_row != this->_matrix.end(); it_row++){
        for( auto it_col = (it_row->second).begin(); it_col != (it_row->second).end(); it_col++){
            if(maxVal < it_col->second) {
                maxVal = it_col->second;
                res_x = it_row->first;
                res_y = it_col->first;

            }
        }
    }
    return make_tuple(res_x, res_y);
}

Sparse_matrix_2 Sparse_matrix_2::abs() {
    Sparse_matrix_2 mabs = Sparse_matrix_2(_rows, _cols);
    for( auto it_row = this->_matrix.begin(); it_row != this->_matrix.end(); it_row++){
        for( auto it_col = (it_row->second).begin(); it_col != (it_row->second).end(); it_col++){
            mabs.setIndex(it_row->first, it_col->first, fabs(it_col->second));
        }
    }

    return mabs;
}

double Sparse_matrix_2::operator()(int idx) const {//solo si mi matriz es un vector fila o columna
    assert(this->_rows == 1 || this->_cols == 1);
    assert(idx <= std::max(this->_rows, this->_cols));
    //si tengo una sola fila, idx es el indice columna
    if (this->_rows == 1 ){return (*this)(1,idx);}
    //si tengo una sola columna, idx es el indice fila
    if (this->_cols == 1 ){return (*this)(idx,1);}
}

bool Sparse_matrix_2::isApproximate(const Sparse_matrix_2 b) const {
    Sparse_matrix_2 a_copy = (*this);
    Sparse_matrix_2 b_copy = b;
    auto diff = (a_copy + b_copy * (-1)).abs();
    for( auto it_row = diff._matrix.begin(); it_row != diff._matrix.end(); it_row++){
        for( auto it_col = (it_row->second).begin(); it_col != (it_row->second).end(); it_col++){
            if(_epsilon < it_col->second) {
                return false;
            }
        }
    }
    return true;
}

/*
double operator()(std::size_t idx) const;

std::tuple<int, int> shape() const;




bool isApproximate(const Sparse_matrix_2 b, double epsilon) const;
 */