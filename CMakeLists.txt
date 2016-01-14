cmake_minimum_required(VERSION 2.6)
project(sm_utils)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests)

if (CMAKE_COMPILER_IS_GNUCC)
  # set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -pg")
  set(CMAKE_CXX_FLAGS "-Wall -O3 -s -std=c++11")
  # set(CMAKE_EXE_LINKER_FLAGS "-pg")
  # set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static-libgcc -static")
endif (CMAKE_COMPILER_IS_GNUCC)

include_directories(include)
add_subdirectory(src)
