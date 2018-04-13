#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>

//#include "src/Matrix.hpp"
#include "src/Sparse_matrix.hpp"

using namespace std;

bool map_of_rows = false; // indica si la matriz está guardada por filas o por columnas.
double epsilon = 0.00001;
int contador=0;

int main(int argc, char** argv){
	
	if (argc != 3){
		cout << endl<<"	Unable to run program" << endl;
		cout << "	Three parameters are expected:    program_name.exe  in_file.txt  p_number" << endl;
		return 1;
	}
	
	//********* levanto W y armo C***********
	string inFile(argv[1]);
	string outFile (strcat(argv[1], ".out"));
	double p = atof(argv[2]);
	
	string line;
	int pages, links, i, j;
	map_of_rows= false;
	contador = 0;//lo uso solo para debug
	ifstream f_test(inFile);
	
    if ( f_test.is_open() ){ f_test >> pages >> links;} 
    else { cout << "Unable to open file." << endl; return 1; }
    
	Sparse_matrix W = Sparse_matrix(pages);
	
	/**/ // leo basura, hay q lograr sacarla
	getline(f_test, line);	
	istringstream lineStream(line);
	lineStream >> i >> j;

	/**/ //ahora si leo el archivo de test -->la entrada i,j indica un 1 en la posicion [j][i]
		 // armo W y C al mismo tiempo
	vector<int> C (pages);	 //podemos ver como inicializarlo con ceros acá
	for(int n=0; n<pages; n++){
		C[n]= 0;
	}

	while( getline(f_test, line) ){ //asumo que el archivo de entrada no termina con salto de linea (en ese caso se vuelve a cargar en W y se suma uno de más a C )
		istringstream lineStream(line);
		lineStream >> j >> i;
		W.setIndex(i, j, 1);
		C[i-1] ++ ;//el vector esta indexado a partir de cero
	}
	

	f_test.close();
	
	//***********fin levantar W************
	

	
	//***********armo matrices -pD y E************
 
	vector<double> minusPD(pages); //se inicializa con "" ceros "" por default, ejemplo  minusPD[5] = 8.90675e-310
	for(int n=0; n<pages; n++){
		minusPD[n]= 0.0;
	}
	
	for (int i = 0; i< pages; i++){
		if (C[i]!=0) { //si C es igual a cero , D es cero
		minusPD[i] = -(p/C[i]);
		}
	}
	
	vector<int> E (pages, 1);
	
	//***********fin armar matrices -pD y E************

	
	
	//*********** Calculo A =  W  * (-pD), descarto resultados menores a epsilon  ************
	
	
	for (int j = 1; j<= pages; j++){
		W.multColByScalar( j, minusPD[j-1]);
	}
	
	//*********** Fin calculo A =  W  y (-pD), descarto resultados menores a epsilon  ************
  
  
  return 1;
}


