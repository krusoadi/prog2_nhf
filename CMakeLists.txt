cmake_minimum_required(VERSION 3.28)
project(prog2_nhf)

set(CMAKE_CXX_STANDARD 17)

add_executable(prog2_nhf main.cpp
        code/BankAccount.cpp
        headers/BankAccount.hpp
        code/Money.cpp
        headers/Money.hpp
        code/Exceptions.cpp
        headers/Exceptions.hpp
        code/BankingSystem.cpp
        headers/BankingSystem.hpp
        code/Share.cpp
        headers/Share.hpp
        code/Currency.cpp
        headers/Currency.h)
