cmake_minimum_required(VERSION 3.14)
project(tinycsharp
    VERSION 0.1.0
    LANGUAGES CXX
    DESCRIPTION "Tiny C# Compiler"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_library(libtinycsharp
    src/ast.cpp
    src/lexer.cpp
    src/parser.cpp
    include/ast.h 
    include/lexer.h 
    include/parser.h
    include/token.h
    include/utils.h
)


target_include_directories(libtinycsharp
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(tinycsharp
    src/main.cpp
)

target_link_libraries(tinycsharp PRIVATE libtinycsharp)

option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_TESTS)
    message(STATUS "Configuring tests...")
    enable_testing() 

    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )

    FetchContent_MakeAvailable(googletest)

    
    add_executable(tinycsharp_tests
        tests/test_lexer.cpp
    )

    
    target_link_libraries(tinycsharp_tests PRIVATE
        libtinycsharp
        GTest::gtest_main
    )
    include(GoogleTest)
    gtest_discover_tests(tinycsharp_tests)
endif()