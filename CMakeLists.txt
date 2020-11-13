cmake_minimum_required(VERSION "3.9.2")

project(IA-Coche)

set(SOURCES
  src/Malla.cpp
  src/Celda.cpp
  src/Texturas.cpp
  src/Coche.cpp
  src/algoritmos.cpp
)

set(CMAKE_CXX_FLAGS "-O2")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS_DEBUG "-g -pedantic-errors -Wall -Wextra -std=c++17 -fsanitize=address")
# set(CMAKE_CXX_FLAGS_DEBUG "-g -pedantic-errors -Wall -Wextra -std=c++17")

set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,-clang-analyzer-*,performance-*,readability-*,-readability-implicit-bool-conversion,-readability-magic-numbers,modernize-*,-modernize-use-trailing-return-type,bugprone-*)

set(SFML_DIR "/usr/include/SFML")
find_package(SFML REQUIRED COMPONENTS system window graphics network audio)
add_executable(main ${SOURCES} src/main.cpp)
target_link_libraries(main sfml-graphics sfml-audio)

#find_package(Catch2 REQUIRED)
#enable_testing()

add_executable(mytest EXCLUDE_FROM_ALL ${SOURCES} test/mytest.cpp)
#target_link_libraries(mytest Catch2::Catch2)
#add_test(
#  NAME mytest
#  COMMAND mytest)
add_custom_target(check COMMAND
                  DEPENDS mytest)
