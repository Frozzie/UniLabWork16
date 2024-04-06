cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME test_matrix)
project(${PROJECT_NAME})

set(CMAKE_C_STANDARD 11)
set(SOURCE_EXE 
    main.c
    matrix/matrix.c)
    
set(DIRECTORIES 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/matrix)


include_directories (${DIRECTORIES})

add_executable(${PROJECT_NAME} ${SOURCE_EXE})
