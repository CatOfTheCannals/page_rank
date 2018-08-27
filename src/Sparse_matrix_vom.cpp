#include "Sparse_matrix_vom.hpp"

int Sparse_matrix_vom::rows() const {
    return _rows;
}

int Sparse_matrix_vom::cols() const {
    return _cols;
}

double Sparse_matrix_vom::operator()(int row_idx, int col_idx) const {
    assert(1<= row_idx <= this->_rows && 1<= col_idx <= this->_cols);
    row_idx = row_idx - 1;
    auto row = _matrix[row_idx];
    if (row.size() == 0){
        return 0;
    } else {
        auto vec_it = row.find(col_idx);
        if (vec_it == row.end()){
            return 0;
        } else {
            return vec_it->second;
        }
    }
}

void Sparse_matrix_vom::setIndex(int i, int j, double value) {
    assert(1<= i <= this->_rows && 1<= j <= this->_cols);
    if(_epsilon < fabs(value)) {
        _matrix[i-1][j] = value;
    } else {
        if((*this)(i,j) != 0) {
            //borrar el numero de la fila
            auto vec_it = _matrix[i-1].find(j);
            _matrix[i-1].erase(vec_it);
        }

    }
}

Sparse_matrix_vom Sparse_matrix_vom::operator+(const Sparse_matrix_vom& m) const { // overloading operator +
    assert(this->_cols == m.cols() && this->_rows == m.rows());
    Sparse_matrix_vom res = Sparse_matrix_vom(this->_rows, this->_cols);
    for(int i = 1 ; i<= this->_rows ; i++) {
        for(int j = 1 ; j <= this->_cols ; j++) {
            double value = (*this)(i,j) + m(i,j);
            res.setIndex(i, j, value);
        }
    }
    return res;
}

Sparse_matrix_vom Sparse_matrix_vom::operator*(const double& scalar) const{
    Sparse_matrix_vom res = Sparse_matrix_vom(_rows, _cols);
    for(int i = 1; i <= _matrix.size(); i++) {
        for(auto const &it_2 : _matrix[i-1]) {
            int j = it_2.first;
            res.setIndex(i, j, (*this)(i, j) * scalar);
        }
    }
    return res;
}

bool Sparse_matrix_vom::operator==(const Sparse_matrix_vom& other) const {
    if (this->_rows != other.rows() || this->_cols != other.cols()) {
        return false;
    }
    else {
        for (int i = 1; i <= this->rows(); ++i) {
            for (int j = 1; j <= this->cols(); ++j) {
                if((*this)(i,j) != other(i,j)) {
                    return false;
                }
            }
        }
    }
    return true;
}

Sparse_matrix_vom Sparse_matrix_vom::getRow(int index) const{
    assert(1<= index<= this->_rows);
    index = index - 1;
    Sparse_matrix_vom row(1, this->_cols);
    row._matrix[0] = _matrix[index];
    return row;
}


void Sparse_matrix_vom::swapRows(int i1, int i2) {
    assert(1<= i1 <= this->_rows && 1<= i2 <= this->_rows);
    i1 = i1 - 1;
    i2 = i2 - 1;
    _matrix[i1].swap(_matrix[i2]);
}

Sparse_matrix_vom Sparse_matrix_vom::subMatrix(int i1, int i2, int j1, int j2) const {
    assert(i1 <= i2 && j1 <= j2);
    assert(0 < i1  &&  i2 <= _rows);
    assert(0 < j1  &&  j2 <= _cols);

    assert(1<= i1 <= this->_rows && 1<= i2 <= this->_rows);
    i1 = i1 - 1;
    i2 = i2 - 1;

    int res_rows = i2 - i1 + 1;
    int res_cols = j2 - j1 + 1;
    Sparse_matrix_vom res = Sparse_matrix_vom(res_rows, res_cols);

    for( int i = 0; i < this->_matrix.size(); i++){
        if(i1 <= i && i <= i2){
            for( auto it_col = (_matrix[i]).begin(); it_col != (_matrix[i]).end(); it_col++){
                if (j1 <= it_col->first && it_col->first <= j2){
                    // std::cout << "i: " << it_row->first << " j: " << it_col->first << std::endl;
                    // std::cout << "proposed i: " << it_row->first - i1 << " proposed j: " << it_col->first - j1 << std::endl;
                    res.setIndex(i - i1 + 1, it_col->first - j1 + 1, it_col->second);
                }
            }
        }

    }

    return res;
}

std::ostream& operator<<(std::ostream& o, const Sparse_matrix_vom& a) {
    for (std::size_t i = 1; i <= a.rows(); i++) {
        for (std::size_t j = 1; j <= a.cols(); j++) {
            o << a(i, j) << '\t';
        }
        o<<endl;
    }
    o<<endl;
    return o;
}

