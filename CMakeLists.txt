cmake_minimum_required(VERSION 3.4.1)
project(log_test)

MESSAGE("Build type: " ${CMAKE_BUILD_TYPE})
SET(CMAKE_BUILD_TYPE "Debug")

find_package(Boost REQUIRED COMPONENTS system filesystem)


aux_source_directory(. SRC_LIST) # 搜索当前目录下的所有.cpp文件

set(DIR_VISSIM_TCP_COMM_SRC 
    ../../git_lib/simpro_function_safety/Runtime/Vissim/VissimTcpServer/VissimTcpServer/VissimTcpComm.cpp)
set(DIR_VISSIM_TCP_COMM_HEAD 
    ../../git_lib/simpro_function_safety/Runtime/Vissim/VissimTcpServer/VissimTcpServer/VissimTcpComm.h
)




# add_library(${PROJECT_NAME} ${SRC_LIST})

add_executable(${PROJECT_NAME} 
    ${SRC_LIST}
    ${DIR_VISSIM_TCP_COMM_SRC}
    ${DIR_VISSIM_TCP_COMM_HEAD}
)


target_link_libraries(${PROJECT_NAME}  -lboost_filesystem)  #链接

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
add_definitions(-DBOOST_SYSTEM_NO_DEPRECATED)


