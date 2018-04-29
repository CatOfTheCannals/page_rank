set(DATA_FILES sparse_run_exp.cpp sparseRandomMatrix.cpp) # run_exp.cpp sparseRandomMatrix.cpp

add_executable(correrExp ${DATA_FILES})

target_link_libraries(correrExp metodos-tp1-base)