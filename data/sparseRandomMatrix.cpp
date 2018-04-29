#include "sparseRandomMatrix.hpp"
#include <random>

Sparse_matrix_2 sparseRandomMatrix(int n, int numberOfConnections) {
    assert(0 < n);
    assert(numberOfConnections <= (n*n)-n);
    Sparse_matrix_2 res(n, n);
    std::random_device rd; // only used once to initialise (seed) engine
    int cont = 0;
    while(cont < numberOfConnections){
        std::mt19937 rng(rd()); // random-number engine used (Mersenne-Twister in this case)
        std::uniform_int_distribution<int> uni(1,n); // guaranteed unbiased
        auto random_i = uni(rng);
        auto random_j = uni(rng);
        if(random_i != random_j && res(random_i,random_j) != 1){
            res.setIndex(random_i,random_j, 1);
            cont++;
        }
    }
    return res;
}

/*
 // estas requieren hacer cambios en los indices de los for loops, de los set index
 // y asegurarse via plots que las matrices generadas sean las esperadas(por ej que no contengan unos en la diagonal)

Sparse_matrix_2 randomChainMatrix(int n, int numberOfConnections){
    assert(0 < n);
    assert(numberOfConnections <= (n*n)-2*n);
    Sparse_matrix_2 res(n, n);
    std::random_device rd;     // only used once to initialise (seed) engine
    for(int i = 0; i+1 < n; i++){
        res.setIndex(i+1,i, 1);
    }
    if(n>1) {
        res.setIndex(0, n - 1, 1);
    }
    int cont = 0;
    while(cont < numberOfConnections){
        std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
        std::uniform_int_distribution<int> uni(0,n-1); // guaranteed unbiased
        auto random_i = uni(rng);
        auto random_j = uni(rng);
        if(random_i != random_j && res(random_i,random_j) != 1){
            res.setIndex(random_i,random_j, 1);
            cont++;
        }
    }
    return res;
}

Sparse_matrix_2 directedList(int n){
    assert(0 < n);
    Sparse_matrix_2 res(n, n);
    for(int i = 0; i+1 < n; i++){
        res.setIndex(i+1,i, 1);
    }
    return res;
}


Sparse_matrix_2 completeColumnAndZeros(int n) {
    assert(0 < n);
    Sparse_matrix_2 res(n, n);
    for (int j = 1; j < n; j++) {
        res.setIndex(j, 0, 1);
    }
    return res;
}

Sparse_matrix_2 conectionsPerColumnRandomMatrix(int n, int connectionsPerColumn){ //NO
    assert(0 < n);
    assert(connectionsPerColumn <= n-1);
    Sparse_matrix_2 res(n, n);
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(0,n-1); // guaranteed unbiased
    for (int j = 0; j < n; j++) {
        int count = 0;
        while(count < connectionsPerColumn){
            auto random_i = uni(rng);
            if (random_i != j && res(random_i, j) != 1) {
                res.setIndex(random_i, j, 1);
                count++;
            }
        }
        count = 0;
    }

    return res;
}

Sparse_matrix_2 completeColumnAndOneBack(int n){
    assert(0 < n);
    Sparse_matrix_2 res(n, n);
    for (int j = 1; j < n; j++) {
        res.setIndex(j, 0, 1);
    }
    if(n>1) {
        res.setIndex(0, 1, 1);
        return res;
    }
}


Sparse_matrix_2 chainAndCompleteGraph(int n, int chainSize){
    assert(chainSize >= 2); //n must be 5 or higher
    assert( n - chainSize >= 3); //requirement in order to have a complete graph that isn't a chain.
    Sparse_matrix_2 res(n, n);
    for (int i = 0; i+1 < chainSize; i++){
        res.setIndex(i+1,i, 1);
    }
    res.setIndex(0, chainSize - 1, 1);
    for (int i = chainSize; i < n ; i++){
        for (int j = chainSize; j < n; j++){
            if(j != i){
                res.setIndex(i,j, 1);
            }
        }
    }
    return res;
}
*/

//diagonal + random. Diagonal + todos con la misma cantidad de links por fila, idem+ columna, misma cantidad de links por fila, por col
//otra matriz, le das el tamaño y m->cantidad de enlaces que quiero distribuidos aleatoriamente