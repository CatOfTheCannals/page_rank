#include "randomMatrix.h"
#include <random>
Matrix randomMatrix(int n, int numberOfConnections){
    assert(0 < n);
    assert(numberOfConnections <= (n*n)-n);
    Matrix res(n, n);
    std::random_device rd;     // only used once to initialise (seed) engine
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

Matrix randomChainMatrix(int n, int numberOfConnections){
    assert(0 < n);
    assert(numberOfConnections <= (n*n)-2*n);
    Matrix res(n, n);
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

Matrix directedList(int n){
    assert(0 < n);
    Matrix res(n, n);
    for(int i = 0; i+1 < n; i++){
        res.setIndex(i+1,i, 1);
    }
    return res;
}


Matrix completeColumnAndZeros(int n) {
    assert(0 < n);
    Matrix res(n, n);
    for (int j = 1; j < n; j++) {
         res.setIndex(j, 0, 1);
    }
    return res;
}

Matrix conectionsPerColumnRandomMatrix(int n, int connectionsPerColumn){ //NO
    assert(0 < n);
    assert(connectionsPerColumn <= n-1);
    Matrix res(n, n);
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

Matrix completeColumnAndOneBack(int n){
    assert(0 < n);
    Matrix res(n, n);
    for (int j = 1; j < n; j++) {
        res.setIndex(j, 0, 1);
    }
    if(n>1) {
        res.setIndex(0, 1, 1);
        return res;
    }
}


Matrix chainAndCompleteGraph(int n, int chainSize){
    assert(chainSize >= 2); //n must be 5 or higher
    assert( n - chainSize >= 3); //requirement in order to have a complete graph that isn't a chain.
    Matrix res(n, n);
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


//diagonal + random. Diagonal + todos con la misma cantidad de links por fila, idem+ columna, misma cantidad de links por fila, por col
//otra matriz, le das el tamaño y m->cantidad de enlaces que quiero distribuidos aleatoriamente