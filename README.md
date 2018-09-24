# page_rank_tp1_metodos
Link to report:
https://www.overleaf.com/17618777pywgphbhcbds#/66872127/
## Compiling with cmake from root dir:

`mkdir build`

`cd build/`

`cmake ..`

`make`

### running main from build dir:

`./main ../cuantitative_tests/test_aleatorio.txt 0.85`

### running google-tests from build dir:

`cd test/`

`./correrTests`

### running cualitative tests:

`cd build/`

`./main ../cualitative_tests/completeGraphP0.01n20.txt 0.01 7 20`

`From 3 to 6 to parameters are expected:    program_name.exe  in_file.txt  p_number randomMatrixNumber n numberOfConnections`
`Some functions take 2 parameters, some just one (this can bee seen in ../data/randomMatrix.h)`
`The results can be found in ../cualitative_tests, the first line on this files is the pnumber, the names of the files indicates the parameters that have been used. randomChainMatrix corresponds to the "ciclo" experiment and zero links had been added randomly for this case`

`This are the codes for each kind of matrix:`
`Sparse_matrix_vom = 0`
`randomMatrix = 1`
`randomChainMatrix = 2`
`directedList = 3`
`completeColumnAndZeros = 4`
`completeColumnAndOneBack = 5`
`chainAndCompleteGraph = 6`
`completeGraph = 7`


`
