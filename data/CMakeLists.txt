set(DATA_FILES run_exp.cpp randomMatrix.cpp)

add_executable(correrExp ${DATA_FILES})

target_link_libraries(correrExp metodos-tp1-base)