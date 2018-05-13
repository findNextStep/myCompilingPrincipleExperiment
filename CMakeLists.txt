cmake_minimum_required(VERSION 3.0.0)
project(CompilingPrincipleExperiment VERSION 0.1.0)

add_compile_options(-std=c++14)

include_directories(
    include
    third/json/include
)

add_executable(CompilingPrincipleExperiment main.cpp)