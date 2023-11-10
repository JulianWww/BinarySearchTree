cmake_minimum_required(VERSION 3.0.0)
project(BinarySearchTree VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

FILE(GLOB_RECURSE source src/*)
file(GLOB_RECURSE TEST "test/*.cpp")

add_library(binary-search-tree INTERFACE)
target_include_directories(binary-search-tree INTERFACE ${CMAKE_SOURCE_DIR}/include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_executable(test_suit_bst ${TEST})
target_link_libraries(test_suit_bst binary-search-tree)