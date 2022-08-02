cmake_minimum_required(VERSION 3.21)
project(SMBLY C)

set(CMAKE_C_STANDARD 99)

configure_file(TestScript.smbly TestScript.smbly COPYONLY)

add_executable(SMBLY-C compiler.c)
add_executable(SMBLY executer.c)
