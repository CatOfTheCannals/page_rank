#include "randomMatrix.h"
#include <random>
Sparse_matrix_vom randomMatrix(int n, int numberOfConnections){
    assert(0 < n);
    assert(numberOfConnections <= (n*n)-n);
    Sparse_matrix_vom res(n, n);
    std::random_device rd;     // only used once to initialise (seed) engine
    int cont = 1;
    while(cont < numberOfConnections){
        std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
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

Sparse_matrix_vom randomChainMatrix(int n, int numberOfConnections){
    assert(0 < n);
    assert(numberOfConnections <= (n*n)-2*n);
    Sparse_matrix_vom res(n, n);
    std::random_device rd;     // only used once to initialise (seed) engine
    for(int i = 1; i < n; i++){
        res.setIndex(i+1,i, 1);
    }
    if(n>1) {
        res.setIndex(1, n , 1);
    }
    int cont = 0;
    while(cont < numberOfConnections){
        std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
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

Sparse_matrix_vom directedList(int n){
    assert(0 < n);
    Sparse_matrix_vom res(n, n);
    for(int i = 1; i<= n; i++){
        res.setIndex(i+1,i, 1);
    }
    return res;
}


Sparse_matrix_vom completeColumnAndZeros(int n) {
    assert(0 < n);
    Sparse_matrix_vom res(n, n);
    for (int j = 1; j <= n; j++) {
         res.setIndex(j, 1, 1);
    }
    for (int j = 1; j <= n; j++) {
         res.setIndex(j, j, 0);
    }
    return res;
}



Sparse_matrix_vom completeColumnAndOneBack(int n){
    assert(1 < n);
    Sparse_matrix_vom res(n, n);
    for (int j = 1; j <= n; j++) {
        res.setIndex(j, 1, 1);
    }
    for (int j = 1; j <= n; j++) {
         res.setIndex(j, j, 0);
    }
    res.setIndex(1, 2, 1);
    return res;
}


Sparse_matrix_vom chainAndCompleteGraph(int n, int chainSize){
    assert(chainSize >= 2); //n must be 5 or higher
    assert( n - chainSize >= 3); //requirement in order to have a complete graph that isn't a chain.
    Sparse_matrix_vom res(n, n);
    for (int i = 1; i+1 <= chainSize; i++){
        res.setIndex(i+1,i, 1);
    }
    res.setIndex(1, chainSize - 1, 1);
    for (int i = chainSize; i <=n ; i++){
        for (int j = chainSize; j <= n; j++){
            if(j != i){
                res.setIndex(i,j, 1);
            }
        }
    }
    for (int j = 1; j <= n; j++) {
         res.setIndex(j, j, 0);
    }
    return res;
}


//diagonal + random. Diagonal + todos con la misma cantidad de links por fila, idem+ columna, misma cantidad de links por fila, por col
//otra matriz, le das el tamaño y m->cantidad de enlaces que quiero distribuidos aleatoriamente
