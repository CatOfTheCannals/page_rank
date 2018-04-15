#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>

//#include "src/Matrix.hpp"
#include "src/Sparse_matrix.hpp"
#include "src/Solvers.hpp"

using namespace std;

bool map_of_rows = false; // indica si la matriz está guardada por filas o por columnas.
double epsilon = 0.00001;


int main(int argc, char** argv){

	if (argc != 3){
		cout << endl<<"	Unable to run program" << endl;
		cout << "	Three parameters are expected:    program_name.exe  in_file.txt  p_number" << endl;
		return 1;
	}
	
	// leo el archivo de test -->la entrada i,j indica un 1 en la posicion [j][i]

	string inFile(argv[1]);
	string outFile (strcat(argv[1], ".out"));
	double p = atof(argv[2]);
	
	string line;
	int pagecount, links, i, j;
	map_of_rows= false;
	ifstream f_test(inFile);
	
    if ( f_test.is_open() ){ f_test >> pagecount >> links;} 
    else { cout << "Unable to open file." << endl; return 1; }
    
	
	/**/ // leo basura, hay q lograr sacarla
	getline(f_test, line);	
	istringstream lineStream(line);
	lineStream >> i >> j;

	/**/ // fin basura
	
	
	//********* levanto W (POR COLUMNAS) y armo C al mismo tiempo ***********
	Sparse_matrix W = Sparse_matrix(pagecount, pagecount);
	vector<int> C (pagecount, 0);
	while( getline(f_test, line) ){ //asumo que el archivo de entrada no termina con salto de linea (en ese caso se vuelve a cargar en W y se suma uno de más a C )
		istringstream lineStream(line);
		lineStream >> j >> i;
		W.setIndex(i, j, 1);
		C[i-1] ++ ;//el vector esta indexado a partir de cero
	}
	
	f_test.close();
	
	//***********fin levantar W************
	

	
	//***********armo matrices -pD y E************
	

	vector<double> minusPD(pagecount, 0.0);
	
	for (int i = 0; i< pagecount; i++){ 
		if (C[i]!=0) { //si C es igual a cero , D es cero
			minusPD[i] = -(p/C[i]);
		}
	}
	
	vector<int> E (pagecount, 1);
	
	
	//***********fin armar matrices -pD y E************


	
	//*********** Calculo A = I + ( W  * (-pD) ), descarto resultados menores a epsilon  ************
	
	Sparse_matrix I = Sparse_matrix::identity(pagecount);
	
	W.preMultiplyByDiagMatrix(minusPD);
	
	Sparse_matrix A = Sparse_matrix(pagecount, pagecount);

	A = I + W;
	//*********** Fin calculo A =  W  y (-pD), descarto resultados menores a epsilon  ************
  

  
	//*********** Guardo A por FILAS, luego Triangulo A **************
	
	
	A.transpose(); 
	
    Sparse_matrix result = Sparse_matrix(A.rows(), W.cols());
	
	A.multiply(W);
//	cout<<A<<endl;
	
//	cout<<A<<endl<<endl<<endl;
//	cout<<B<<endl;
	
	//std::tuple<Sparse_matrix, Sparse_matrix> salida_gauss = gauss_elimination(W); // no soy muy fan de los nombres. EG es hacer la triangulación. para mi debería llamarse "gaussAndBackSub" o "solve". y "salida_gauss" capaz "res"
	//*********** Fin triangulo A **************
  
  return 0;
}

