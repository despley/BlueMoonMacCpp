cmake_minimum_required(VERSION 3.13)
project(BlueMoon3)
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")


find_package(Boost REQUIRED COMPONENTS system thread log program_options chrono unit_test_framework)
include_directories(${Boost_INCLUDE_DIR})

add_executable(${PROJECT_NAME} main.cpp CardHandler.cpp CardHandler.h Cards.h card_tests.cpp)
configure_file(Resources/cards.txt cards.txt)

set(TEST_EXECUTABLE ${PROJECT_NAME}-test)

add_executable(${TEST_EXECUTABLE} test_main.cpp card_tests.cpp)

