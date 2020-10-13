cmake_minimum_required(VERSION "3.10")

project(IA-Coche)

set(SOURCES
  src/Mapa.cpp
  src/Celda.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
#set(CMAKE_CXX_FLAGS_DEBUG "-g -pedantic-errors -Wall -Wextra -std=c++17 -fsanitize=address")
set(CMAKE_CXX_FLAGS_DEBUG "-g -pedantic-errors -Wall -Wextra -std=c++17")
add_executable(main ${SOURCES} src/main.cpp)

#find_package(Catch2 REQUIRED)
#enable_testing()

add_executable(mytest EXCLUDE_FROM_ALL ${SOURCES} test/mytest.cpp)
#target_link_libraries(mytest Catch2::Catch2)
#add_test(
#  NAME mytest
#  COMMAND mytest)
add_custom_target(check COMMAND
                  DEPENDS mytest)
