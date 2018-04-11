#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

//#include "src/Matrix.hpp"
#include "src/Sparse_matrix.hpp"

using namespace std;

bool map_of_rows = false; // indica si la matriz está guardada por filas o por columnas.
int contador=0;

int main(int argc, char** argv){
	
	if (argc != 3){
		cout << endl<<"	Unable to run program" << endl;
		cout << "	Three parameters are expected:    program_name.exe  in_file.txt  out_file.txt" << endl;
		return 1;
	}
	
	string inFile(argv[1]);
	string outFile(argv[2]);
	string line;
	int pages, links, i, j;
	map_of_rows= false;
	contador = 0;//lo uso solo para debug
	ifstream f_test(inFile);
	
    if ( f_test.is_open() ){ f_test >> pages >> links;} 
    else { cout << "Unable to open file." << endl; return 1; }
    
	Sparse_matrix sm = Sparse_matrix(pages);
	
	/**/ // leo basura, hay q lograr sacarla
	getline(f_test, line);	
	istringstream lineStream(line);
	lineStream >> i >> j;

	/**/ //ahora si leo el archivo de test
	
	while( getline(f_test, line) ){
		istringstream lineStream(line);
		lineStream >> i >> j;
		sm.setIndex(i,j,1);
	}
	f_test.close();
	
	
	
/*	Sparse_matrix m  = Sparse_matrix(5);
	
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
	assert( m((size_t)0, (size_t) 3) == 1);
	
	
	*/
  return 0;
}


