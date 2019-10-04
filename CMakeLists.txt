#CMakeLists.txt to build project using cmake
#run $cmake CMakeLists.txt

cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_FLAGS "-Wall")

project(visu)

include_directories(header/)

file(
  GLOB_RECURSE 
  source_files
  src/* header/* 
)

add_executable(
  visu
  ${source_files}
)

