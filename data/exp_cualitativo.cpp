#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <utility>
#include "chrono"
#include "../src/sparse_page_rank.h"
#include "randomMatrix.h"


using namespace std;



/*
Para compilar : (desde la carpeta data )

			g++ -o cualitativo exp_cualitativo.cpp randomMatrix.cpp  ../src/sparse_page_rank.cpp ../src/Sparse_matrix_vom.cpp ../src/Sparse_solvers.cpp


Para correr:
			cualitativo p_grande   p_chico   min_dimension_de_matriz  max_dimension_de_matriz

ejemplo :
			cualitativo 0.1 0.001 8 10

los resultados quedan en ../data/results/

 */


bool pairCompare( const pair<int, double>& x, const pair<int, double>& y ){
	
	return x.second > y.second;
}


std::ostream& operator<<(std::ostream& o, const pair< vector<pair<int, double>> , int > & p){
	vector<pair<int, double>> v = p.first;
	int max_dim = p.second;
	for(int j = 1 ; j <= max_dim; j++){
			o << '\t' ;
	}
	o << "Rank:"<<endl;
    for(int i = 1 ; i<= v.size(); i++){
		for(int j = 1 ; j<= max_dim; j++){
			o << '\t' ;
		}
		o << v[i].first <<  '\t' << v[i].second << endl;
	}      
    return o;
}


vector< pair<int, double> > orderByRank(Sparse_matrix_vom M){
	
	vector<pair<int, double> > res;
	for(int i = 1; i <= M.rows(); i++ ){	
		res.push_back(make_pair(i, M(i,1)) ) ;
	}
	sort(res.begin(), res.end(), pairCompare);
	return res;
}



void familia_chain( double p, int min_matrix_dim, int max_matrix_dim){
	
	ostringstream filename;
    filename << "../data/results/chain_p"<< p << "_minDim" << min_matrix_dim << "_maxDim" << max_matrix_dim << ".csv";
    ofstream outputFile;
    outputFile.open(filename.str());
	
	for(int i = min_matrix_dim; i <= max_matrix_dim; i++) {
		
		Sparse_matrix_vom W =randomChainMatrix(i,0); //cero conexiones extras
		Sparse_matrix_vom C = colSumDiag(W);
		Sparse_matrix_vom res = page_rank(W, C, p);
		
		outputFile << "W: "<< endl << W << endl ;
		outputFile << make_pair(orderByRank(res), max_matrix_dim ) << endl;	
	}
    outputFile.close();
		
}



void familia_directed_list( double p, int min_matrix_dim, int max_matrix_dim){
	
	ostringstream filename;
    filename << "../data/results/directed_list_p"<< p << "_minDim" << min_matrix_dim << "_maxDim" << max_matrix_dim << ".csv";
    ofstream outputFile;
    outputFile.open(filename.str());	
	for(int i = min_matrix_dim; i <= max_matrix_dim; i++) {
		
		Sparse_matrix_vom W = directedList(i);
		Sparse_matrix_vom C = colSumDiag(W);
		Sparse_matrix_vom res = page_rank(W, C, p);
		outputFile << "W: "<< endl << W << endl ;
		outputFile << make_pair(orderByRank(res), max_matrix_dim ) << endl;	
	}
    outputFile.close();
	
}



void familia_completeColumnAndZeros(double p, int min_matrix_dim, int max_matrix_dim){
	
	ostringstream filename;
    filename << "../data/results/complete_column_and_zeros_p"<< p << "_minDim" << min_matrix_dim << "_maxDim" << max_matrix_dim << ".csv";
    ofstream outputFile;
    outputFile.open(filename.str());	
	for(int i = min_matrix_dim; i <= max_matrix_dim; i++) {
		Sparse_matrix_vom W = completeColumnAndZeros(i);
		Sparse_matrix_vom C = colSumDiag(W);
		Sparse_matrix_vom res = page_rank(W, C, p);
		outputFile << "W: "<< endl << W << endl;
		outputFile << make_pair(orderByRank(res), max_matrix_dim ) << endl;	
	}
    outputFile.close();

}



