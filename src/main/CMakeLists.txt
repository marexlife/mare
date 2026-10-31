cmake_minimum_required(VERSION 3.20)
project(main)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} 
    PRIVATE main.cpp 
    PRIVATE FILE_SET CXX_MODULES FILES
    lexer.ixx
    token_kind.ixx
    token.ixx
)