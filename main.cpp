#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <string.h>

#include "chrono"
#include "data/randomMatrix.cpp"

#define GET_TIME std::chrono::high_resolution_clock::now()
#define GET_TIME_DELTA(begin, end) \
     std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()

#include "src/sparse_page_rank.h"

using namespace std;



int main(int argc, char** argv){

	if (argc > 6 || argc < 3){
		cout << endl<<"	Unable to run program" << endl;
		cout << "	From 3 to 6 to parameters are expected:    program_name.exe  in_file.txt  p_number randomMatrixNumber n numberOfConnections" << endl;
		return 1;
	}

    int tipoMatriz = 0;
    if(argc>3){ tipoMatriz = std::atoi(argv[3]);}

    if (tipoMatriz!=0){
    double p = std::atof(argv[2]);
    string outFilePath(argv[1]);
	outFilePath += ".out";
    Sparse_matrix_vom W = Sparse_matrix_vom(1,1);
        int n = std::atoi(argv[4]);
        if (tipoMatriz == 3) {
            W = directedList(n);
        } else if (tipoMatriz == 4) {
            W = completeColumnAndZeros(n);
        } else if (tipoMatriz == 5) {
            W = completeColumnAndOneBack(n);
        } else {
            int numberOfConnections = std::atoi(argv[4]);
            if (tipoMatriz == 1) {
                W = randomMatrix(n, numberOfConnections);
            } else if (tipoMatriz == 2) {
                W = randomChainMatrix(n, numberOfConnections);
            } else if (tipoMatriz == 6) {
                W = chainAndCompleteGraph(n, numberOfConnections);
            }
        }

    auto C = colSumDiag(W);
	//***********fin levantar W************
	auto output_rank = page_rank(W, C, p);

    ofstream outFile;
    outFile.open(outFilePath);
    outFile << p << endl;
    outFile << output_rank;
	outFile.close();
    } else {
        if (argc != 3){
            cout << endl<<"	Unable to run program" << endl;
            cout << "	Three parameters are expected:    program_name.exe  in_file.txt  p_number" << endl;
            return 1;
        }

        // leo el archivo de test -->la entrada i,j indica un 1 en la posicion [j][i]

        cout << "argv[0]: " << argv[0] << endl;
        cout << "argv[1]: " << argv[1] << endl;
        cout << "argv[2]: " << argv[2] << endl;

        string inFile(argv[1]);
        string outFilePath(argv[1]);
        outFilePath += ".out";
        double p = std::atof(argv[2]);



        cout << "outFilePath: " << outFilePath << endl;
        cout << "p: " << p << endl;

        string line;
        int pagecount, links, i, j;
        ifstream f_test(inFile);

        if ( f_test.is_open() ){ f_test >> pagecount >> links;}
        else { cout << "Unable to open file." << endl; return 1; }


        /**/ // leo basura, hay q lograr sacarla
        getline(f_test, line);
        istringstream lineStream(line);
        lineStream >> i >> j;

        /**/ // fin basura


        //********* levanto W (POR COLUMNAS) y armo C al mismo tiempo ***********
        auto begin = GET_TIME;

        Sparse_matrix_vom W = Sparse_matrix_vom(pagecount, pagecount);
        while( getline(f_test, line) ){ //asumo que el archivo de entrada no termina con salto de linea (en ese caso se vuelve a cargar en W y se suma uno de más a C )
            istringstream lineStream(line);
            lineStream >> j >> i;
            W.setIndex(i, j, 1);
        }
        f_test.close();
        auto C = colSumDiag(W);

        auto end = GET_TIME;
        cout << "'load_time': " << GET_TIME_DELTA(begin, end) << endl;
        //***********fin levantar W************

        begin = GET_TIME;
        auto output_rank = page_rank(W, C, p);
        end = GET_TIME;
        cout << "'page_rank_time': " << GET_TIME_DELTA(begin, end) << endl;

        ofstream outFile;
        outFile.open(outFilePath);
        outFile << p << endl;
        outFile << output_rank;
        outFile.close();
    }

    return 0;
}

