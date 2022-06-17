
cmake_minimum_required (VERSION 2.8)

project (protobuf-demo)
include_directories ("${PROJECT_SOURCE_DIR}/protobuf2/include")

add_executable(demo main.cc)

