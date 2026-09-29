cmake_minimum_required(VERSION 3.23)
project(L3 C)

set(CMAKE_C_STANDARD 99)

add_executable(L3 mrim2553_L3.c mrim2553_normal.h mrim2553_inline.h mrim2553_macro.h mrim2553_mode.h)
