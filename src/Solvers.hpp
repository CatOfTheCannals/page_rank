#ifndef TP1_METODOS_SOLVERS_H
#define TP1_METODOS_SOLVERS_H

#include <cassert>
#include <cmath>
#include <chrono>
#include <iostream>
#include <tuple>

#include "Matrix.hpp"


std::tuple<Matrix, Matrix> gauss_elimination(const Matrix& a);

Matrix backward_sub(const Matrix& a, const Matrix& y);

Matrix forward_sub(const Matrix& a, const Matrix& y);


#endif //TP1_METODOS_SOLVERS_H
