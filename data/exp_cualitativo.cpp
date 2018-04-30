#include <iostream>
#include <fstream>
#include <sstream>
#include "chrono"
#include "../src/page_rank.h"
#include "randomMatrix.h"


using namespace std;


int first_expected( Matrix W, string tipo ){

	if (tipo == "chain"){
		
	}else if(tipo == "rnd"){
		
	}
	return 2;
}


int first_ranked( Matrix W){

	return 2;
}


void familia_randoms( double p, int n, int m, int cant) {

    ostringstream filename;
    filename << "../data/results/familia_randoms_p"<< p << "_n" << n << "_m" << m << ".csv";
    ofstream outputFile;
    outputFile.open(filename.str());
	
	
	for(int i = 0; i < cant; i++) {
	
		Matrix W =randomMatrix(n,m);
		Matrix C = colSumDiag(W);
		
		page_rank(W, C, p);
		
		outputFile << "Esperado: "<< first_expected(W, "rnd") <<"   Obtenido: " << first_ranked(W) << endl;
		cout << W <<endl;
	}
    outputFile.close();
}



void familia_chain(double p, int n, int m, int cant){
	
	ostringstream filename;
    filename << "../data/results/familia_chain_p"<< p << "_n" << n << "_m" << m << ".csv";
    ofstream outputFile;
    outputFile.open(filename.str());
	
	
	for(int i = 0; i < cant; i++) {
	
		Matrix W =randomChainMatrix(n,m);
		Matrix C = colSumDiag(W);
		
		Matrix rec = page_rank(W, C, p);
		
		outputFile << "Esperado: "<< first_expected(W, "chain") <<"   Obtenido: " << first_ranked(W) << endl;
		
	}
    outputFile.close();
		
}



int main(int argc, char** argv) { //espero recibir p y cant
 
 
	if (argc != 4){
		cout << endl<<"	Unable to run program" << endl;
		cout << "	Four parameters are expected:    program_name.exe  p_number amount_of_instances_per_experiment dim_of_matrix" << endl;
		return 1;
	}
	double p = atof(argv[1]);
	int cant = atoi(argv[2]);
	int matrix_dim = atoi(argv[3]);
	
	int max_conections = (matrix_dim * matrix_dim)-matrix_dim;
	int min_conections = matrix_dim;
	int conections = rand()%( max_conections - min_conections + 1); 
	
	familia_randoms(p, matrix_dim , conections, cant);
	
	familia_chain(p, matrix_dim, conections, cant);
	
	
	
	return 1;
	
}