void familia_completeColumnAndOneBack(double p, int min_matrix_dim, int max_matrix_dim){
	
	ostringstream filename;
    filename << "../data/results/complete_column_and_one_back_p"<< p << "_minDim" << min_matrix_dim << "_maxDim" << max_matrix_dim << ".csv";
    ofstream outputFile;
    outputFile.open(filename.str());
	for(int i = min_matrix_dim; i <= max_matrix_dim; i++) {
		Sparse_matrix_vom W = completeColumnAndOneBack(i);
		Sparse_matrix_vom C = colSumDiag(W);
		Sparse_matrix_vom res = page_rank(W, C, p);
		outputFile << "W: "<< endl << W << endl;
		outputFile << make_pair(orderByRank(res), max_matrix_dim ) << endl;	
	}
    outputFile.close();
}



void familia_chainAndCompleteGraph(double p, int min_matrix_dim, int max_matrix_dim){

	ostringstream filename1;
	ostringstream filename2;
	ostringstream filename3;
    filename1 << "../data/results/chain_and_c_graph_chainSmGraph"<<"_p"<< p << "_minDim" << min_matrix_dim << "_maxDim" << max_matrix_dim << ".csv";
    filename2 << "../data/results/chain_and_c_graph_chainGrGraph"<<"_p"<< p << "_minDim" << min_matrix_dim << "_maxDim" << max_matrix_dim << ".csv";
    filename3 << "../data/results/chain_and_c_graph_chainEqGraph"<<"_p"<< p << "_minDim" << min_matrix_dim << "_maxDim" << max_matrix_dim << ".csv";
    ofstream outputFile1;
    ofstream outputFile2;
    ofstream outputFile3;
    
    outputFile1.open(filename1.str());
    outputFile2.open(filename2.str());
    outputFile3.open(filename3.str());
	
	for(int i = min_matrix_dim; i <= max_matrix_dim; i++) {
		
		Sparse_matrix_vom W1 = chainAndCompleteGraph(i, max(2, i*1/5) );
		Sparse_matrix_vom C1 = colSumDiag(W1);
		Sparse_matrix_vom rec1 = page_rank(W1, C1, p);
		
		outputFile1 << "W: "<< endl << W1 << endl;
		outputFile1 << make_pair(orderByRank(rec1), max_matrix_dim ) << endl;	
		
		
		Sparse_matrix_vom W2 = chainAndCompleteGraph(i, max(2, i*5/9) );
		Sparse_matrix_vom C2 = colSumDiag(W2);
		Sparse_matrix_vom rec2 = page_rank(W2, C2, p);
		
		outputFile2 << "W: "<< endl << W2 << endl;
		outputFile2 << make_pair(orderByRank(rec2), max_matrix_dim ) << endl;	
		
		
		Sparse_matrix_vom W3 = chainAndCompleteGraph(i, max(2, i*1/2) );
		Sparse_matrix_vom C3 = colSumDiag(W3);
		Sparse_matrix_vom rec3 = page_rank(W3, C3, p);
		
		outputFile3 << "W: "<< endl << W3 << endl ;
		outputFile3 << make_pair(orderByRank(rec3), max_matrix_dim ) << endl;	
		
	}
    outputFile1.close();
    outputFile2.close();
    outputFile3.close();
}




int main(int argc, char** argv) { 
 
 
	if (argc != 5){
		cout << endl<<"	Unable to run program" << endl;
		cout << "	Five parameters are expected:    cualitativo.exe  p_grande  p_chico  min_matrix_dim  max_matrix_dim " << endl;
		return 1;
	}
	double p_grande = atof(argv[1]);
	double p_chico = atof(argv[2]);
	int min_matrix_dim = atoi(argv[3]);
	int max_matrix_dim = atoi(argv[4]);
	
	
	familia_chain(p_grande, min_matrix_dim, max_matrix_dim);
	familia_chain(p_chico, min_matrix_dim, max_matrix_dim);

	familia_directed_list(p_grande, min_matrix_dim, max_matrix_dim);
	familia_directed_list(p_chico, min_matrix_dim, max_matrix_dim);

	familia_completeColumnAndZeros(p_grande, min_matrix_dim, max_matrix_dim);
	familia_completeColumnAndZeros(p_chico, min_matrix_dim, max_matrix_dim);

	familia_completeColumnAndOneBack(p_grande, min_matrix_dim, max_matrix_dim);
	familia_completeColumnAndOneBack(p_chico, min_matrix_dim, max_matrix_dim);

	if (max_matrix_dim >= 5){
		if (min_matrix_dim < 5){min_matrix_dim=5;}
		familia_chainAndCompleteGraph(p_grande, min_matrix_dim, max_matrix_dim);
		familia_chainAndCompleteGraph(p_chico, min_matrix_dim, max_matrix_dim);
	}

	return 1;

}
