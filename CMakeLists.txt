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
        code/BankSystem.cpp
        headers/BankSystem.hpp
        code/Share.cpp
        headers/Share.hpp
        code/Currency.cpp
        headers/Currency.hpp
        headers/TContainer.hpp
        code/IDManager.cpp
        headers/IDManager.hpp
        code/UI.cpp
        headers/UI.hpp
        code/User.cpp
        headers/User.hpp
        code/FileManager.cpp
        headers/FileManager.hpp
        headers/memtrace.h
        code/memtrace.cpp
)

add_compile_definitions(prog2_nhf "MEMTRACE")

add_compile_options(-DMEMTRACE -Wall -Werror)
