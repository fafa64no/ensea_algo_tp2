cmake_minimum_required(VERSION 4.0)
project(ensea_algo_tp2)

set(CMAKE_CXX_STANDARD 23)

add_executable(ensea_algo_tp2 main.cpp
        src/utlis/file_io.cpp
        src/utlis/algo_utils.cpp
        src/exercises/exercise_1.cpp
        src/exercises/exercise_2.cpp
        src/exercises/exercise_3.cpp
        src/exercises/exercise_4.cpp
        src/exercises/exercise_5.cpp
        src/utlis/MinHeap.cpp
)

target_include_directories(ensea_algo_tp2 PRIVATE
    src
    src/exercises
    src/utlis
)
