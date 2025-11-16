cmake_minimum_required(VERSION 3.30)
project(avltree)

set(CMAKE_CXX_STANDARD 20)

add_executable(AVLTreeDebug
        AVLTreeDebug.cpp
        AVLTree.cpp
        AVLTree.h)

target_compile_options(AVLTreeDebug PRIVATE -fsanitize=address)
target_link_options(AVLTreeDebug PRIVATE -fsanitize=address)
