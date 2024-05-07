cmake_minimum_required(VERSION 3.28)
project(prog2_nhf)

set(CMAKE_CXX_STANDARD 17)

add_executable(prog2_nhf main.cpp
        BankAccount.cpp
        BankAccount.hpp
        Money.cpp
        Money.hpp
        Exceptions.cpp
        Exceptions.hpp
        BankingSystem.cpp
        BankingSystem.hpp
        Share.cpp
        Share.hpp)
