cmake_minimum_required(VERSION 3.20)
project(Project_5___Air_Traffic_Controller)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project_5___Air_Traffic_Controller main.cpp priorityqueue.h)

target_link_libraries (Project_5___Air_Traffic_Controller sfml-graphics sfml-window sfml-system)