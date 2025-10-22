cmake_minimum_required(VERSION 4.0)
project(ensea_algo_tp2)

set(CMAKE_CXX_STANDARD 20)

add_executable(ensea_algo_tp2 main.cpp
        src/subsequence_finder.cpp
        src/utlis/file_io.cpp
)

target_include_directories(ensea_algo_tp2 PRIVATE
    src
    src/utlis
)
