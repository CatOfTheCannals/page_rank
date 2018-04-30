#include <iostream>
#include <fstream>
#include <sstream>
#include "chrono"
#include "../src/sparse_page_rank.h"
#include "randomMatrix.h"


using namespace std;



void familia_chain( double p, int max_matrix_dim){
	
	ostringstream filename;
    filename << "../data/results/familia_chain_p"<< p << "_maxDim" << max_matrix_dim << ".csv";
    ofstream outputFile;
    outputFile.open(filename.str());
	
	
	for(int i = 2; i <= max_matrix_dim; i++) {
		
		Sparse_matrix_2 W =randomChainMatrix(i,0); //cero conexiones extras
		Sparse_matrix_2 C = colSumDiag(W);
		Sparse_matrix_2 rec = page_rank(W, C, p);
		outputFile << "W: "<< endl << W << endl << " Rank: " << endl << rec << endl;
		
	}
    outputFile.close();
		
}

void familia_directed_list( double p, int max_matrix_dim){
	
	ostringstream filename;
    filename << "../data/results/familia_directed_list_p"<< p << "_maxDim" << max_matrix_dim << ".csv";
    ofstream outputFile;
    outputFile.open(filename.str());
	
	for(int i = 2; i <= max_matrix_dim; i++) {
		
		Sparse_matrix_2 W = directedList(i); //cero conexiones extras
		Sparse_matrix_2 C = colSumDiag(W);
		Sparse_matrix_2 rec = page_rank(W, C, p);
		outputFile << "W: "<< endl << W << endl << " Rank: " << endl << rec << endl;
		
	}
    outputFile.close();
	
}


int main(int argc, char** argv) { //espero recibir p y cant
 
 
	if (argc != 4){
		cout << endl<<"	Unable to run program" << endl;
		cout << "	Four parameters are expected:    program_name.exe  p_number max_matrix_dim  number_of_instances" << endl;
		return 1;
	}
	double p = atof(argv[1]);
	int max_matrix_dim = atoi(argv[2]);
	int instances = atoi(argv[3]);
	
	
//	int min_conections = matrix_dim;
//	int conections = rand()%( max_conections - min_conections + 1); 
	
	
	familia_chain(p, max_matrix_dim);
	
	familia_directed_list(p, max_matrix_dim);
	
	
	return 1;
	
}
