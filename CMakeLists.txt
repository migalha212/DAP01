cmake_minimum_required(VERSION 3.30)
project(DA2025_PRJ1_G0608)

set(CMAKE_CXX_STANDARD 14)

include_directories(data_structures)

add_executable(DA2025_PRJ1_G0608
    data_structures/Graph.h
    data_structures/MutablePriorityQueue.h
    src/main.cpp
        src/CLInterface.cpp
        src/CLInterface.h
        src/ParseFile.cpp
        src/ParseFile.h
        src/ShortestPathAlgorithms.cpp
        src/ShortestPathAlgorithms.h
        )
