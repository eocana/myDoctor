cmake_minimum_required(VERSION 3.24)
project(myDoctor C)

set(CMAKE_C_STANDARD 11)

add_executable(myDoctor main.c menu.h menu.c enfermedades.h enfermedades.c)