Sparse_matrix_vom Sparse_matrix_vom::multiply(const Sparse_matrix_vom b) const{

    Sparse_matrix_vom res(this->rows(), b.cols());
    if(this->_matrix.size() == 0 || b._matrix.size() == 0) { // alguno de los inputs es matriz de ceros?
        return res;
    }

    auto begin = GET_TIME;
    Sparse_matrix_vom bt = b.transpose(); //esto me sirve para tener las columnas de b almazenadas en las filas de bt
    auto end = GET_TIME;
    std::cout << "'transpose_time': " << GET_TIME_DELTA(begin, end) << std::endl;

    begin = GET_TIME;
    double val;
    for (int i = 1; i <= res.rows(); ++i) {
        for (int j = 1; j <= res.cols(); ++j) {

            auto row(this->getRow(i));
            auto col(bt.getRow(j));

            val = dotProd(row, col);
            res.setIndex(i, j, val);
        }
    }
    end = GET_TIME;
    std::cout << "'mult_time': " << GET_TIME_DELTA(begin, end) << std::endl;


    return res;
}

double dotProd(const Sparse_matrix_vom u, const Sparse_matrix_vom w) {
    assert(u.rows()== 1 && w.rows()== 1);
    assert(u._matrix.size()== 1 && w._matrix.size()== 1);

    double sum = 0;
    s_vec u_map = u._matrix[0]; // quiero la fila de u
    for(auto &iv : u_map) { // itero los pares indice valor de u
        auto w_map = w._matrix[0]; // quiero la fila de w
        auto w_map_it = w_map.find(iv.first);// si w tiene valores en el mismo indice que estoy viendo de u
        if(w_map_it != w_map.end()) {
            sum += iv.second * w_map_it->second;
        }
    }
    return sum;
}
Sparse_matrix_vom Sparse_matrix_vom::transpose() const{
    s_matrix b_col(_cols);
    for( int i = 0; i <_matrix.size(); i++){
        for( auto it_col = _matrix[i].begin(); it_col != _matrix[i].end(); it_col++){
            b_col[it_col->first - 1][i + 1] = it_col->second;
        }
    }
    Sparse_matrix_vom bt(this->cols(), this->rows());
    bt._matrix = b_col;
    return bt;
}

Sparse_matrix_vom Sparse_matrix_vom::identity(int n) {
    Sparse_matrix_vom id(n,n);
    for(int i = 1; i <= n ; i++) {
        id.setIndex(i,i,1);
    }
    return id;
}

std::tuple<int, int> Sparse_matrix_vom::maxCoeff() {
    int res_y = 1;
    int res_x = 1;
    double maxVal = (*this)(1,1);
    for( int i = 0; i <_matrix.size(); i++){
        for( auto it_col = _matrix[i].begin(); it_col != _matrix[i].end(); it_col++){
            if(maxVal < it_col->second) {
                maxVal = it_col->second;
                res_x = i + 1;
                res_y = it_col->first;
            }
        }
    }
    return make_tuple(res_x, res_y);
}

Sparse_matrix_vom Sparse_matrix_vom::abs() {
    Sparse_matrix_vom mabs = Sparse_matrix_vom(_rows, _cols);
    for( int i = 1; i <= _matrix.size(); i++){
        for( auto it_col = _matrix[i-1].begin(); it_col != _matrix[i-1].end(); it_col++){
            int j = it_col->first;
            mabs.setIndex(i, j, fabs(it_col->second));
        }
    }
    return mabs;
}

double Sparse_matrix_vom::operator()(int idx) const {//solo si mi matriz es un vector fila o columna
    assert(this->_rows == 1 || this->_cols == 1);
    assert(idx <= std::max(this->_rows, this->_cols));
    //si tengo una sola fila, idx es el indice columna
    if (this->_rows == 1 ){return (*this)(1,idx);}
    //si tengo una sola columna, idx es el indice fila
    if (this->_cols == 1 ){return (*this)(idx,1);}
}

bool Sparse_matrix_vom::isApproximate(const Sparse_matrix_vom b) const {
    Sparse_matrix_vom a_copy = (*this);
    Sparse_matrix_vom b_copy = b;
    auto diff = (a_copy + b_copy * (-1)).abs();
    for( auto it_row = diff._matrix.begin(); it_row != diff._matrix.end(); it_row++){
        for( auto it_col = it_row->begin(); it_col != it_row->end(); it_col++){
            if(_epsilon < it_col->second) {
                return false;
            }
        }
    }
    return true;
}

Sparse_matrix_vom Sparse_matrix_vom::random_matrix(int height, int width){
    Sparse_matrix_vom random_matrix(height, width);
    for(int i = 1; i <= random_matrix.rows(); i++){
        for(int j = 1; j <= random_matrix.cols(); j++){
            if(i != j && rand() % 9) {
                random_matrix.setIndex(i, j, 1); //matrix density of %90
            }

        }
    }
    return random_matrix;
}

/*
double operator()(std::size_t idx) const;

std::tuple<int, int> shape() const;

bool isApproximate(const Sparse_matrix_vom b, double epsilon) const;
 */