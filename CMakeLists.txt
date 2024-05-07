cmake_minimum_required(VERSION 3.28)
project(prog2_nhf)

set(CMAKE_CXX_STANDARD 17)

add_executable(prog2_nhf main.cpp
        BankAccount.cpp
        BankAccount.h
        Money.cpp
        Money.h
        Exceptions.cpp
        Exceptions.h)
