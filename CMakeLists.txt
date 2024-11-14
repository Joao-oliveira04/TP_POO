cmake_minimum_required(VERSION 3.26)
project(TP_POO)

set(CMAKE_CXX_STANDARD 23)

add_executable(TP_POO main.cpp
        Classes/Deserto.cpp
        Classes/Deserto.h
        Classes/Montanhas.cpp
        Classes/Montanhas.h
        Classes/Caravanas.cpp
        Classes/Caravanas.h
        Classes/Cidades.cpp
        Classes/Cidades.h
        Classes/Itens.cpp
        Classes/Itens.h)
