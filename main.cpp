#include <iostream>
#include <fstream>
#include <string>
//#include "src/Matrix.hpp"
#include "src/Sparse_matrix.hpp"

using namespace std;

bool map_of_rows = false; // indica si la matriz está guardada por filas o por columnas.

int main(int argc, char** argv){

    // m.printarray();

    string line;

    ifstream f_test("test.txt");
    if ( f_test.is_open() ){
        while( getline(f_test, line) ){
            cout << line << endl;
        }
        f_test.close();
    } else {
        cout << "Unable to open file." << endl;
    }

	Sparse_matrix m  = Sparse_matrix(5);
	
	map<int, double> col0;
	map<int, double> col1;
	map<int, double> col2;
	map<int, double> col3;
	map<int, double> col4;
 
	col0[0] = 0;
	col0[1] = 0;
	col0[2] = 0;
	col0[3] = 1;
	col0[4] = 0;

	col1[0] = 0;
	col1[1] = 0;
	col1[2] = 1;
	col1[3] = 1;
	col1[4] = 1;

	col2[0] = 0;
	col2[1] = 1;
	col2[2] = 0;
	col2[3] = 0;
	col2[4] = 0;

	col3[0] = 0;
	col3[1] = 0;
	col3[2] = 0;
	col3[3] = 0;
	col3[4] = 1;

	col4[0] = 0;
	col4[1] = 0;
	col4[2] = 0;
	col4[3] = 0;
	col4[4] = 0;

	m[0] = col0;
	m[1] = col1;
	m[2] = col2;
	m[3] = col3;
	m[4] = col4;


	assert( m((size_t)3, (size_t)3) == 0);
	assert( m((size_t) 0, (size_t) 3) == 1);
	
	
	
  return 0;
}


