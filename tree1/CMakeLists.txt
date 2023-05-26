cmake_minimum_required(VERSION 3.23)
project(tree1 C)

set(CMAKE_C_STANDARD 99)

add_executable(tree1 main.c binarytreea.h queue.h threadbinarytree.h huffmantree.h)
