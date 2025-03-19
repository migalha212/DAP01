cmake_minimum_required(VERSION 3.30)
project(DA2025_PRJ1_G103)

set(CMAKE_CXX_STANDARD 14)

include_directories(data_structures)

add_executable(DA2025_PRJ1_G103
    data_structures/Graph.h
    data_structures/MutablePriorityQueue.h
    src/application.cpp
        src/clInterface.cpp
        src/clInterface.h
        src/ParseFile.cpp
        src/ParseFile.h
        src/ShortestPathAlgorithms.cpp
        src/ShortestPathAlgorithms.h
        )
