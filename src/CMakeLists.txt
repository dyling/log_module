cmake_minimum_required(VERSION 3.4.1)
project(log_module)

MESSAGE("Build type: " ${CMAKE_BUILD_TYPE})
SET(CMAKE_BUILD_TYPE "Debug")

aux_source_directory(. SRC_LIST)

# add_library(${PROJECT_NAME} ${SRC_LIST})

add_executable(${PROJECT_NAME} 
    ${SRC_LIST}
)

include_directories(/usr/local/include/)

# NOT SUPPORT 
# link_libraries(/usr/local/lib/libboost_filesystem.a)
# link_directories("/usr/local/lib/")

target_link_libraries(${PROJECT_NAME} libboost_filesystem.a)

# add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
# add_definitions(-DBOOST_SYSTEM_NO_DEPRECATED)


