cmake_minimum_required(VERSION 3.6)
project(c_vigenere)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.c vigenere.c vigenere.h stringHelper.c stringHelper.h fileHelper.c fileHelper.h)
add_executable(c_vigenere ${SOURCE_FILES})