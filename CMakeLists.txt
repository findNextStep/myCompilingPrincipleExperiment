cmake_minimum_required(VERSION 3.0.0)
project(CompilingPrincipleExperiment VERSION 0.1.0)

add_compile_options(-std=c++14)

include_directories(
    include
    third/json/single_include
)

add_library(
    token
    src/lib/token.cpp
)
add_library(
    lexicalAnalysier
    src/lib/lexicalAnalysier.cpp
)
target_link_libraries(
    lexicalAnalysier
    token
)

add_library(
    grammaticalAnalysier
    src/lib/grammaticalAnalysier.cpp
)
add_executable(functionalTestForLexicalAnalysier src/test/functionalTestForLexicalAnalysier.cpp)
target_link_libraries(
    functionalTestForLexicalAnalysier
    lexicalAnalysier
)

add_executable(grammaticalAnalysierTest
src/test/grammaticalAnalysierTest.cpp)

target_link_libraries(
    grammaticalAnalysierTest
    grammaticalAnalysier
)