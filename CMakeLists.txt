cmake_minimum_required(VERSION 3.20)
project(lab4)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab4 main.cpp TasksQueue.cpp TasksQueue.h TasksQueueProcessor.cpp TasksQueueProcessor.h Sorter.cpp Sorter.h)
