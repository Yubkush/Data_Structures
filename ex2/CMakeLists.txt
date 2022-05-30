cmake_minimum_required(VERSION 3.0.0)
project(ex2 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
SET(COMPILE_FLAGS "-std=c++11 -DNDEBUG -Wall")
set(CMAKE_CPP_FLAGS ${COMPILE_FLAGS})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(
  hash_test
  tests/HashTable_test.cpp
  HashTable.cpp
  LinkedList.cpp
  Employee.cpp
)
target_link_libraries(
  hash_test
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(hash_test)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
