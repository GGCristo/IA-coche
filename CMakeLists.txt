cmake_minimum_required(VERSION "3.9.2")

project(IA-Coche)

set(SOURCES
  src/Mapa.cpp
  src/Celda.cpp
  src/Texturas.cpp
  src/Coche.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS_DEBUG "-g -pedantic-errors -Wall -Wextra -std=c++17 -fsanitize=address")
#set(CMAKE_CXX_FLAGS_DEBUG "-g -pedantic-errors -Wall -Wextra -std=c++17")

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
