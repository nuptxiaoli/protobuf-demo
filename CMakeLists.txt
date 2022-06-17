
cmake_minimum_required (VERSION 2.6)

project (protobuf-demo)
AUX_SOURCE_DIRECTORY(./ SRC_LIST)
include_directories (${PROJECT_SOURCE_DIR}/protobuf2/include)

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/protobuf2/lib)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} protobuf)


